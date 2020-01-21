/* *****************************************************************************
 *  Name: mingliang meng
 *  Date: 2020.1.14
 *  Description: created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.StdDraw;
import edu.princeton.cs.algs4.StdOut;

import java.util.ArrayList;
import java.util.Arrays;

public class BruteCollinearPoints {
    private ArrayList<LineSegment> segList;

    public BruteCollinearPoints(Point[] points) // finds all line segments containing 4 points
    {
        if (points == null) {
            throw new IllegalArgumentException();
        }
        for (int i = 0; i < points.length; ++i) {
            if (points[i] == null) {
                throw new IllegalArgumentException();
            }
        }
        Arrays.sort(points);
        for (int i = 1; i < points.length; ++i) {
            if (points[i].compareTo(points[i - 1]) == 0) {
                throw new IllegalArgumentException();
            }
        }

        segList = new ArrayList<LineSegment>();
        for (int i = 0; i < points.length - 3; ++i) {
            for (int j = i + 1; j < points.length - 2; ++j) {
                double slope1 = points[i].slopeTo(points[j]);
                for (int m = j + 1; m < points.length - 1; ++m) {
                    double slope2 = points[j].slopeTo(points[m]);
                    if (slope1 != slope2) continue;
                    for (int n = m + 1; n < points.length; ++n) {
                        double slope3 = points[m].slopeTo(points[n]);
                        if (slope3 != slope1) continue;
                        LineSegment line = new LineSegment(points[i], points[n]);
                        segList.add(line);
                    }
                }
            }
        }
    }

    public int numberOfSegments() // the number of line segments
    {
        return segList.size();
    }

    public LineSegment[] segments() // the line segments
    {
        LineSegment[] res = new LineSegment[segList.size()];
        for (int i = 0; i < segList.size(); ++i) {
            res[i] = segList.get(i);
        }
        return res;
    }

    public static void main(String[] args) {
        In in = new In(args[0]);
        int n = in.readInt();
        Point[] points = new Point[n];
        for (int i = 0; i < n; i++) {
            int x = in.readInt();
            int y = in.readInt();
            points[i] = new Point(x, y);
        }
        // draw the points
        StdDraw.enableDoubleBuffering();
        StdDraw.setXscale(0, 32768);
        StdDraw.setYscale(0, 32768);
        StdDraw.filledCircle(10, 10, 0.1);
        for (Point p : points) {
            p.draw();
        }
        StdDraw.show();
        // print and draw the line segments
        FastCollinearPoints collinear = new FastCollinearPoints(points);
        for (LineSegment segment : collinear.segments()) {
            StdOut.println(segment);
            segment.draw();
        }
        StdDraw.show();
    }
}
