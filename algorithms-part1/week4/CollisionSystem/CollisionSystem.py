import random
import sys
import time
import pygame
import heapq
import math
from pygame.locals import *
from heapq import *

LIGHT = (100, 100, 100)
DARK = (200, 200, 200)      # 蛇的颜色
BLACK = (0, 0, 0)           # 网格线颜色
RED = (200, 30, 30)         # 红色，GAME OVER 的字体颜色
BGCOLOR = (40, 40, 60)      # 背景色
WIDTH = 800
HEIGHT = 600
NUMBER = 20

class Particle:
    def __init__(self):
        self.radius = 10
        self.rx = random.uniform(self.radius,WIDTH)
        self.ry = random.uniform(self.radius,HEIGHT)
        self.vx = random.uniform(-5,5)
        self.vy = random.uniform(-5,5)
        self.count = 0
        self.mass = 0.5
        self.color = RED
    
    def set_argment(self,inRx,inRy,inVx,inVy,inradius,inMass,inColor):
        self.rx = inRx
        self.ry = inRy
        self.vx = inVx
        self.vy = inVy
        self.count = 0
        self.radius = inradius
        self.mass = inMass
        self.color = inColor

    def move(self,dt):
        self.rx += (int)(self.vx*dt)
        self.ry += (int)(self.vy*dt)
    
    def get_count(self):
        return self.count
    
    def time_to_hit(self,that):
        if self.rx == that.rx and self.ry == that.ry:
            return float('inf')

        dx = that.rx - self.rx
        dy = that.ry - self.ry
        dvx = that.vx - self.vx
        dvy = that.vy - self.vy
        dvdr = dx * dvx + dy * dvy
        if dvdr > 0.0:
            return float('inf')

        dvdv = dvx * dvx + dvy * dvy
        if dvdv == 0.0:
            return float('inf')
        drdr = dx * dx + dy * dy
        sigma = self.radius + that.radius
        d = (dvdr * dvdr) - dvdv * (drdr - sigma * sigma)
        if d < 0.0: 
            return float('inf')
        
        time = -(dvdr + math.sqrt(d))/dvdv
        if time <= 0.2:
            return float('inf')

        return time

    
    def time_to_hit_verticalwall(self):
        if self.vx > 0:
            return (WIDTH - self.radius - self.rx)/self.vx
        elif self.vx < 0:
            return (self.radius - self.rx)/self.vx
        else:
            return float('inf')
    
    def time_to_hit_horizontalwall(self):
        if self.vy > 0:
            return (HEIGHT - self.radius - self.ry)/self.vy
        elif self.vy < 0:
            return (self.radius - self.ry)/self.vy
        else:
            return float('inf')
    
    def bounce_off(self,that):
        dx = that.rx - self.rx
        dy = that.ry - self.ry
        dvx = that.vx - self.vx
        dvy = that.vy - self.vy
        # dv dot dr
        dvdr = dx * dvx + dy * dvy 
        # distance between particle centers at collison            
        dist = self.radius + that.radius       

        # magnitude of normal force
        magnitude = 2 * self.mass * that.mass * dvdr / ((self.mass + that.mass) * dist)

        # normal force, and in x and y directions
        fx = magnitude * dx / dist
        fy = magnitude * dy / dist

        # update velocities according to normal force
        self.vx += fx / self.mass
        self.vy += fy / self.mass
        self.vx -= fx / that.mass
        self.vy -= fy / that.mass

        # update collision counts
        self.count += 1
        that.count += 1
    
    def bounce_off_verticalwall(self):
        self.vx = -self.vx
        self.count += 1
    
    def bounce_off_horizontalwall(self):
        self.vy = -self.vy
        self.count += 1
    
    def kinetic_energy(self):
        return 0.5*self.mass * (self.vx * self.vx + self.vy * self.vy)


class Event:
    def __init__(self,t,pa,pb,countA,countB):
        self.countA = countA
        self.countB = countB
        self.a = pa
        self.b = pb
        self.time = t
    
    def __gt__(self,other):
        return self.time > other.time

    def __ge__(self,other):
        return self.time >= other.time

    def __le__(self,other):
        return self.time <= other.time

    def __lt__(self,other):
        return self.time < other.time

class CollisionSystem:
    def __init__(self,particles):
        self.t = 0.0
        self.HZ = 0.1
        self.particles = []
        self.pq = []
        for p in particles:
            self.particles.append(p)
        
        #init game
        pygame.init()
        self.screen = pygame.display.set_mode((WIDTH,HEIGHT))
        pygame.display.set_caption('Collision System')
    
    def isValid(self,event):
        if event.a >= 0 and event.countA != self.particles[event.a].get_count():
            return False
        if event.b >= 0 and event.countB != self.particles[event.b].get_count():
            return False
        return True

    def predict(self,index,limit):
        if index < 0 or index >= len(self.particles):
            return
        
        for i in range(len(self.particles)):
            if i == index:
                continue
            dt = self.particles[index].time_to_hit(self.particles[i])
            print("hit to the ball:",dt)
            if self.t + dt <= limit:
                event = Event(self.t + dt,index,i,self.particles[index].get_count(), self.particles[i].get_count())
                heappush(self.pq,event)
        
        dtx = self.particles[index].time_to_hit_verticalwall()
        dty = self.particles[index].time_to_hit_horizontalwall()
        if dtx + self.t <= limit:
            event = Event(self.t + dtx,index,-1,self.particles[index].get_count(),0)
            heappush(self.pq,event)
        if dty + self.t <= limit:
            event = Event(self.t + dty,-1,index,0,self.particles[index].get_count())
            heappush(self.pq,event)

    def cycle_draw(self,particle):
        pygame.draw.circle(self.screen,particle.color,((int)(particle.rx),(int)(particle.ry)),(int)(particle.radius))

    def redraw(self,limit):
        self.screen.fill(DARK)
        for i in range(len(self.particles)):
            self.cycle_draw(self.particles[i])

        pygame.display.update()
        self.delay()
        if self.t < limit:
            event = Event(self.t + 1/self.HZ,-1,-1,0,0)
            heappush(self.pq,event)
    
    def delay(self):
        lasttime = time.time()
        while True:
            for event in pygame.event.get():
                if event.type == QUIT:
                    sys.exit()
            curTime = time.time()
            if curTime - lasttime > 0.05:
                break

    def simulate(self,limit):
        for i in range(len(self.particles)):
            self.predict(i,limit)
        event = Event(0,-1,-1,0,0)
        heappush(self.pq,event)

        while(True):
            curr = heappop(self.pq)
            print(curr.time,curr.a,curr.b)
            print("cost time =",curr.time - self.t)
            if self.isValid(curr) is not True:
                continue
            for i in range(len(self.particles)):
                self.particles[i].move(curr.time - self.t)
            
            self.t = curr.time
            px = curr.a
            py = curr.b
            if px >= 0 and py >= 0:
                self.particles[px].bounce_off(self.particles[py])
                print(self.particles[px].rx,self.particles[px].ry,self.particles[px].vx,self.particles[px].vy)
                print(self.particles[py].rx,self.particles[py].ry,self.particles[py].vx,self.particles[py].vy)
                print("next hit = ",self.particles[px].time_to_hit(self.particles[py]))
            elif px >= 0 and py < 0:
                self.particles[px].bounce_off_verticalwall()
            elif px < 0  and py >= 0:
                self.particles[py].bounce_off_horizontalwall()
            else:
                self.redraw(limit)
            
            self.predict(px,limit)
            self.predict(py,limit)
        
        
def main():
    particles = []
    for i in range(NUMBER):
        particles.append(Particle())
    cs = CollisionSystem(particles)
    cs.simulate(10000)

if __name__ == '__main__':
    main()
    
        


