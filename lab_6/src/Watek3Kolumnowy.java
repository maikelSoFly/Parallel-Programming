import java.util.Objects;

//     Project name: Histogram
//
//     Created by maikel on 12.11.2017.
//     Copyright © 2017 Mikołaj Stępniewski. All rights reserved.
//
public class Watek3Kolumnowy extends Thread {
    private Obraz obraz;
    private int id;
    private int num_threads;
    private int columns;
    private int[] loc_hist;
    private Object lock;

    public Watek3Kolumnowy(Obraz obraz, int id, int num_threads, int columns, Object lock) {
        this.obraz = obraz;
        this.id = id;
        this.num_threads = num_threads;
        this.columns = columns;
        this.lock = lock;
    }


    public void run() {
        loc_hist = new int[94];
        int start = id;
        int skok = num_threads;
        for(int i = start; i < columns; i += skok) {
            obraz.calculateHistogramColumn(i, loc_hist, id, lock);

        }
    }
}
