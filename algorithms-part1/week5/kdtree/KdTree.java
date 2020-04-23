/* *****************************************************************************
 *  Name:mike meng  
 *  Date:2020.1.31
 *  Description:created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.Point2D;
import edu.princeton.cs.algs4.RectHV;
import edu.princeton.cs.algs4.Stack;
import edu.princeton.cs.algs4.StdDraw;

public class KdTree {
    private TreeNode tree;

    private class TreeNode {
        public Point2D val;
        public TreeNode left;
        public TreeNode right;
        public int count;

        public TreeNode(Point2D p) {
            this.val = p;
            this.left = null;
            this.right = null;
            this.count = 1;
        }
    }

    /**
     * construct an empty set of points
     *
     * @param
     */
    public KdTree() {
        this.tree = null;
    }

    /**
     * is the set empty?
     *
     * @param
     */
    public boolean isEmpty() {
        return this.tree == null;
    }

    /**
     * number of points in the set
     *
     * @param
     */
    public int size() {
        if (this.tree == null) return 0;
        return this.tree.count;
    }

    /**
     * insert point to the BST
     *
     * @root: root of the BST
     * @p: point
     * @X_MODE: x coodirate or y coodirate
     */
    private TreeNode insertTree(TreeNode root, Point2D p, boolean vertical) {
        if (root == null) return new TreeNode(p);
        if (root.val.equals(p)) return root;

        if (vertical) { // split x coordinate
            if (root.val.x() > p.x()) root.left = insertTree(root.left, p, false);
            else root.right = insertTree(root.right, p, false);
        }
        else { // split y coordinate
            if (root.val.y() > p.y()) root.left = insertTree(root.left, p, true);
            else root.right = insertTree(root.right, p, true);
        }

        root.count = 1;
        if (root.left != null) root.count += root.left.count;
        if (root.right != null) root.count += root.right.count;
        return root;
    }

    /**
     * add the point to the set (if it is not already in the set)
     *
     * @p: point
     */
    public void insert(Point2D p) {
        if (p == null)
            throw new IllegalArgumentException();

        this.tree = insertTree(this.tree, p, true);
    }

    /**
     * seach the tree, does the point in the BST
     *
     * @p: point
     */
    private boolean searchTree(TreeNode root, Point2D p, boolean vertical) {
        if (root == null) return false;
        if (root.val.equals(p)) return true;

        if (vertical) { // split x coordinate
            if (root.val.x() > p.x()) return searchTree(root.left, p, false);
            else return searchTree(root.right, p, false);
        }
        else { // split y coordinate
            if (root.val.y() > p.y()) return searchTree(root.left, p, true);
            else return searchTree(root.right, p, true);
        }
    }

    /**
     * does the set contain point p?
     *
     * @p: point
     */
    public boolean contains(Point2D p) {
        if (p == null)
            throw new IllegalArgumentException();
        return searchTree(this.tree, p, true);
    }

    /**
     * draw the BST tree split
     *
     * @p: point
     */
    private void treeDraw(TreeNode root, boolean vertical, RectHV rect) {
        if (root == null) return;
        // draw point
        StdDraw.setPenColor(StdDraw.BLACK);
        // StdDraw.setPenRadius(0.001);
        root.val.draw();

        if (vertical) { // split x coordinate
            StdDraw.setPenColor(StdDraw.RED);
            StdDraw.line(root.val.x(), rect.ymin(), root.val.x(), rect.ymax());
            RectHV left = new RectHV(rect.xmin(), rect.ymin(), root.val.x(), rect.ymax());
            RectHV right = new RectHV(root.val.x(), rect.ymin(), rect.xmax(), rect.ymax());
            treeDraw(root.left, false, left);
            treeDraw(root.right, false, right);
        }
        else { // split y coordinate
            StdDraw.setPenColor(StdDraw.BLUE);
            StdDraw.line(rect.xmin(), root.val.y(), rect.xmax(), root.val.y());
            RectHV buttom = new RectHV(rect.xmin(), rect.ymin(), rect.xmax(), root.val.y());
            RectHV top = new RectHV(rect.xmin(), root.val.y(), rect.xmax(), rect.ymax());
            treeDraw(root.left, true, buttom);
            treeDraw(root.right, true, top);
        }
    }

    /**
     * draw all points to standard draw
     *
     * @p: point
     */
    public void draw() {
        treeDraw(this.tree, true, new RectHV(0.0, 0.0, 1.0, 1.0));
    }

    /**
     * range search all the points in the retangle
     *
     * @p: point
     */
    private void rangeSearchTree(TreeNode root, RectHV curr, RectHV rect, Stack<Point2D> res,
                                 boolean vertical) {
        if (root == null) return;
        if (rect.contains(root.val)) res.push(root.val);

        RectHV left = null;
        RectHV right = null;
        if (vertical) { // search x coordinate
            left = new RectHV(curr.xmin(), curr.ymin(), root.val.x(), curr.ymax());
            right = new RectHV(root.val.x(), curr.ymin(), curr.xmax(), curr.ymax());
            
        }
        else { // search y coordinate
            left = new RectHV(curr.xmin(), curr.ymin(), curr.xmax(), root.val.y());
            right = new RectHV(curr.xmin(), root.val.y(), curr.xmax(), curr.ymax());
        }

        if (left.intersects(rect)) rangeSearchTree(root.left, left, rect, res, !vertical);
        if (right.intersects(rect)) rangeSearchTree(root.right, right, rect, res, !vertical);
    }

    /**
     * all points that are inside the rectangle (or on the boundary)
     *
     * @p: point
     */
    public Iterable<Point2D> range(
            RectHV rect) {
        if (rect == null)
            throw new IllegalArgumentException();
        Stack<Point2D> target = new Stack<Point2D>();
        rangeSearchTree(this.tree, new RectHV(0.0, 0.0, 1.0, 1.0), rect, target, true);
        return target;
    }

    /**
     * all points that are inside the rectangle (or on the boundary)
     *
     * @p: point
     */
    private Point2D nearestTree(TreeNode root, Point2D curr, RectHV rect, Point2D p,
                                boolean vertical) {
        if (root == null) return curr;
        if (root.val.distanceSquaredTo(p) < curr.distanceSquaredTo(p)) {
            curr = root.val;
        }

        RectHV left = null;
        RectHV right = null;
        if (vertical) { // search x coordinate
            left = new RectHV(rect.xmin(), rect.ymin(), root.val.x(), rect.ymax());
            right = new RectHV(root.val.x(), rect.ymin(), rect.xmax(), rect.ymax());
        }
        else { // search y coordinate
            left = new RectHV(rect.xmin(), rect.ymin(), rect.xmax(), root.val.y());
            right = new RectHV(rect.xmin(), root.val.y(), rect.xmax(), rect.ymax());
        }

        double subLeft = left.distanceSquaredTo(p);
        double subRight = right.distanceSquaredTo(p);
        if (subLeft < subRight) {
            if (subLeft < curr.distanceSquaredTo(p))
                curr = nearestTree(root.left, curr, left, p, !vertical);
            if (subRight < curr.distanceSquaredTo(p))
                curr = nearestTree(root.right, curr, right, p, !vertical);
        }
        else {
            if (subRight < curr.distanceSquaredTo(p))
                curr = nearestTree(root.right, curr, right, p, !vertical);
            if (subLeft < curr.distanceSquaredTo(p))
                curr = nearestTree(root.left, curr, left, p, !vertical);
        }

        return curr;
    }

    /**
     * a nearest neighbor in the set to point p; null if the set is empty
     *
     * @p: point
     */
    public Point2D nearest(Point2D p) {
        if (p == null)
            throw new IllegalArgumentException();
        if (this.tree == null) return null;
        RectHV rect = new RectHV(0.0, 0.0, 1.0, 1.0);
        return nearestTree(this.tree, this.tree.val, rect, p, true);
    }
}
