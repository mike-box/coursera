/* *****************************************************************************
 *  Name:
 *  Date:
 *  Description:
 **************************************************************************** */

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

import java.util.Comparator;

public class Solver {
    private final Stack<Board> seqList;
    private boolean canSlove;

    private class StateNode implements Comparable<StateNode> {
        public Board board;
        public StateNode previous;
        private final int moves;
        private final int priority;

        public StateNode(Board state, int moves, StateNode previous) {
            if (state == null) {
                throw new IllegalArgumentException();
            }

            this.board = state;
            this.previous = previous;
            this.moves = moves;
            this.priority = this.moves + state.manhattan();
        }

        public int compareTo(StateNode that) {
            if (this.priority < that.priority) return -1;
            if (this.priority > that.priority) return 1;
            return 0;
        }
    }

    /*
     *find a solution to the initial board (using the A* algorithm)
     *
     */
    public Solver(Board initial) {
        seqList = new Stack<Board>();
        MinPQ<StateNode> primaryQ = new MinPQ<StateNode>(new Comparator<StateNode>() {
            @Override
            public int compare(StateNode o1, StateNode o2) {
                return o1.compareTo(o2);
            }
        });
        MinPQ<StateNode> twinQ = new MinPQ<StateNode>(new Comparator<StateNode>() {
            @Override
            public int compare(StateNode o1, StateNode o2) {
                return o1.compareTo(o2);
            }
        });

        StateNode primaryStart = new StateNode(initial, 0, null);
        primaryQ.insert(primaryStart);
        StateNode twinStart = new StateNode(initial.twin(), 0, null);
        twinQ.insert(twinStart);

        while (!primaryQ.min().board.isGoal() && !twinQ.min().board.isGoal()) {
            StateNode primaryCurr = primaryQ.delMin();
            addNeigborsToQue(primaryCurr, primaryQ);

            StateNode twinCurr = twinQ.delMin();
            addNeigborsToQue(twinCurr, twinQ);
        }

        if (twinQ.min().board.isGoal()) {
            this.canSlove = false;
            return;
        }
        if (primaryQ.min().board.isGoal()) {
            this.canSlove = true;
            StateNode root = primaryQ.min();
            while (root != null) {
                seqList.push(root.board);
                root = root.previous;
            }
        }
    }

    private void addNeigborsToQue(StateNode curr, MinPQ<StateNode> pq) {
        Board prevBoard = null;
        if (curr.previous != null) {
            prevBoard = curr.previous.board;
        }

        for (Board next : curr.board.neighbors()) {
            if (next.equals(prevBoard)) continue;
            pq.insert(new StateNode(next, curr.moves + 1, curr));
        }
    }

    /**
     * is the initial board solvable? (see below)
     *
     * @param
     */
    public boolean isSolvable() {
        return this.canSlove;
    }

    /**
     * min number of moves to solve initial board
     *
     * @param
     */
    public int moves() {
        if (!isSolvable()) return -1;
        return this.seqList.size() - 1;
    }


    /**
     * sequence of boards in a shortest solution
     *
     * @param
     */
    public Iterable<Board> solution() {
        if (!isSolvable()) return null;
        return seqList;
    }

    /**
     * test client (see below)
     *
     * @param
     */
    public static void main(String[] args) {
        // create initial board from file
        In in = new In(args[0]);
        int n = in.readInt();
        int[][] tiles = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                tiles[i][j] = in.readInt();
        Board initial = new Board(tiles);
        // solve the puzzle
        Solver solver = new Solver(initial);
        // print solution to standard output
        if (!solver.isSolvable())
            StdOut.println("No solution possible");
        else {
            StdOut.println("Minimum number of moves = " + solver.moves());
            for (Board board : solver.solution())
                StdOut.println(board);
        }
    }

}
