/* *****************************************************************************
 *  Name:              mike meng
 *  Coursera User ID:  mingliang meng
 *  Last modified:     4/8/2020
 **************************************************************************** */

public class RightTriangle {
    public static void main(String[] args) {
        int a = Integer.parseInt(args[0]);
        int b = Integer.parseInt(args[1]);
        int c = Integer.parseInt(args[2]);
        boolean check1 = a > 0 && b > 0 && c > 0;
        boolean check2 = (a + b > c && b + c > a && c + a > b);
        boolean check3 = (a * a + b * b) == c * c || (a * a + c * c) == b * b
                || (c * c + b * b) == a * a;
        boolean right = check1 && check2 && check3;
        System.out.println(right);
    }
}
