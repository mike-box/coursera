/* *****************************************************************************
 *  Name:
 *  Date:
 *  Description:
 **************************************************************************** */

import edu.princeton.cs.algs4.Picture;

public class SeamCarver {
    private int[][] pixels;
    private double[][] imgenergy;
    private int width;
    private int height;
    private final int border = 1000;

    // create a seam carver object based on the given picture
    public SeamCarver(Picture picture) {
        if (picture == null) throw new IllegalArgumentException();
        this.width = picture.width();
        this.height = picture.height();
        this.imgenergy = new double[this.height][];
        this.pixels = new int[this.height][];
        for (int i = 0; i < this.height; ++i) {
            this.imgenergy[i] = new double[this.width];
            this.pixels[i] = new int[this.width];
        }

        for (int i = 0; i < this.height; ++i) {
            for (int j = 0; j < this.width; ++j) {
                this.pixels[i][j] = picture.getRGB(j, i);
            }
        }
        for (int i = 0; i < this.height; ++i) {
            for (int j = 0; j < this.width; ++j) {
                this.imgenergy[i][j] = energy(j, i);
            }
        }
    }

    // current picture
    public Picture picture() {
        Picture p = new Picture(this.width, this.height);
        for (int i = 0; i < this.height; ++i) {
            for (int j = 0; j < this.width; ++j) {
                p.setRGB(j, i, pixels[i][j]);
            }
        }

        return p;
    }

    // width of current picture
    public int width() {
        return this.width;
    }

    // height of current picture
    public int height() {
        return this.height;
    }

    // get delta square
    private double square(int cx, int cy) {
        int dr = ((cx >> 16) & 0xFF) - ((cy >> 16) & 0xFF);
        int dg = ((cx >> 8) & 0xFF) - ((cy >> 8) & 0xFF);
        int db = ((cx) & 0xFF) - ((cy) & 0xFF);
        return dr * dr + dg * dg + db * db;
    }

    // assert row index is valid
    private void assertRow(int row) {
        if (row < 0 || row >= this.height) throw new IllegalArgumentException();
    }

    // assert column index is valid
    private void assertCol(int col) {
        if (col < 0 || col >= this.width) throw new IllegalArgumentException();
    }

    private void assertHorizontalSeam(int[] seam) {
        if (seam == null || seam.length != this.width)
            throw new IllegalArgumentException();
        for (int i = 0; i < this.width; ++i) {
            if (seam[i] < 0 || seam[i] >= height)
                throw new IllegalArgumentException();
            if (i > 0 && Math.abs(seam[i] - seam[i - 1]) > 1)
                throw new IllegalArgumentException();
        }
    }

    private void assertVerticalSeam(int[] seam) {
        if (seam == null || seam.length != this.height)
            throw new IllegalArgumentException();
        for (int i = 0; i < this.height; ++i) {
            if (seam[i] < 0 || seam[i] >= width)
                throw new IllegalArgumentException();
            if (i > 0 && Math.abs(seam[i] - seam[i - 1]) > 1)
                throw new IllegalArgumentException();
        }
    }

    // energy of pixel at column x and row y
    public double energy(int x, int y) {
        assertRow(y);
        assertCol(x);
        if (x == 0 || x == this.width - 1) return border;
        if (y == 0 || y == this.height - 1) return border;
        double dx = square(this.pixels[y][x - 1], this.pixels[y][x + 1]);
        double dy = square(this.pixels[y - 1][x], this.pixels[y + 1][x]);
        return Math.sqrt(dx + dy);
    }

    // sequence of indices for horizontal seam
    public int[] findHorizontalSeam() {
        double[] dp = new double[this.height];
        double[] copy = new double[this.height];
        int[][] moves = new int[this.height][];
        int[] res = new int[this.width];

        for (int i = 0; i < this.height; i++) {
            dp[i] = border;
            moves[i] = new int[this.width];
        }
        for (int i = 1; i < this.width; i++) {
            for (int j = 0; j < this.height; j++) {
                int move = 0;
                if (j - 1 >= 0 && dp[j - 1] < dp[j + move]) move = -1;
                if (j + 1 < height && dp[j + 1] < dp[j + move]) move = 1;
                copy[j] = imgenergy[j][i] + dp[j + move];
                moves[j][i] = move;
            }
            System.arraycopy(copy, 0, dp, 0, height);
        }

        int start = 0;
        for (int i = 0; i < this.height; ++i) {
            if (dp[i] < dp[start]) start = i;
        }
        for (int i = this.width - 1; i >= 0; --i) {
            res[i] = start;
            start += moves[start][i];
        }
        return res;
    }

    // sequence of indices for vertical seam
    public int[] findVerticalSeam() {
        double[] dp = new double[this.width];
        double[] copy = new double[this.width];
        int[][] moves = new int[this.height][];
        int[] res = new int[this.height];

        for (int i = 0; i < this.height; i++) {
            moves[i] = new int[width];
        }
        for (int i = 0; i < this.width; i++) {
            dp[i] = border;
            moves[0][i] = 0;
        }
        for (int i = 1; i < this.height; i++) {
            for (int j = 0; j < this.width; j++) {
                int move = 0;
                if (j - 1 >= 0 && dp[j - 1] < dp[j + move]) move = -1;
                if (j + 1 < width && dp[j + 1] < dp[j + move]) move = 1;
                copy[j] = imgenergy[i][j] + dp[j + move];
                moves[i][j] = move;
            }
            System.arraycopy(copy, 0, dp, 0, width);
        }

        int start = 0;
        for (int i = 0; i < this.width; ++i) {
            if (dp[i] < dp[start]) start = i;
        }
        for (int i = this.height - 1; i >= 0; --i) {
            res[i] = start;
            start += moves[i][start];
        }
        return res;
    }

    // remove horizontal seam from current picture
    public void removeHorizontalSeam(int[] seam) {
        assertHorizontalSeam(seam);
        for (int i = 0; i < width; ++i) {
            for (int j = seam[i]; j < height - 1; ++j) {
                this.pixels[j][i] = this.pixels[j + 1][i];
            }
        }
        height--;
        for (int i = 0; i < width; i++) {
            int top = seam[i];
            if (i - 1 >= 0 && seam[i - 1] < top) top = seam[i - 1];
            if (i + 1 < width && seam[i + 1] < top) top = seam[i + 1];
            top = Math.max(top - 1, 0);
            for (int j = top; j < height; ++j) {
                imgenergy[j][i] = energy(i, j);
            }
        }
    }

    // remove vertical seam from current picture
    public void removeVerticalSeam(int[] seam) {
        assertVerticalSeam(seam);
        for (int i = 0; i < height; ++i) {
            System.arraycopy(pixels[i], seam[i] + 1, pixels[i], seam[i], width - seam[i] - 1);
        }
        width--;
        for (int i = 0; i < height; i++) {
            int left = seam[i];
            if (i - 1 >= 0 && seam[i - 1] < left) left = seam[i - 1];
            if (i + 1 < height && seam[i + 1] < left) left = seam[i + 1];
            left = Math.max(0, left - 1);
            for (int j = left; j < width; ++j) {
                imgenergy[i][j] = energy(j, i);
            }
        }
    }
}
