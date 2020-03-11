/* *****************************************************************************
 *  Name:mike meng
 *  Date:2020.2.22
 *  Description:created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.FlowEdge;
import edu.princeton.cs.algs4.FlowNetwork;
import edu.princeton.cs.algs4.FordFulkerson;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdOut;

import java.util.HashMap;
import java.util.HashSet;

public class BaseballElimination {
    private final int[] wins;
    private final int[] loss;
    private final int[] left;
    private final int[][] games;
    private final String[] teamnames;
    private final HashMap<String, Integer> teams;

    public BaseballElimination(
            String filename) // create a baseball division from given filename in format specified
    {
        if (filename == null)
            throw new IllegalArgumentException();
        In in = new In(filename);
        int n = in.readInt();
        if (n <= 0)
            throw new IllegalArgumentException();

        // read all games data
        this.teams = new HashMap<String, Integer>();
        this.teamnames = new String[n];
        this.wins = new int[n];
        this.loss = new int[n];
        this.left = new int[n];
        this.games = new int[n][];
        for (int i = 0; i < n; ++i) {
            this.games[i] = new int[n];
            String name = in.readString();
            this.teamnames[i] = name;
            this.teams.put(name, i);
            this.wins[i] = in.readInt();
            this.loss[i] = in.readInt();
            this.left[i] = in.readInt();
            for (int j = 0; j < n; ++j) {
                this.games[i][j] = in.readInt();
            }
        }
    }

    private void assertTeam(String team) {
        if (!this.teams.containsKey(team))
            throw new IllegalArgumentException();
    }

    private Iterable<String> minCutOfElimination(String team) {
        assertTeam(team);
        int idx = this.teams.get(team);
        HashSet<String> subset = new HashSet<String>();
        int maxWin = this.wins[idx] + this.left[idx];
        int n = this.teams.size();

        // check trivial elimination
        for (int i = 0; i < this.teams.size(); ++i) {
            if (maxWin < this.wins[i]) subset.add(this.teamnames[i]);
        }
        if (!subset.isEmpty()) return subset;

        // check nontrivial Elimination
        int vertex = n * (n - 1) / 2 + n + 2;
        int s = vertex - 2;
        int t = vertex - 1;
        int remain = 0;
        int vertexId = n;
        FlowNetwork G = new FlowNetwork(vertex);
        HashMap<Integer, Stack<Integer>> vertexHash
                = new HashMap<Integer, Stack<Integer>>();

        for (int i = 0; i < n; ++i) {
            if (i == idx) continue;
            G.addEdge(new FlowEdge(i, t, maxWin - this.wins[i]));
            for (int j = 0; j < i; ++j) {
                if (j == idx) continue;
                G.addEdge(new FlowEdge(s, vertexId, this.games[i][j]));
                G.addEdge(new FlowEdge(vertexId, i, Double.POSITIVE_INFINITY));
                G.addEdge(new FlowEdge(vertexId, j, Double.POSITIVE_INFINITY));
                remain += this.games[i][j];
                Stack<Integer> tmp = new Stack<Integer>();
                tmp.push(i);
                tmp.push(j);
                vertexHash.put(vertexId, tmp);
                vertexId++;
            }
        }

        FordFulkerson ff = new FordFulkerson(G, s, t);
        if (ff.value() >= remain) return null;
        for (FlowEdge e : G.adj(s)) {
            if (ff.inCut(e.to())) {
                for (int x : vertexHash.get(e.to())) {
                    subset.add(this.teamnames[x]);
                }
            }
        }

        return subset;
    }

    public int numberOfTeams() // number of teams
    {
        return this.teams.size();
    }

    public Iterable<String> teams() // all teams
    {
        return this.teams.keySet();
    }

    public int wins(String team) // number of wins for given team
    {
        assertTeam(team);
        int idx = this.teams.get(team);
        return this.wins[idx];
    }

    public int losses(String team) // number of losses for given team
    {
        assertTeam(team);
        int idx = this.teams.get(team);
        return this.loss[idx];
    }

    public int remaining(String team) // number of remaining games for given team
    {
        assertTeam(team);
        int idx = this.teams.get(team);
        return this.left[idx];
    }

    public int against(String team1,
                       String team2) // number of remaining games between team1 and team2
    {
        assertTeam(team1);
        assertTeam(team2);
        int idx1 = this.teams.get(team1);
        int idx2 = this.teams.get(team2);
        return this.games[idx1][idx2];
    }

    public boolean isEliminated(String team) // is given team eliminated?
    {
        assertTeam(team);
        HashSet<String> res = (HashSet<String>) minCutOfElimination(team);
        return res != null;
    }

    public Iterable<String> certificateOfElimination(
            String team) // subset R of teams that eliminates given team; null if not eliminat
    {
        assertTeam(team);
        return minCutOfElimination(team);
    }

    public static void main(String[] args) {
        BaseballElimination division = new BaseballElimination(args[0]);
        for (String team : division.teams()) {
            if (division.isEliminated(team)) {
                StdOut.print(team + " is eliminated by the subset R = { ");
                for (String t : division.certificateOfElimination(team)) {
                    StdOut.print(t + " ");
                }
                StdOut.println("}");
            }
            else {
                StdOut.println(team + " is not eliminated");
            }
        }
    }
}
