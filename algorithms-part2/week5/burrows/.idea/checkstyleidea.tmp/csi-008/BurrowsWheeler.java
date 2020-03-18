/* *****************************************************************************
 *  Name:mike meng
 *  Date:2020.3.15
 *  Description:created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.BinaryStdIn;
import edu.princeton.cs.algs4.BinaryStdOut;

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
        int[] next = new int[str.length()];
        int[] count = new int[EXTENDED_ASCII + 1];

        for (int i = 0; i < str.length(); ++i) {
            count[str.charAt(i)+]++;
        }
        for (int i = 0; i < EXTENDED_ASCII; ++i) {
            count[i + 1] += count[i];
        }
        for (int i = 0; i < str.length(); i++) {
            next[count[str.charAt(i)]++] = i;
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
