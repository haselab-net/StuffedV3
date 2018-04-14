using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Robokey {
    public class Vec2d {
        public double x;
        public double y;

        public Vec2d() {
            this.x = 0.0f;
            this.y = 0.0f;
        }

        public Vec2d(double x, double y) {
            this.x = x;
            this.y = y;
        }

        public double this[int i] {
            get {
                double[] a = { x, y };
                try {
                    return a[i];
                } catch (IndexOutOfRangeException e) {
                    Console.WriteLine(e.Message);
                    throw new ArgumentOutOfRangeException("index parameter out of range");
                }
            }
            set {
                if (i == 0) { x = value; }
                else if (i == 1) { y = value; }
                else { throw new ArgumentOutOfRangeException("index parameter out of range"); }
            }
        }

        public static Vec2d operator +(Vec2d u, Vec2d v) {
            return new Vec2d(u.x + v.x, u.y + v.y);
        }

        public static Vec2d operator -(Vec2d u, Vec2d v) {
            return new Vec2d(u.x - v.x, u.y - v.y);
        }

        public static Vec2d operator *(double c, Vec2d v) {
            return new Vec2d(c * v.x, c * v.y);
        }

        public static Vec2d operator *(Vec2d v, double c) {
            return new Vec2d(c * v.x, c * v.y);
        }

        // Method for dot product (scalar product)
        public static double operator *(Vec2d u, Vec2d v) {
            return u.x * v.x + u.y * v.y;
        }

        public static Vec2d operator /(double c, Vec2d v) {
            return new Vec2d(v.x / c, v.y / c);
        }

        public static double operator %(Vec2d u, Vec2d v) {
            return u.x * v.y - u.y * v.x;
        }

        public double Norm() {
            return Math.Sqrt(x * x + y * y);
        }

        public Vec2d Unit() {
            double norm = this.Norm();
            return new Vec2d(this.x / norm, this.y / norm);
        }

        public Vec2d Clone() {
            return new Vec2d(this.x, this.y);
        }

        public string getString() {
            string s = "(" + this.x + " " + this.y + ")";
            return s;
        }

        public new string ToString() {
            return getString();
        }
    }
}
