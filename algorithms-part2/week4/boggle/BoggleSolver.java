/* *****************************************************************************
 *  Name:mike meng
 *  Date:2020.3.7
 *  Description:created by mike meng
 **************************************************************************** */

import java.util.HashSet;

public class BoggleSolver {
    // Initializes the data structure using the given array of strings as the dictionary.
    // (You can assume each word in the dictionary contains only the uppercase letters A through Z.)
    private final TrieNode trie;
    private final HashSet<String> valid;
    private boolean[][] visit;
    private int row;
    private int col;

    public BoggleSolver(String[] dictionary) {
        this.trie = new TrieNode();
        this.row = 0;
        this.col = 0;
        this.valid = new HashSet<String>();
        for (int i = 0; i < dictionary.length; ++i)
            insertTrie(this.trie, dictionary[i]);
    }

    private class TrieNode {
        public TrieNode[] next;
        public boolean isWord;
        public String val;

        public TrieNode() {
            this.next = new TrieNode[26];
            for (int i = 0; i < 26; ++i)
                this.next[i] = null;
            this.isWord = false;
            this.val = null;
        }
    }

    // check colum index is valid
    private boolean validColum(int y) {
        if (y < 0 || y >= this.col) return false;
        return true;
    }

    // check row index is valid
    private boolean validRow(int x) {
        if (x < 0 || x >= this.row) return false;
        return true;
    }

    // insert word into trie
    private boolean insertTrie(TrieNode root, String word) {
        if (root == null) return false;

        TrieNode node = this.trie;
        for (int i = 0; i < word.length(); ++i) {
            int idx = word.charAt(i) - 'A';
            if (node.next[idx] == null) node.next[idx] = new TrieNode();
            node = node.next[idx];
        }

        node.isWord = true;
        node.val = word;
        return true;
    }

    // search the word in the trie
    private boolean searchTrie(TrieNode root,String word){
        TrieNode node = root;
        for(int i = 0; i < word.length(); ++i){
            if(node.next[word.charAt(i)-'A'] == null) return false;
            node = node.next[word.charAt(i)-'A'];
        }
        return node.isWord;
    }

    // search every dice in the board
    private boolean searchBoard(TrieNode root, BoggleBoard board, int x, int y) {
        if (root == null || board == null) return false;
        if (!validRow(x) || !validColum(y)) return false;

        int[] dx = { -1, -1, -1, 1, 1, 1, 0, 0 };
        int[] dy = { 1, 0, -1, 1, 0, -1, -1, 1 };
        char key = board.getLetter(x, y);

        if (root.next[key - 'A'] == null) return false;
        root = root.next[key - 'A'];
        if (key == 'Q') {
            if (root.next['U' - 'A'] == null) return false;
            root = root.next['U' - 'A'];
        }
        if (root.isWord && root.val.length() >= 3) valid.add(root.val);
        for (int i = 0; i < 8; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!validRow(nx) || !validColum(ny)) continue;
            if (visit[nx][ny]) continue;
            visit[nx][ny] = true;
            searchBoard(root, board, nx, ny);
            visit[nx][ny] = false;
        }

        return true;
    }

    // Returns the set of all valid words in the given Boggle board, as an Iterable.
    public Iterable<String> getAllValidWords(BoggleBoard board) {
        this.row = board.rows();
        this.col = board.cols();
        this.visit = new boolean[this.row][];
        this.valid.clear();
        for (int i = 0; i < this.row; ++i)
            this.visit[i] = new boolean[this.col];
        for (int i = 0; i < this.row; ++i)
            for (int j = 0; j < this.col; ++j)
                this.visit[i][j] = false;
        for (int i = 0; i < this.row; ++i) {
            for (int j = 0; j < this.col; ++j) {
                visit[i][j] = true;
                searchBoard(this.trie, board, i, j);
                visit[i][j] = false;
            }
        }

        return valid;
    }

    // Returns the score of the given word if it is in the dictionary, zero otherwise.
    // (You can assume the word contains only the uppercase letters A through Z.)
    public int scoreOf(String word) {
        if(!searchTrie(this.trie,word)) return 0;
        
        int n = word.length();
        if(n < 3) return 0;
        if(n == 3 || n == 4) return 1;
        if(n == 5) return 2;
        if(n == 6) return 3;
        if(n == 7) return 5;

        return 11;
    }
}
