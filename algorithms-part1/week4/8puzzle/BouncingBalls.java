/* *****************************************************************************
 *  Name:
 *  Date:
 *  Description:
 **************************************************************************** */

import edu.princeton.cs.algs4.StdDraw;

public class BouncingBalls {
    public static void main(String[] args) {
        StdDraw.clear(StdDraw.BLACK);
        StdDraw.setPenColor(StdDraw.BOOK_BLUE);

        int n = Integer.parseInt(args[0]);
        Ball[] balls = new Ball[n];
        for (int i = 0; i < n; i++)
            balls[i] = new Ball();
        while (true) {
            StdDraw.clear(StdDraw.BLACK);
            StdDraw.setPenColor(StdDraw.BOOK_BLUE);
            for (int i = 0; i < n; i++) {
                balls[i].move(0.1);
                balls[i].draw();
            }
            StdDraw.show();
            StdDraw.pause(50);
        }
    }
}
