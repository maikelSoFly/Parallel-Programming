//     Project name: Histogram
//
//     Created by maikel on 07.11.2017.
//     Copyright © 2017 Mikołaj Stępniewski. All rights reserved.
//
public class Watek2 implements Runnable {
    private Obraz obraz;
    private int id;
    private char[] znaki;
    private int iloscZnakow;
    private int[] histogram;


    public Watek2(Obraz obraz, int id, int iloscZnakow) {
        this.obraz = obraz;
        this.id = id;
        this.iloscZnakow = iloscZnakow;
        this.znaki = new char[iloscZnakow];
    }


    public void run() {
        for(int i = 0; i < iloscZnakow; i++) {
            znaki[i] = (char)(33+(id*iloscZnakow)+i);
        }
        histogram = new int[iloscZnakow];
        for(int i = 0; i < iloscZnakow; i++)
            histogram[i] = 0;
        obraz.seekForChars(znaki, histogram);
    }

    public int[] getHistogram() {
        return this.histogram;
    }

    public char[] getZnaki() {
        return this.znaki;
    }

}
