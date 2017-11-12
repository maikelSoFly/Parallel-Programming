//     Project name: Histogram
//
//     Created by maikel on 07.11.2017.
//     Copyright © 2017 Mikołaj Stępniewski. All rights reserved.
//
public class Watek3Wierszowy extends Thread {
    private int id;
    private Obraz obraz;
    private int[] loc_hist;
    private int num_threads;
    private int rows;


    public Watek3Wierszowy(Obraz obraz, int id, int num_threads, int rows) {
        this.obraz = obraz;
        this.id = id;
        this.num_threads = num_threads;
        this.rows = rows;
    }


    public void run() {
        loc_hist = new int[94];
        int start = id;
        int koniec = rows;
        int skok = num_threads;
        for(int i = start; i < koniec; i+=skok) {
            obraz.calculateHistogramRow(i, loc_hist);
        }
    }

    public int[] getHist() {
        return this.loc_hist;
    }
}
