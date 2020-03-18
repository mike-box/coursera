/* *****************************************************************************
 *  Name:mike meng
 *  Date:2020.3.15
 *  Description:created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.BinaryStdIn;
import edu.princeton.cs.algs4.BinaryStdOut;

public class MoveToFront {
    private static final int EXTENDED_ASCII = 256;

    // apply move-to-front encoding, reading from standard input and writing to standard output
    public static void encode() {
        // initial alpha sequence table
        char[] alpha = new char[EXTENDED_ASCII];
        String str = BinaryStdIn.readString();
        for (int i = 0; i < EXTENDED_ASCII; ++i) alpha[i] = (char) (i);
        for (int i = 0; i < str.length(); ++i) {
            char x, prev;
            // exchange
            for (x = 0, prev = alpha[0]; alpha[x] != str.charAt(i); x++) {
                char t = alpha[x];
                alpha[x] = prev;
                prev = t;
            }
            BinaryStdOut.write(x);
            alpha[0] = alpha[x];
            alpha[x] = prev;
        }
        BinaryStdOut.close();
    }


    // apply move-to-front decoding, reading from standard input and writing to standard output
    public static void decode() {
        char[] alpha = new char[EXTENDED_ASCII];
        String str = BinaryStdIn.readString();
        for (int i = 0; i < EXTENDED_ASCII; ++i) alpha[i] = (char) i;
        for (int i = 0; i < str.length(); ++i) {
            char key = alpha[str.charAt(i)];
            for (int j = str.charAt(i) - 1; j >= 0; --j) alpha[j + 1] = alpha[j];
            BinaryStdOut.write(key);
            alpha[0] = key;
        }
        BinaryStdOut.close();
    }

    // if args[0] is "-", apply move-to-front encoding
    // if args[0] is "+", apply move-to-front decoding
    public static void main(String[] args) {
        if (args[0].equals("-")) encode();
        else if (args[0].equals("+")) decode();
        else throw new IllegalArgumentException("Illegal command line argument");
    }
}
