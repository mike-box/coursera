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

public class FastCollinearPoints {
    private ArrayList<LineSegment> segList;

    public FastCollinearPoints(
            Point[] points) // finds all line segments containing 4 or more points
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

        Point[] tmpArr = new Point[points.length - 1];
        segList = new ArrayList<LineSegment>();

        for (int i = 0; i < points.length; ++i) {
            int idx = 0;
            for (int j = 0; j < points.length; ++j) {
                if (i == j) continue;
                tmpArr[idx++] = points[j];
            }

            Arrays.sort(tmpArr, 0, tmpArr.length, points[i].slopeOrder());
            int l = 0;
            for (int j = 0; j < tmpArr.length - 1; ++j) {
                double s1 = tmpArr[j].slopeTo(points[i]);
                double s2 = tmpArr[j + 1].slopeTo(points[i]);
                if (s1 != s2) {
                    if (j - l >= 2 && points[i].compareTo(tmpArr[l]) < 0) {
                        segList.add(new LineSegment(points[i], tmpArr[j]));
                    }
                    l = j + 1;
                    continue;
                }
            }
            if (tmpArr.length - l >= 3 && points[i].compareTo(tmpArr[l]) < 0) {
                segList.add(new LineSegment(points[i], tmpArr[tmpArr.length - 1]));
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
