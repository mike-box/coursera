/* *****************************************************************************
 *  Name: mengmingliang
 *  Date: 2020.1.10
 *  Description: created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;

import java.util.Iterator;

public class RandomizedQueue<Item> implements Iterable<Item> {
    private Item[] queue;
    private int currSz;
    private int current;

    // construct an empty randomized queue
    public RandomizedQueue() {
        queue = (Item[]) new Object[2];
        this.currSz = 2;
        this.current = 0;
    }

    private void resize(int capacity) {
        if (capacity <= 0) {
            throw new IllegalArgumentException();
        }
        Item[] arr = (Item[]) new Object[capacity];
        for (int i = 0; i < current; ++i) {
            arr[i] = queue[i];
        }
        currSz = capacity;
        queue = arr;
    }

    // is the randomized queue empty?
    public boolean isEmpty() {
        return this.current == 0;
    }

    // return the number of items on the randomized queue
    public int size() {
        return this.current;
    }

    // add the item
    public void enqueue(Item item) {
        if (item == null) {
            throw new IllegalArgumentException();
        }
        if (current >= currSz) {
            resize(currSz * 2);
        }
        this.queue[current++] = item;
    }

    // remove and return a random item
    public Item dequeue() {
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }
        int idx = StdRandom.uniform(this.current);
        Item val = queue[idx];
        queue[idx] = queue[--current];
        if (current <= (currSz / 4) && current >= 1) {
            resize(currSz / 2);
        }

        return val;
    }

    // return a random item (but do not remove it)
    public Item sample() {
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }
        int idx = StdRandom.uniform(this.current);
        return queue[idx];
    }

    // return an independent iterator over items in random order
    public Iterator<Item> iterator() {
        return new RandomizedQueueIterator();
    }

    private class RandomizedQueueIterator implements Iterator<Item> {
        private final int[] seq;
        private int currIdx;

        public RandomizedQueueIterator() {
            seq = new int[current];
            for (int i = 0; i < current; ++i) {
                seq[i] = i;
            }
            StdRandom.shuffle(seq);
            currIdx = 0;
        }

        public boolean hasNext() {
            if (currIdx == current) {
                return false;
            }
            return true;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }

        public Item next() {
            if (!hasNext()) {
                throw new java.util.NoSuchElementException();
            }
            Item val = queue[seq[currIdx++]];
            return val;
        }
    }

    // unit testing (required)
    public static void main(String[] args) {
        if (args.length < 2) {
            throw new IllegalArgumentException();
        }

        int n = Integer.parseInt(args[0]);
        int curr = 0;
        // input file
        In in = new In(args[1]);
        RandomizedQueue<String> rq = new RandomizedQueue<String>();

        while (!in.isEmpty() && curr < n) {
            rq.enqueue(in.readString());
            curr++;
        }
        while (!rq.isEmpty()) {
            StdOut.println(rq.dequeue());
        }
    }
}
