/* *****************************************************************************
 *  Name:              Alan Turing
 *  Coursera User ID:  123456
 *  Last modified:     1/1/2019
 **************************************************************************** */

public class Percolation {
    private int[][] grid;
    private int rowSz;
    private int colSz;
    private int[] roots;
    private int[] sz;
    private int openSz;
    private boolean[] touchTop;
    private boolean[] touchButtom;
    private boolean state;

    // creates n-by-n grid, with all sites initially blocked
    public Percolation(int n) {
        this.grid = new int[n][];
        this.rowSz = n;
        this.colSz = n;
        this.roots = new int[n * n];
        this.sz = new int[n * n];
        this.openSz = 0;
        this.touchTop = new boolean[n * n];
        this.touchButtom = new boolean[n * n];
        this.state = false;

        for (int i = 0; i < n; ++i) {
            grid[i] = new int[n];
            for (int j = 0; j < n; ++j) {
                grid[i][j] = 0;
                roots[i * n + j] = i * n + j;
                sz[i * n + j] = 1;
                touchTop[i * n + j] = false;
                touchButtom[i * n + j] = false;
            }
        }
    }

    public int find(int row, int col) {
        int val = row * colSz + col;
        while (roots[val] != val) {
            val = roots[val];
        }

        return val;
    }

    public boolean connected(int row1, int col1, int row2, int col2) {
        int root1 = find(row1, col1);
        int root2 = find(row2, col2);
        if (root1 == root2) {
            return true;
        }
        else {
            return false;
        }
    }

    public int count(int row, int col) {
        int root = find(row, col);
        return sz[root];
    }

    public boolean union(int row1, int col1, int row2, int col2) {
        int root1 = find(row1, col1);
        int root2 = find(row2, col2);
        if (root1 == root2) {
            return true;
        }

        if (sz[root1] > sz[root2]) {
            roots[root2] = root1;
            sz[root1] += sz[root2];
            touchTop[root1] = this.touchTop[root1] || this.touchTop[root2];
            touchButtom[root1] = this.touchButtom[root1] || this.touchButtom[root2];
            this.state = this.state || (touchButtom[root1] & touchButtom[root1]);
        }
        else {
            roots[root1] = root2;
            sz[root2] += sz[root1];
            touchTop[root2] = this.touchTop[root1] | this.touchTop[root2];
            touchButtom[root2] = this.touchButtom[root1] | this.touchButtom[root2];
            this.state = this.state || (touchButtom[root2] & touchButtom[root2]);
        }

        return true;
    }

    // opens the site (row, col) if it is not open already
    public void open(int row, int col) {
        int[] d = { 0, -1, 0, 1, 0 };
        row--;
        col--;
        if (row < 0 || row >= this.rowSz || col < 0 || col >= this.colSz) {
            return;
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
            return false;
        }
        return grid[row][col] == 1;
    }

    // is the site (row, col) full?
    public boolean isFull(int row, int col) {
        row--;
        col--;
        if (row < 0 || row >= this.rowSz || col < 0 || col >= this.colSz) {
            return false;
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
