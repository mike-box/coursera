/* *****************************************************************************
 *  Name:mike meng
 *  Date:2020.1.19
 *  Description:created by mike meng
 **************************************************************************** */

import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.StdDraw;

public class CollisionSystem {
    private MinPQ<Event> pq; // the priority queue
    private double t = 0.0; // simulation clock time
    private final double HZ = 0.5;
    private Particle[] particles; // the array of particles
    private int particleSz;

    public CollisionSystem(Particle[] particles) {
        if (particles == null) {
            throw new IllegalArgumentException();
        }

        this.particleSz = particles.length;
        this.particles = particles;
    }

    private class Event implements Comparable<Event> {
        private double time; // time of event
        private Particle a, b; // particles involved in event
        private int countA, countB; // collision counts for a and b

        public Event(double t, Particle a, Particle b) {
            this.time = t;
            this.a = a;
            this.b = b;
            this.countA = 0;
            this.countB = 0;
            if (a != null) this.countA = a.getCount();
            if (b != null) this.countB = b.getCount();
        }

        public int compareTo(Event that) {
            return Double.compare(this.time, that.time);
        }

        public boolean isValid() {
            if (a != null && a.getCount() != this.countA) return false;
            if (b != null && b.getCount() != this.countB) return false;
            return true;
        }
    }

    private void predict(Particle a) {
        if (a == null) return;

        for (int i = 0; i < this.particleSz; i++) {
            double dt = a.timeToHit(particles[i]);
            pq.insert(new Event(t + dt, a, particles[i]));
        }
        pq.insert(new Event(t + a.timeToHitVerticalWall(), a, null));
        pq.insert(new Event(t + a.timeToHitHorizontalWall(), null, a));
    }

    private void redraw() {
        StdDraw.clear();
        for (int i = 0; i < this.particleSz; ++i) {
            this.particles[i].draw();
        }
        StdDraw.show();
        StdDraw.pause(5);
        pq.insert(new Event(this.t + 1 / HZ, null, null));
    }

    public void simulate() { /* see next slide */
        this.pq = new MinPQ<Event>();
        for (int i = 0; i < this.particleSz; ++i) {
            this.predict(particles[i]);
        }
        pq.insert(new Event(0, null, null));

        while (true) {
            Event event = pq.delMin();
            if (!event.isValid()) continue;
            Particle particleA = event.a;
            Particle particleB = event.b;
            //StdOut.println(event.time);
            //update all particles & time clock
            for (int i = 0; i < this.particleSz; ++i) {
                this.particles[i].move(event.time - this.t);
            }
            this.t = event.time;

            //check collison
            if (particleA != null && particleB != null) particleA.bounceOff(particleB);
            else if (particleA != null && particleB == null) particleA.bounceOffVerticalWall();
            else if (particleA == null && particleB != null) particleB.bounceOffHorizontalWall();
            else this.redraw();
            this.predict(particleA);
            this.predict(particleB);
        }
    }

    public static void main(String[] args) {
        StdDraw.clear(StdDraw.BLACK);
        StdDraw.setPenColor(StdDraw.BOOK_BLUE);
        StdDraw.setScale(-1, 1);

        int n = Integer.parseInt(args[0]);
        Particle[] arrays = new Particle[n];
        for (int i = 0; i < n; i++)
            arrays[i] = new Particle();

        CollisionSystem cs = new CollisionSystem(arrays);
        cs.simulate();
    }
}
