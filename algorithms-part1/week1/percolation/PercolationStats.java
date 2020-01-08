/* *****************************************************************************
 *  Name:              Alan Turing
 *  Coursera User ID:  123456
 *  Last modified:     1/1/2019
 **************************************************************************** */

import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;

import java.util.Random;

public class PercolationStats {
    // perform independent trials on an n-by-n grid
    public PercolationStats(int n, int trials) {
        if (n <= 0 || trials <= 0) {
            throw new IllegalArgumentException("invalide argument");
        }
    }

    // sample mean of percolation threshold
    public double mean() {
        return 0.3;
    }

    // sample standard deviation of percolation threshold
    public double stddev() {
        return 0.0;
    }

    // low endpoint of 95% confidence interval
    public double confidenceLo() {
        return 0.1;
    }

    // high endpoint of 95% confidence interval
    public double confidenceHi() {
        return 0.5;
    }

    public static void main(String[] args) {
        int n = 100;
        int expr = 50;
        if (args.length == 2) {
            n = Integer.parseInt(args[0]);
            expr = Integer.parseInt(args[1]);
        }

        // repeatedly open site specified my mouse click and draw resulting system
        StdOut.println(n);
        StdDraw.enableDoubleBuffering();
        Percolation perc = new Percolation(n);
        PercolationVisualizer.draw(perc, n);
        StdDraw.show();

        /*random*/
        Random r = new Random();
        int x = r.nextInt(n) + 1;
        int y = r.nextInt(n) + 1;
        perc.open(x, y);
        StdDraw.pause(5);
    }
}
