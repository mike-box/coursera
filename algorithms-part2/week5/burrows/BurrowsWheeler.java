/* *****************************************************************************
 *  Name:mike meng
 *  Date:2020.3.15
 *  Description:created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.BinaryStdIn;
import edu.princeton.cs.algs4.BinaryStdOut;

import java.util.ArrayList;
import java.util.LinkedList;

public class BurrowsWheeler {
    private static final int EXTENDED_ASCII = 256;

    // apply Burrows-Wheeler transform,
    // reading from standard input and writing to standard output
    public static void transform() {
        String str = BinaryStdIn.readString();
        int row = 0;

        CircularSuffixArray sa = new CircularSuffixArray(str);
        for (int i = 0; i < sa.length(); ++i) {
            if (sa.index(i) == 0) {
                row = i;
                break;
            }
        }
        BinaryStdOut.write(row);
        for (int i = 0; i < sa.length(); ++i) {
            char c = str.charAt((sa.index(i) - 1 + str.length()) % str.length());
            BinaryStdOut.write(c);
        }
        BinaryStdOut.close();
    }

    // apply Burrows-Wheeler inverse transform,
    // reading from standard input and writing to standard output
    public static void inverseTransform() {
        int row = BinaryStdIn.readInt();
        String str = BinaryStdIn.readString();

        ArrayList<LinkedList<Integer>> alpha = new ArrayList<LinkedList<Integer>>();
        int[] next = new int[str.length()];
        int[] count = new int[EXTENDED_ASCII];

        for (int i = 0; i < EXTENDED_ASCII; ++i) alpha.add(new LinkedList<Integer>());
        for (int i = 0; i < str.length(); ++i) {
            alpha.get(str.charAt(i)).add(i);
            count[str.charAt(i)]++;
        }
        int curr = 0;
        for (int i = 0; i < str.length(); ++i) {
            while (count[curr] == 0) curr++;
            next[i] = alpha.get(curr).poll();
            count[curr]--;
        }
        for (int i = 0; i < str.length(); ++i) {
            BinaryStdOut.write(str.charAt(next[row]));
            row = next[row];
        }
        BinaryStdOut.close();
    }

    // if args[0] is "-", apply Burrows-Wheeler transform
    // if args[0] is "+", apply Burrows-Wheeler inverse transform
    public static void main(String[] args) {
        if (args[0].equals("-")) transform();
        else if (args[0].equals("+")) inverseTransform();
        else throw new IllegalArgumentException("Illegal command line argument");
    }
}
