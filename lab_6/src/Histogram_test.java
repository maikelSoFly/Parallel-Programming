//     Project name: Histogram
//
//     Created by maikel on 06.11.2017.
//     Copyright © 2017 Mikołaj Stępniewski. All rights reserved.
//
import java.util.Scanner;


class Histogram_test {

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);

        System.out.println("Set image size: n (#rows), m(#kolumns)");
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        Obraz obraz_1 = new Obraz(n, m);

        //obraz_1.calculate_histogram();
        //obraz_1.print_histogram();


         // Zadanie 1.
        int num_threads = 94;

         Watek[] NewThr = new Watek[num_threads];

         for (int i = 0; i < num_threads; i++) {
             (NewThr[i] = new Watek(obraz_1, (char)(33+i), i)).start();
         }

         for (int i = 0; i < num_threads; i++) {
             try {
                 NewThr[i].join();
             } catch (InterruptedException e) {
                e.printStackTrace();
             }
         }

        // Zadanie 2.
        System.out.println("--- Zadanie 2 ---");

        System.out.println("Set number of threads");
        num_threads = scanner.nextInt();
        Watek2[] NewThr2 = new Watek2[num_threads];
        Thread[] NewThr2Thr = new Thread[num_threads];

        int ilosc_znakow = 94/num_threads;
        Object lock = new Object();

        for (int i = 0; i < num_threads; i++) {
            NewThr2[i] = new Watek2(obraz_1, i, ilosc_znakow, lock);
            (NewThr2Thr[i] = new Thread(NewThr2[i])).start();
        }

        for (int i = 0; i < num_threads; i++) {
            try {
                NewThr2Thr[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }


        // Zadanie 3.

        System.out.println("---Zadanie 3 (wierszowo)---");

        Watek3Wierszowy[] NewThr3 = new Watek3Wierszowy[num_threads];

        for (int i = 0; i < num_threads; i++) {
            (NewThr3[i] = new Watek3Wierszowy(obraz_1, i, num_threads, n)).start();
        }

        for (int i = 0; i < num_threads; i++) {
            try {
                NewThr3[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        int[] histogram = new int[94];
        for(int i = 0; i < 94; i++) {
            histogram[i] = 0;
        }

        for (int i = 0; i < num_threads; i++) {
            int[] loc_hist = NewThr3[i].getHist();

            for(int j = 0; j < 94; j++) {
                histogram[j] += loc_hist[j];
            }
        }

        for(int i = 0; i < 94; i++) {
            System.out.println((char)(33+i) +" "+ histogram[i]);
        }


        // Zadanie Dodatkowe
        System.out.println("---Zadanie dodatkowe---");
        Watek3Kolumnowy[] NewThr4 = new Watek3Kolumnowy[num_threads];

        for(int i = 0; i < num_threads; i++) {
            (NewThr4[i] = new Watek3Kolumnowy(obraz_1, i, num_threads, m, lock)).start();
        }

        for(int i = 0; i < num_threads; i++) {
            try {
                NewThr4[i].join();
            } catch(InterruptedException e) {
                e.printStackTrace();
            }
        }



    }

}