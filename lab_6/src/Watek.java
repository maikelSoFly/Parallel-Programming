//     Project name: Histogram
//
//     Created by maikel on 07.11.2017.
//     Copyright © 2017 Mikołaj Stępniewski. All rights reserved.
//
public class Watek extends Thread {
    private Obraz obraz;
    private Integer id;
    private char znak;


    public Watek(Obraz obraz, char znak, Integer id) {
        this.obraz = obraz;
        this.znak = znak;
        this.id = id;
    }

    @Override
    public void run() {
        Integer counter = obraz.seekForChar(this.znak);
        System.out.println("[watek "+id+"]  "+znak +": "+ counter);
    }


    public static void main(String args[]) {

    }
}
