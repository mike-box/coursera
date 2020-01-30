/* *****************************************************************************
 *  Name:mingliang meng
 *  Date:2020.1.25
 *  Description: created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.Stack;

import java.util.TreeSet;

public class PointSET {
    private final TreeSet<Point2D> points;

    public PointSET() // construct an empty set of points
    {
        this.points = new TreeSet<Point2D>();
    }

    public boolean isEmpty() // is the set empty?
    {
        return this.points.isEmpty();
    }

    public int size() // number of points in the set
    {
        return this.points.size();
    }

    public void insert(Point2D p) // add the point to the set (if it is not already in the set)
    {
        if (p == null)
            throw new IllegalArgumentException();
        this.points.add(p);
    }

    public boolean contains(Point2D p) // does the set contain point p?
    {
        if (p == null)
            throw new IllegalArgumentException();
        return points.contains(p);
    }

    public void draw() // draw all points to standard draw
    {
        for (Point2D p : points) {
            p.draw();
        }
    }

    public Iterable<Point2D> range(
            RectHV rect) // all points that are inside the rectangle (or on the boundary)
    {
        if (rect == null)
            throw new IllegalArgumentException();

        Stack<Point2D> res = new Stack<Point2D>();
        for (Point2D p : points) {
            if (rect.contains(p)) res.push(p);
        }

        return res;
    }

    public Point2D nearest(
            Point2D p) // a nearest neighbor in the set to point p; null if the set is empty
    {
        if (p == null)
            throw new IllegalArgumentException();
        if (points.isEmpty()) return null;

        double dist = Double.POSITIVE_INFINITY;
        Point2D x = null;
        for (Point2D curr : points) {
            if (curr.distanceSquaredTo(p) < dist) {
                dist = curr.distanceSquaredTo(p);
                x = curr;
            }
        }

        return x;
    }
}
