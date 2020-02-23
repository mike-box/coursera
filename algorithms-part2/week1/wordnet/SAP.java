/* *****************************************************************************
 *  Name:mingliang meng
 *  Date:2020.2.1
 *  Description:created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.Queue;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

public class SAP {
    private final Digraph graph;

    /**
     * constructor takes a digraph (not necessarily a DAG)
     *
     * @Digraph: prameter
     */
    public SAP(Digraph G) {
        if (G == null)
            throw new IllegalArgumentException();
        this.graph = new Digraph(G);
    }

    /**
     * shortest path BFS
     *
     * @Iterable<Integer>: source
     */
    private ArrayList<Integer> shortestAncestral(Iterable<Integer> v, Iterable<Integer> w) {
        HashMap<Integer, Integer> distance = new HashMap<Integer, Integer>();
        HashSet<Integer> visit = new HashSet<Integer>();
        Queue<Integer> qu = new Queue<Integer>();
        ArrayList<Integer> res = new ArrayList<Integer>();

        // BFS
        int step = 1;
        int mindistance = this.graph.V();
        int commonancestor = -1;

        for (Integer vx : v) {
            distance.put(vx, 0);
            qu.enqueue(vx);
        }
        while (!qu.isEmpty()) {
            int sz = qu.size();
            for (int i = 0; i < sz; ++i) {
                int curr = qu.dequeue();
                for (Integer neg : this.graph.adj(curr)) {
                    if (distance.containsKey(neg)) continue;
                    distance.put(neg, step);
                    qu.enqueue(neg);
                }
            }
            step++;
        }

        step = 0;
        for (Integer wx : w) {
            qu.enqueue(wx);
        }
        while (!qu.isEmpty()) {
            int sz = qu.size();
            for (int i = 0; i < sz; ++i) {
                int curr = qu.dequeue();
                visit.add(curr);
                if (distance.containsKey(curr) && distance.get(curr) + step < mindistance) {
                    mindistance = distance.get(curr) + step;
                    commonancestor = curr;
                }
                for (Integer neg : this.graph.adj(curr)) {
                    if (visit.contains(neg)) continue;
                    qu.enqueue(neg);
                }
            }
            step++;
        }

        if (commonancestor == -1) {
            mindistance = -1;
        }
        res.add(mindistance);
        res.add(commonancestor);
        return res;
    }

    private boolean assertInt(int v){
        if(v < 0 || v >= this.graph.V()) throw new IllegalArgumentException();
    }
    
    private boolean assertSet(Iterable<Integer> v){
        if (v == null || w == null) throw new IllegalArgumentException();
        for(Integer vx : v){
            assertInt(vx);
        }
    }
    /**
     * length of shortest ancestral path between v and w; -1 if no such path
     *
     * @int: source
     */
    public int length(int v, int w) {
        assertInt(v);
        assertInt(w);
        if (v == w) return 0;

        ArrayList<Integer> setv = new ArrayList<Integer>();
        ArrayList<Integer> setw = new ArrayList<Integer>();
        setv.add(v);
        setw.add(w);
        return this.shortestAncestral(setv, setw).get(0);
    }

    
    /**
     * a common ancestor of v and w that participates in a shortest ancestral path; -1 if no such path
     *
     * @int:(v,w) source
     */
    public int ancestor(int v, int w) {
        assertInt(v);
        assertInt(w);
        if (v == w) return v;
        
        ArrayList<Integer> setv = new ArrayList<Integer>();
        ArrayList<Integer> setw = new ArrayList<Integer>();
        setv.add(v);
        setw.add(w);
        return this.shortestAncestral(setv, setw).get(1);
    }

    /**
     * length of shortest ancestral path between any vertex in v and any vertex in w; -1 if no such path
     *
     * @Iterable:(v,w) source
     */
    public int length(Iterable<Integer> v, Iterable<Integer> w) {
        assertSet(v);
        assertSet(w);
        return this.shortestAncestral(v, w).get(0);
    }

    /**
     * a common ancestor that participates in shortest ancestral path; -1 if no such path
     *
     * @Iterable:(v,w) source
     */
    public int ancestor(Iterable<Integer> v, Iterable<Integer> w) {
        assertSet(v);
        assertSet(w);
        return this.shortestAncestral(v, w).get(1);
    }

    // do unit testing of this class
    public static void main(String[] args) {
        In in = new In(args[0]);
        Digraph G = new Digraph(in);
        SAP sap = new SAP(G);
        while (!StdIn.isEmpty()) {
            int v = StdIn.readInt();
            int w = StdIn.readInt();
            int length = sap.length(v, w);
            int ancestor = sap.ancestor(v, w);
            StdOut.printf("length = %d, ancestor = %d\n", length, ancestor);
        }
    }
}
