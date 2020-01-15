/* *****************************************************************************
 *  Name:mengmingliang
 *  Date:2020.1.9
 *  Description:created by mike meng,we will finish the home word.
 **************************************************************************** */

import edu.princeton.cs.algs4.StdIn;
import edu.princeton.cs.algs4.StdOut;

public class Permutation {
    public static void main(String[] args) {
        int n = Integer.parseInt(args[0]);
        RandomizedQueue<String> rq = new RandomizedQueue<String>();
        while (!StdIn.isEmpty()) {
            rq.enqueue(StdIn.readString());
        }
        while (n > 0) {
            StdOut.println(rq.dequeue());
            n--;
        }
    }
}
