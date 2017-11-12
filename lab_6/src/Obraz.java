//     Project name: Histogram
//
//     Created by maikel on 06.11.2017.
//     Copyright © 2017 Mikołaj Stępniewski. All rights reserved.
//
import  java.util.Random;


class Obraz {

    private int size_n;
    private int size_m;
    private char[][] tab;
    private int[] histogram;

    public Obraz(int n, int m) {

        this.size_n = n;
        this.size_m = m;
        tab = new char[n][m];

        final Random random = new Random();

        for(int i=0;i<n;i++) {
            for(int j=0;j<m;j++) {
                tab[i][j] = (char)(random.nextInt(94)+33);  // ascii 33-127
                System.out.print(tab[i][j]+" ");
            }
            System.out.print("\n");
        }
        System.out.print("\n\n");

        histogram = new int[94];
        clear_histogram();
    }

    public void clear_histogram(){
        for(int i=0;i<94;i++) histogram[i]=0;
    }

    public void calculate_histogram(){
        for(int i=0;i<size_n;i++) {
            for(int j=0;j<size_m;j++) {
                for(int k=0;k<94;k++) {
                    if(tab[i][j] == (char)(k+33)) histogram[k]++;
                }
            }
        }
    }

    public Integer seekForChar(char znak) {
        Integer counter = 0;
        for(int i=0;i<size_n;i++) {
            for(int j=0;j<size_m;j++) {
                if(tab[i][j] == znak) {
                    counter++;
                }
            }
        }

        return counter;
    }

    public void seekForChars(char[] znaki, int[] histogram, Object lock, int id) {
        for(int i=0;i<size_n;i++) {
            for(int j=0;j<size_m;j++) {
                for(int k=0;k<znaki.length;k++) {

                    if(tab[i][j] == znaki[k]) {
                        synchronized (lock) {
                            histogram[k]++;
                            System.out.println("[Watek: "+id+"]  "+znaki[k] +" "+ histogram[k]);
                        }

                    }
                }
            }
        }
    }

    public void calculateHistogramRow(int row, int[] loc_hist) {
        for(int i=0;i<size_n;i++) {
            for(int k=0;k<94;k++) {
                if(tab[row][i] == (char)(k+33)) loc_hist[k]++;
            }
        }
    }

    public void calculateHistogramColumn(int column, int[] loc_hist, int id, Object lock) {
        for(int i=0;i<size_m;i++) {
            for(int k=0;k<94;k++) {

                if (tab[i][column] == (char) (k + 33)) {
                    synchronized (lock) {
                        loc_hist[k]++;
                        System.out.println("[Watek: "+id+"] " +" "+ tab[i][column] +": "+loc_hist[k]);
                    }
                }

            }
        }
    }

    public void print_histogram(){
        for(int i=0;i<94;i++) {
            System.out.print((char)(i+33)+" "+histogram[i]+"\n");
        }
    }

    public char[][] getTab() {
        return tab;
    }

}