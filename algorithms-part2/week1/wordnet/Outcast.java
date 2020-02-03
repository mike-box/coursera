/* *****************************************************************************
 *  Name:mingliang meng
 *  Date:2020.2.1
 *  Description:created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

public class Outcast {
    private WordNet wordnet;

    /**
     * constructor takes a WordNet object
     *
     * @WordNet:
     */
    public Outcast(WordNet wordnet) {
        if (wordnet == null) {
            throw new IllegalArgumentException();
        }
        this.wordnet = wordnet;
    }

    /**
     * given an array of WordNet nouns, return an outcast
     *
     * @nouns: input string array
     */
    public String outcast(String[] nouns) {
        int maxdistance = 0;
        int maxIdx = 0;

        for (int i = 0; i < nouns.length; ++i) {
            int distance = 0;
            for (int j = 0; j < nouns.length; ++j) {
                distance += this.wordnet.distance(nouns[i], nouns[j]);
            }
            if (distance > maxdistance) {
                maxIdx = i;
                maxdistance = distance;
            }
        }

        return nouns[maxIdx];
    }

    // see test client below
    public static void main(String[] args) 
    {
        WordNet wordnet = new WordNet(args[0], args[1]);
        Outcast outcast = new Outcast(wordnet);
        for (int t = 2; t < args.length; t++) {
            In in = new In(args[t]);
            String[] nouns = in.readAllStrings();
            StdOut.println(args[t] + ": " + outcast.outcast(nouns));
        }
    }
}
