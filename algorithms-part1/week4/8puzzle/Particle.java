/* *****************************************************************************
 *  Name: mike meng
 *  Date: 2020.1.19
 *  Description: created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdRandom;

import java.awt.Color;

public class Particle {
    private double rx, ry; // position
    private double vx, vy; // velocity
    private final double radius; // radius
    private double mass;
    private int count; // number of collisions
    private final Color color;    // color

    public Particle(double rx, double ry, double vx, double vy, double radius, double mass,
                    Color color) {
        this.rx = rx;
        this.ry = ry;
        this.vx = vx;
        this.vy = vy;
        this.radius = radius;
        this.mass = mass;
        this.color = color;
        this.count = 0;
    }

    public Particle() {
        this.rx = StdRandom.uniform(-1, 1);
        this.ry = StdRandom.uniform(-1, 1);
        this.vx = StdRandom.uniform(-0.05, 0.05);
        this.vy = StdRandom.uniform(-0.05, 0.05);
        this.radius = StdRandom.uniform(0.01, 0.03);
        this.mass = StdRandom.uniform(0.1, 0.5);
        this.color = Color.BLACK;
        this.count = 0;
    }

    public int getCount() {
        return this.count;
    }

    public void move(double dt) {
        rx = rx + vx * dt;
        ry = ry + vy * dt;
    }

    public void draw() {
        StdDraw.setPenColor(this.color);
        StdDraw.filledCircle(rx, ry, radius);
    }

    public double timeToHit(Particle that) {
        if (this == that) return Double.POSITIVE_INFINITY;
        double dx = that.rx - this.rx, dy = that.ry - this.ry;
        double dvx = that.vx - this.vx;
        double dvy = that.vy - this.vy;
        double dvdr = dx * dvx + dy * dvy;
        if (dvdr > 0) return Double.POSITIVE_INFINITY;
        double dvdv = dvx * dvx + dvy * dvy;
        double drdr = dx * dx + dy * dy;
        double sigma = this.radius + that.radius;
        double d = (dvdr * dvdr) - dvdv * (drdr - sigma * sigma);
        if (d < 0) return Double.POSITIVE_INFINITY;
        return -(dvdr + Math.sqrt(d)) / dvdv;
    }

    public double timeToHitVerticalWall() {
        if (this.vx > 0) return (1.0 - rx + this.radius) / vx;
        else if (this.vx < 0) return (-1.0 - rx + this.radius) / vx;
        else return Double.POSITIVE_INFINITY;
    }

    public double timeToHitHorizontalWall() {
        if (this.vy > 0) return (1.0 - ry - this.radius) / vy;
        else if (this.vy < 0) return (-1.0 - ry + this.radius) / vy;
        else return Double.POSITIVE_INFINITY;
    }

    public void bounceOff(Particle that) {
        double dx = that.rx - this.rx, dy = that.ry - this.ry;
        double dvx = that.vx - this.vx, dvy = that.vy - this.vy;
        double dvdr = dx * dvx + dy * dvy;
        double dist = this.radius + that.radius;
        double J = 2 * this.mass * that.mass * dvdr / ((this.mass + that.mass) * dist);
        double Jx = J * dx / dist;
        double Jy = J * dy / dist;
        this.vx += Jx / this.mass;
        this.vy += Jy / this.mass;
        that.vx -= Jx / that.mass;
        that.vy -= Jy / that.mass;
        this.count++;
        that.count++;
    }

    public void bounceOffVerticalWall() {
        this.vx = -this.vx;
        this.count++;
    }

    public void bounceOffHorizontalWall() {
        this.vy = -this.vy;
        this.count++;
    }

    public double kineticEnergy() {
        return 0.5 * this.mass * (this.vx * this.vx + this.vy * this.vy);
    }

    public static void main(String[] args) {

    }
}
