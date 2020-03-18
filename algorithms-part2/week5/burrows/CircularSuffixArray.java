/* *****************************************************************************
 *  Name:mike meng
 *  Date:2020.3.15
 *  Description:created by mike meng
 **************************************************************************** */

public class CircularSuffixArray {
    private final int[] suffix;
    private final String str;

    // circular suffix array of s
    public CircularSuffixArray(String s) {
        if (s == null)
            throw new IllegalArgumentException("invalid index");
        this.suffix = new int[s.length()];
        this.str = s;
        for (int i = 0; i < s.length(); ++i) this.suffix[i] = i;
        sort(0, s.length() - 1, 0);
    }

    private void exch(int[] arr, int lx, int rx) {
        int t = arr[lx];
        arr[lx] = arr[rx];
        arr[rx] = t;
    }

    private void sort(int lo, int hi, int d) {
        if (lo >= hi) return;
        if (d >= length()) return;
        int lt = lo, gt = hi;
        int v = str.charAt((suffix[lo] + d) % length());
        int i = lo + 1;

        while (i <= gt) {
            int t = str.charAt((suffix[i] + d) % length());
            if (t < v) exch(suffix, lt++, i++);
            else if (t > v) exch(suffix, i, gt--);
            else i++;
        }
        sort(lo, lt - 1, d);
        sort(lt, gt, d + 1);
        sort(gt + 1, hi, d);
    }

    // check valid index
    private boolean assertIndex(int i) {
        if (i < 0 || i >= length())
            throw new IllegalArgumentException("invalid index");
        return true;
    }

    // length of s
    public int length() {
        return this.suffix.length;
    }

    // returns index of ith sorted suffix
    public int index(int i) {
        assertIndex(i);
        return this.suffix[i];
    }
}
