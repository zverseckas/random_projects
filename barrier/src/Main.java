/**
 * Demo of a graph density calculator with a cyclic barrier
 * Created by zilvinas on 16.3.5.
 */
public class Main {
    public static void main(String[] arga) {
        int[][] m = {
            {2, 1, 0, 0, 1, 0},
            {1, 0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 0},
            {0, 0, 1, 0, 1, 1},
            {1, 1, 0, 1, 0, 0},
            {0, 0, 0, 1, 0, 0}
        };
        Graph g = new Graph(m, false);
        System.out.println(g.getDensity());

        Barrier b = new Barrier(4);

        Test t1 = new Test(1000, b);
        Test t2 = new Test(0, b);
        Test t3 = new Test(500, b);
        Test t4 = new Test(200, b);

        t1.start();
        t2.start();
        t3.start();
        t4.start();

    }
}
