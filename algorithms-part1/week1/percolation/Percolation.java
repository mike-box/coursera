/* *****************************************************************************
 *  Name:              mike meng
 *  Coursera User ID:  mengmingliang
 *  Last modified:     1/8/2020
 **************************************************************************** */

import edu.princeton.cs.algs4.WeightedQuickUnionUF;

public class Percolation {
    private int[][] grid;
    private final int rowSz;
    private final int colSz;
    private int openSz;
    private boolean[] touchTop;
    private boolean[] touchButtom;
    private boolean state;
    private WeightedQuickUnionUF uf;

    // creates n-by-n grid, with all sites initially blocked
    public Percolation(int n) {
        if (n <= 0) {
            throw new java.lang.IllegalArgumentException();
        }

        this.uf = new WeightedQuickUnionUF(n * n);
        this.grid = new int[n][];
        this.rowSz = n;
        this.colSz = n;
        this.openSz = 0;
        this.touchTop = new boolean[n * n];
        this.touchButtom = new boolean[n * n];
        this.state = false;

        for (int i = 0; i < n; ++i) {
            grid[i] = new int[n];
            for (int j = 0; j < n; ++j) {
                grid[i][j] = 0;
                touchTop[i * n + j] = false;
                touchButtom[i * n + j] = false;
            }
        }
    }

    private int find(int row, int col) {
        int val = row * colSz + col;
        return uf.find(val);
    }

    private boolean union(int row1, int col1, int row2, int col2) {
        int root1 = find(row1, col1);
        int root2 = find(row2, col2);
        uf.union(root1, root2);
        boolean canTouchTop = this.touchTop[root1] || this.touchTop[root2];
        boolean canTouchButtom = this.touchButtom[root1] || this.touchButtom[root2];
        touchTop[root1] = canTouchTop;
        touchButtom[root1] = canTouchButtom;
        touchTop[root2] = canTouchTop;
        touchButtom[root2] = canTouchButtom;
        this.state = this.state || (canTouchTop && canTouchButtom);

        return true;
    }

    // opens the site (row, col) if it is not open already
    public void open(int row, int col) {
        int[] d = { 0, -1, 0, 1, 0 };
        row--;
        col--;
        if (row < 0 || row >= this.rowSz || col < 0 || col >= this.colSz) {
            throw new java.lang.IllegalArgumentException();
        }
        if (this.grid[row][col] == 1) {
            return;
        }

        this.grid[row][col] = 1;
        this.openSz++;
        if (row == 0) {
            this.touchTop[row * colSz + col] = true;
        }
        if (row == rowSz - 1) {
            this.touchButtom[row * colSz + col] = true;
        }
        if (rowSz == 1) {
            this.state = true;
        }
        for (int i = 0; i < 4; ++i) {
            int x = row + d[i];
            int y = col + d[i + 1];
            if (x >= 0 && x < this.rowSz && y >= 0 && y < this.colSz) {
                if (this.grid[x][y] == 1) {
                    union(row, col, x, y);
                }
            }
        }
    }

    // is the site (row, col) open?
    public boolean isOpen(int row, int col) {
        row--;
        col--;
        if (row < 0 || row >= this.rowSz || col < 0 || col >= this.colSz) {
            throw new java.lang.IllegalArgumentException();
        }
        return grid[row][col] == 1;
    }

    // is the site (row, col) full?
    public boolean isFull(int row, int col) {
        row--;
        col--;
        if (row < 0 || row >= this.rowSz || col < 0 || col >= this.colSz) {
            throw new java.lang.IllegalArgumentException();
        }

        int root = find(row, col);
        if (touchTop[root]) {
            return true;
        }
        else {
            return false;
        }
    }

    // returns the number of open sites
    public int numberOfOpenSites() {
        return this.openSz;
    }

    // does the system percolate?
    public boolean percolates() {
        return this.state;
    }

    // test client (optional)
    public static void main(String[] args) {
        System.out.println("hello word!");
    }
}
