
/* *****************************************************************************
 *  Name:mingliang meng
 *  Date:2020.1.31
 *  Description: created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.Digraph;
import edu.princeton.cs.algs4.DirectedCycle;
import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

import java.util.ArrayList;
import java.util.HashMap;

public class WordNet {
    private final SAP sap;
    private final HashMap<String, ArrayList<Integer>> synId;
    private final ArrayList<String> synset;

    /**
     * constructor takes the name of the two input files
     *
     * @input file: prameter
     */
    public WordNet(String synsets, String hypernyms) {
        if (synsets == null || hypernyms == null)
            throw new IllegalArgumentException();

        In synIn = new In(synsets);
        In hypIn = new In(hypernyms);
        String[] synRecord = synIn.readAllLines();
        Digraph graph = new Digraph(synRecord.length);
        this.synset = new ArrayList<String>();
        this.synId = new HashMap<String, ArrayList<Integer>>();

        for (int i = 0; i < synRecord.length; i++) {
            String[] record = synRecord[i].split(",");
            int id = Integer.parseInt(record[0]);
            String[] syns = record[1].split(" ");
            for (int j = 0; j < syns.length; ++j) {
                if (this.synId.containsKey(syns[j])) {
                    ArrayList<Integer> list = this.synId.get(syns[j]);
                    list.add(id);
                    this.synId.put(syns[j], list);
                }
                else {
                    ArrayList<Integer> list = new ArrayList<Integer>();
                    list.add(id);
                    this.synId.put(syns[j], list);
                }
            }
            this.synset.add(record[1]);
        }

        while (!hypIn.isEmpty()) {
            String[] record = hypIn.readLine().split(",");
            int sid = Integer.parseInt(record[0]);
            for (int i = 1; i < record.length; i++) {
                int hid = Integer.parseInt(record[i]);
                graph.addEdge(sid, hid);
            }
        }

        if (!isRooted(graph))
            throw new IllegalArgumentException();
        this.sap = new SAP(graph);
    }

    /**
     * check the graph is DAG
     *
     * @Digraph: graph
     */
    private boolean isRooted(Digraph G) {
        int roots = 0;
        for (int i = 0; i < G.V(); ++i) {
            if (G.outdegree(i) == 0) roots++;
        }
        if (roots != 1) return false;
        DirectedCycle dag = new DirectedCycle(G);
        if (dag.hasCycle()) return false;
        return true;
    }

    /**
     * returns all WordNet nouns
     *
     * @Digraph: graph
     */
    public Iterable<String> nouns() {
        return this.synId.keySet();
    }

    /**
     * is the word a WordNet noun?
     *
     * @String: check word
     */
    public boolean isNoun(String word) {
        if (word == null) {
            throw new IllegalArgumentException();
        }
        return this.synId.containsKey(word);
    }

    /**
     * distance between nounA and nounB (defined below)
     *
     * @String: source & distination
     */
    public int distance(String nounA, String nounB) {
        if (!this.synId.containsKey(nounA) || !this.synId.containsKey(nounB)) {
            throw new IllegalArgumentException();
        }

        ArrayList<Integer> setA = this.synId.get(nounA);
        ArrayList<Integer> setB = this.synId.get(nounB);
        return this.sap.length(setA, setB);
    }

    /**
     * a synset (second field of synsets.txt) that is the common ancestor of nounA and nounB 
     * in a shortest ancestral path (defined below)
     *
     * @String: source & distination
     */
    public String sap(String nounA, String nounB) {
        if (!this.synId.containsKey(nounA) || !this.synId.containsKey(nounB)) {
            throw new IllegalArgumentException();
        }

        ArrayList<Integer> setA = this.synId.get(nounA);
        ArrayList<Integer> setB = this.synId.get(nounB);
        int ancestor = this.sap.ancestor(setA, setB);
        if (ancestor == -1) return null;
        return this.synset.get(ancestor);
    }

    // do unit testing of this class
    public static void main(String[] args) {
        WordNet net = new WordNet(args[0], args[1]);
        while (!StdIn.isEmpty()) {
            String nounA = StdIn.readString();
            String nounB = StdIn.readString();
            int length = net.distance(nounA, nounB);
            String ancestor = net.sap(nounA, nounB);
            StdOut.printf("length = %d, ancestor = %s\n", length, ancestor);
        }
    }
}
