/* *****************************************************************************
 *  Name:              mike meng
 *  Coursera User ID:  mingliang meng
 *  Last modified:     4/8/2020
 **************************************************************************** */

public class CMYKtoRGB {
    public static void main(String[] args) {
        double c = Double.parseDouble(args[0]);
        double m = Double.parseDouble(args[1]);
        double y = Double.parseDouble(args[2]);
        double k = Double.parseDouble(args[3]);
        double w = 1 - k;
        int r = (int) Math.rint(255.0 * w * (1.0 - c));
        int g = (int) Math.rint(255.0 * w * (1 - m));
        int b = (int) Math.rint(255.0 * w * (1 - y));
        System.out.println("red   = " + r);
        System.out.println("green = " + g);
        System.out.println("blue  = " + b);
    }
}
