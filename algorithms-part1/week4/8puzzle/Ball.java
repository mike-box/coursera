/* *****************************************************************************
 *  Name:mike meng
 *  Date:2020.1.17
 *  Description: add by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdRandom;

public class Ball {
    private double rx, ry; // position
    private double vx, vy; // velocity
    private double mass;
    private final double radius; // radius
    private int count; // number of collisions


    public Ball() {
        this.rx = StdRandom.uniform(0.02, 0.05);
        this.ry = StdRandom.uniform(0.02, 0.05);
        this.vx = StdRandom.uniform(0.01, 0.05);
        this.vy = StdRandom.uniform(0.01, 0.05);
        this.radius = StdRandom.uniform(0.01, 0.05);
    }

    public void move(double dt) {
        if ((rx + vx * dt < radius) || (rx + vx * dt > 1.0 - radius)) {
            vx = -vx;
        }
        if ((ry + vy * dt < radius) || (ry + vy * dt > 1.0 - radius)) {
            vy = -vy;
        }
        rx = rx + vx * dt;
        ry = ry + vy * dt;
    }

    public void draw() {
        StdDraw.filledCircle(rx, ry, radius);
    }


    public static void main(String[] args) {
        StdDraw.clear(StdDraw.BLACK);
        // draw the bullseye
        StdDraw.setPenColor(StdDraw.BOOK_BLUE);
        StdDraw.filledCircle(0.1, 0.1, 0.3);

    }
}
