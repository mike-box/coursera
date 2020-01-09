/* *****************************************************************************
 *  Name:              mike meng
 *  Coursera User ID:  mengmingliang
 *  Last modified:     1/8/2020
 **************************************************************************** */

import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;

public class PercolationStats {
    // perform independent trials on an n-by-n grid
    private final double[] threshold;
    private double meanVal;
    private double devVal;
    private final int trials;


    public PercolationStats(int n, int trials) {
        if (n <= 0 || trials <= 0) {
            throw new IllegalArgumentException();
        }

        this.threshold = new double[trials];
        this.trials = trials;
        this.meanVal = 0.0;
        this.devVal = 0.0;

        for (int i = 0; i < trials; ++i) {
            Percolation perc = new Percolation(n);
            while (perc.percolates() == false) {
                int row = StdRandom.uniform(n) + 1;
                int col = StdRandom.uniform(n) + 1;
                if (!perc.isOpen(row, col)) {
                    perc.open(row, col);
                }
            }
            threshold[i] = (double) perc.numberOfOpenSites() / (n * n);
        }
    }

    // sample mean of percolation threshold
    public double mean() {
        this.meanVal = StdStats.mean(threshold);
        return this.meanVal;
    }

    // sample standard deviation of percolation threshold
    public double stddev() {
        this.devVal = StdStats.stddev(threshold);
        return this.devVal;
    }

    // low endpoint of 95% confidence interval
    public double confidenceLo() {
        return this.meanVal - 1.96 * devVal / Math.sqrt(this.trials);
    }

    // high endpoint of 95% confidence interval
    public double confidenceHi() {
        return this.meanVal + 1.96 * devVal / Math.sqrt(this.trials);
    }

    public static void main(String[] args) {
        int n = 100;
        int expr = 50;
        if (args.length == 2) {
            n = Integer.parseInt(args[0]);
            expr = Integer.parseInt(args[1]);
        }

        double[] exprthreshold = new double[expr];
        for (int i = 0; i < expr; ++i) {
            Percolation perc = new Percolation(n);
            while (!perc.percolates()) {
                int row = StdRandom.uniform(n) + 1;
                int col = StdRandom.uniform(n) + 1;
                if (!perc.isOpen(row, col)) {
                    perc.open(row, col);
                }
            }
            exprthreshold[i] = (double) perc.numberOfOpenSites() / (n * n);
        }

        StdOut.println("mean                    =" + StdStats.mean(exprthreshold));
        StdOut.println("stddev                  =" + StdStats.stddev(exprthreshold));
        double lo = StdStats.mean(exprthreshold) - 1.96 / Math.sqrt(expr);
        double hi = StdStats.mean(exprthreshold) + 1.96 / Math.sqrt(expr);
        StdOut.println("95% confidence interval = [" + lo + "," + hi + "]");
    }
}
