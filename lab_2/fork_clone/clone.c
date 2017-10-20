#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sched.h>
#include <linux/sched.h>
#include <sys/syscall.h>

int zmienna_globalna=0;

#define ROZMIAR_STOSU 1024*64

int funkcja_watku( void* argument )
{
  int i;
  pid_t tid = (pid_t) syscall (SYS_gettid);

  int local_var = *((int *)argument);

  for (i = 0; i < 10000; i++) {
    zmienna_globalna++;
    //printf("[tid: %d] | %d\n", tid, zmienna_globalna++);
    local_var++;
  }

  printf("[pid: %d | tid: %d]  local var: %d, global var: %d\n", getpid(), tid, local_var, zmienna_globalna);

  return 0;
}

main()
{

  void *stos;
  pid_t pid;
  pid_t tids[2];
  int local_var = 0;
  int i;

  stos = malloc( 2*ROZMIAR_STOSU);
  if (stos == 0) {
    printf("Proces nadrzędny - blad alokacji stosu\n");
    exit( 1 );
  }

  printf("This process pid is %d\n", getpid());

  for(i=0;i<2;i++) {
    tids[i] = clone( &funkcja_watku, (void *) stos+(ROZMIAR_STOSU*(i+1)),
		 CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM, (void*)&local_var );
    printf("Thread %d created. It's id is %d\n", i, tids[i]);
  } printf("\n");

  waitpid(tids[0], NULL, __WCLONE);
  waitpid(tids[1], NULL, __WCLONE);
  printf("-----------------------------------------\n");
  printf("pid: %d, local var: %d, global_var: %d\n", getpid(), local_var, zmienna_globalna);
  free( stos );
}
