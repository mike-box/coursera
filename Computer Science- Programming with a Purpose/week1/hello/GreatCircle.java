/* *****************************************************************************
 *  Name:              mike meng
 *  Coursera User ID:  mingliang meng
 *  Last modified:     4/8/2020
 **************************************************************************** */

public class GreatCircle {
    public static void main(String[] args) {
        double r = 6371.0;
        double x1 = Math.toRadians(Double.parseDouble(args[0]));
        double y1 = Math.toRadians(Double.parseDouble(args[1]));
        double x2 = Math.toRadians(Double.parseDouble(args[2]));
        double y2 = Math.toRadians(Double.parseDouble(args[3]));
        double dist = 2 * r * Math.asin(Math.sqrt(
                Math.pow(Math.sin((x2 - x1) / 2), 2) +
                        Math.cos(x1) * Math.cos(x2) * Math.pow(Math.sin((y2 - y1) / 2), 2)));
        System.out.println(Double.toString(dist) + " kilometers");
    }
}
