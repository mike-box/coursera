/* *****************************************************************************
 *  Name:mengmingliang
 *  Date:2020.1.9
 *  Description:created by mike meng,we will finish the home word.
 **************************************************************************** */

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdOut;

import java.util.Iterator;

public class Deque<Item> implements Iterable<Item> {
    private ListNode head = null;
    private ListNode tail = null;
    private int queSz = 0;

    private class ListNode {
        private Item val;
        private ListNode prev;
        private ListNode next;
    }

    // construct an empty deque
    public Deque() {
        this.queSz = 0;
        this.head = null;
        this.tail = null;
    }

    // is the deque empty?
    public boolean isEmpty() {
        return this.queSz == 0;
    }

    // return the number of items on the deque
    public int size() {
        return this.queSz;
    }

    // add the item to the front
    public void addFirst(Item item) {
        if (item == null) {
            throw new IllegalArgumentException();
        }

        ListNode node = new ListNode();
        node.val = item;
        node.prev = null;
        node.next = null;
        if (this.head == null) {
            head = node;
            tail = node;
        }
        else {
            node.next = head;
            head.prev = node;
            head = node;
        }

        this.queSz++;
    }

    // add the item to the back
    public void addLast(Item item) {
        if (item == null) {
            throw new IllegalArgumentException();
        }

        ListNode node = new ListNode();
        node.val = item;
        node.prev = null;
        node.next = null;
        if (this.head == null || this.tail == null) {
            head = node;
            tail = node;
        }
        else {
            node.prev = tail;
            tail.next = node;
            tail = node;
        }

        this.queSz++;
    }

    // remove and return the item from the front
    public Item removeFirst() {
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }

        Item val = this.head.val;
        head = head.next;
        this.queSz--;
        if (head != null) {
            head.prev = null;
        }
        else {
            head = null;
            tail = null;
        }

        return val;
    }

    // remove and return the item from the back
    public Item removeLast() {
        if (isEmpty()) {
            throw new java.util.NoSuchElementException();
        }

        Item val = this.tail.val;
        tail = tail.prev;
        this.queSz--;
        if (tail != null) {
            tail.next = null;
        }
        else {
            tail = null;
            head = null;
        }

        return val;
    }

    // return an iterator over items in order from front to back
    public Iterator<Item> iterator() {
        return new DequeIterator();
    }

    private class DequeIterator implements Iterator<Item> {
        private ListNode current = head;

        public boolean hasNext() {
            return current != null;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }

        public Item next() {
            if (!hasNext()) {
                throw new java.util.NoSuchElementException();
            }
            Item val = current.val;
            current = current.next;
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
        Deque<String> dq = new Deque<String>();

        while (!in.isEmpty() && curr < n) {
            dq.addFirst(in.readString());
            curr++;
        }
        while (!dq.isEmpty()) {
            StdOut.println(dq.size());
            if (!dq.isEmpty()) {
                StdOut.println(dq.removeFirst());
            }
            if (!dq.isEmpty()) {
                StdOut.println(dq.removeLast());
            }
        }
    }

}
