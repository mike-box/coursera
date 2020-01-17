/* *****************************************************************************
 *  Name:mingliang meng
 *  Date:2020.1.15
 *  Description: created by mike meng
 **************************************************************************** */

import java.util.ArrayList;
import java.util.Arrays;

public class Board {
    private int[][] blocks;
    private final int dimension;

    /**
     * construct a board from an n-by-n array of blocks
     * (where blocks[i][j] = block in row i, column j)
     *
     * @param tiles
     */
    public Board(int[][] tiles) {
        //check argument
        if (tiles == null || tiles.length == 0) {
            throw new IllegalArgumentException();
        }

        this.dimension = tiles.length;
        this.blocks = new int[tiles.length][];
        for (int i = 0; i < tiles.length; i++) {
            blocks[i] = Arrays.copyOf(tiles[i], this.dimension);
        }
    }

    /**
     * blocks formate to string.
     *
     * @param
     */
    public String toString() {
        StringBuilder s = new StringBuilder();
        s.append(dimension + "\n");
        for (int i = 0; i < dimension; i++) {
            for (int j = 0; j < dimension; j++) {
                s.append(String.format("%2d ", blocks[i][j]));
            }
            s.append("\n");
        }
        return s.toString();
    }


    /**
     * check the block is blank
     *
     * @param (x,y)
     */
    private boolean isBlank(int x, int y) {
        if (x < 0 || x >= this.dimension ||
                y < 0 || y >= this.dimension) {
            return true;
        }
        return this.blocks[x][y] == 0;
    }

    /**
     * check the block is blank
     *
     * @param
     */
    public int dimension() {
        return this.dimension;
    }

    /**
     * get the hamming distance
     *
     * @param
     */
    public int hamming() {
        int count = 0;
        for (int i = 0; i < this.dimension; ++i) {
            for (int j = 0; j < this.dimension; ++j) {
                if (blocks[i][j] != (i * this.dimension + j + 1) && !isBlank(i, j)) {
                    count++;
                }
            }
        }
        return count;
    }

    /**
     * get the manhattan distance
     *
     * @param
     */
    public int manhattan() {
        int count = 0;
        for (int i = 0; i < this.dimension; ++i) {
            for (int j = 0; j < this.dimension; ++j) {
                int correctrow = (this.blocks[i][j] - 1) / this.dimension;
                int correctcol = (this.blocks[i][j] - 1) % this.dimension;
                if (!isBlank(i, j)) {
                    count += Math.abs(correctrow - i) + Math.abs(correctcol - j);
                }
            }
        }

        return count;
    }

    /**
     * check is this board the goal board?
     *
     * @param
     */
    public boolean isGoal() {
        return this.hamming() == 0;
    }

    private boolean isArrayEqual(int[][] a, int[][] b) {
        for (int i = 0; i < a.length; ++i) {
            for (int j = 0; j < b.length; ++j) {
                if (a[i][j] != b[i][j]) return false;
            }
        }
        return true;
    }

    /**
     * does this board equal y?
     *
     * @param
     */
    public boolean equals(Object y) {
        if (this == y) return true;
        if (y == null) return false;
        if (y.getClass() != Board.class) return false;
        if (this.dimension != ((Board) y).dimension()) return false;
        return isArrayEqual(blocks, ((Board) y).blocks);
    }

    /**
     * all neighboring boards
     *
     * @param
     */
    public Iterable<Board> neighbors() {
        ArrayList<Board> res = new ArrayList<Board>();
        int blankRow = 0;
        int blankCol = 0;

        for (int i = 0; i < this.dimension; ++i) {
            for (int j = 0; j < this.dimension; ++j) {
                if (isBlank(i, j)) {
                    blankRow = i;
                    blankCol = j;
                    break;
                }
            }
        }

        int[] dir = new int[] { -1, 0, 1, 0, -1 };
        for (int i = 0; i < 4; ++i) {
            int x = blankRow + dir[i];
            int y = blankCol + dir[i + 1];
            if (x >= 0 && x < this.dimension &&
                    y >= 0 && y < this.dimension) {
                setBlocks(blankRow, blankCol, blocks[x][y]);
                setBlocks(x, y, 0);
                res.add(new Board(this.blocks));
                setBlocks(x, y, blocks[blankRow][blankCol]);
                setBlocks(blankRow, blankCol, 0);
            }
        }

        return res;
    }

    /**
     * set blocks (x,y) to val
     *
     * @param
     */
    private void setBlocks(int x, int y, int val) {
        this.blocks[x][y] = val;
    }

    /**
     * a board that is obtained by exchanging any pair of tiles
     *
     * @param
     */
    public Board twin() {
        for (int i = 0; i < this.dimension; ++i) {
            for (int j = 0; j < this.dimension; ++j) {
                if (!isBlank(i, j) && !isBlank(i, j + 1)) {
                    int val1 = this.blocks[i][j];
                    int val2 = this.blocks[i][j + 1];
                    setBlocks(i, j, val2);
                    setBlocks(i, j + 1, val1);
                    Board newboard = new Board(this.blocks);
                    setBlocks(i, j, val1);
                    setBlocks(i, j + 1, val2);
                    return newboard;
                }
            }
        }

        return null;
    }

}
