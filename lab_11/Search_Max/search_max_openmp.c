/**
 * @Author: Mikołaj Stępniewski <maikel>
 * @Date:   2015-12-10T00:05:04+01:00
 * @Email:  mikolaj.stepniewski1@gmail.com
 * @Filename: search_max_openmp.c
 * @Last modified by:   maikel
 * @Last modified time: 2017-12-17T17:04:52+01:00
 * @License: Apache License  Version 2.0, January 2004
 * @Copyright: Copyright © 2017 Mikołaj Stępniewski. All rights reserved.
 */



#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<omp.h>

#include "search_max_openmp.h"

/********************** linear search ************************/
double search_max(
		      double *A,
		      int p,
		      int k
		      )
{

  double a_max = A[p];
  int i;
  for(i=p+1; i<=k; i++) if(a_max < A[i]) a_max = A[i];

  return(a_max);
}

/************* parallel linear search - openmp ****************/
double search_max_openmp_simple(
		      double *A,
		      int p,
		      int k
		      )
{

  double a_max = A[p];
  double a_max_local = a_max;

#pragma omp parallel default(none) firstprivate(A, p, k, a_max_local) shared(a_max)
  {
    int i;
#pragma omp for
    for(i=p+1; i<=k; i++) if(a_max_local < A[i]) a_max_local = A[i];

#pragma omp critical (cs_a_max)
    {
      if(a_max < a_max_local) a_max = a_max_local;
    }

  }

  return(a_max);
}


/************* parallel linear search - openmp ****************/
double search_max_openmp_task(
		      double *A,
		      int p,
		      int k
		      )
{

  double a_max = A[p];
  double a_max_local = a_max;

#pragma omp parallel default(none) shared(a_max) firstprivate(A,p,k, a_max_local)
  {

#pragma omp single
    {
      int num_threads = omp_get_num_threads();
      int n = k-p+1;

      int num_tasks = num_threads+1;
      int n_loc=ceil(n/num_tasks);

      int itask, i;
      for(itask=0; itask<num_tasks; itask++){

	int p_task = p+itask*n_loc;
	if(p_task>k) {
	  printf("Error in task decomposition! Exiting.\n");
	  exit(0);
	}
	int k_task = p+(itask+1)*n_loc-1;
	if(itask==num_tasks-1) k_task = k;

#pragma omp task default(none) firstprivate(p_task, k_task, a_max_local, A) shared(a_max) private(i)
	{
		for(i = p_task; i < k_task; i++) {
			if(a_max_local < A[i]) a_max_local = A[i];
		}

		if(a_max < a_max_local) {
			#pragma omp critical
			a_max = a_max_local;
		}

	} // end task definition

      } // end loop over tasks
    } // end single region
  } // end parallel region

  return(a_max);
}


/************ binary search (array not sorted) ****************/
double bin_search_max(
		      double *a,
		      int p,
		      int k
)
{

  if(p<k) {

    int s=(p+k)/2;

    double a_max_1 = bin_search_max(a, p, s);

    double a_max_2 = bin_search_max(a, s+1, k);

    //printf("p %d  k %d, maximal elements %lf, %lf\n", p, k, a_max_1, a_max_2);


    if(a_max_1 < a_max_2) return(a_max_2);
    else return(a_max_1);

  }
  else{

    return(a[p]);

  }

}


/*** single task for parallel binary search (array not sorted) - openmp ***/
#define  max_level 19

double bin_search_max_task(
  double* A,
  int p,
  int k,
  int level
			   )
{
	if(p<k) {

	  level++;

      int s=(p+k)/2;
	  double a_max_1, a_max_2;


	 #pragma omp task final(level > max_level) default(none) firstprivate(A, p,k,s,level) shared(a_max_1, a_max_2)
	 {
	 	if (!omp_in_final())
		 	a_max_1 = bin_search_max_task(A, p, s, level);
		else
		 	a_max_1 = search_max(A,p,s);
	 }

	 #pragma omp task final(level > max_level) default(none) firstprivate(A, p,k,s,level) shared(a_max_1, a_max_2)
	 {
		if (!omp_in_final())
		 	a_max_2 = bin_search_max_task(A, s+1, k, level);
		else
			a_max_2 = search_max(A,s+1,k);
	 }

	  #pragma omp taskwait
	  if(a_max_1 < a_max_2)
		  return(a_max_2);
      else return(a_max_1);

  }
  else{
	return(A[p]);
  }


}

/********** parallel binary search (array not sorted) - openmp ***********/

double bin_search_max_openmp(
		      double *A,
		      int p,
		      int k
){

  double a_max;

#pragma omp parallel default(none) firstprivate(A,p,k) shared(a_max)
  {
#pragma omp single
    {
#pragma omp task
     {
	  a_max = bin_search_max_task(A,p,k,0);
     }
    }
  }

  return(a_max);
}
