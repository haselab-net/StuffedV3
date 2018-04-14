using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Robokey {
    public class Vec3d {
        public double x;
        public double y;
        public double z;


        public Vec3d() {
            this.x = 0.0f;
            this.y = 0.0f;
            this.z = 0.0f;
        }

        public Vec3d(double x, double y, double z) {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public double this[int i] {
            get {
                double[] a = { x, y, z };
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
                else if (i == 2) { z = value; }
                else { throw new ArgumentOutOfRangeException("index parameter out of range"); }
            }
        }

        public static Vec3d operator +(Vec3d u, Vec3d v) {
            return new Vec3d(u.x + v.x, u.y + v.y, u.z + v.z);
        }

        public static Vec3d operator -(Vec3d u, Vec3d v) {
            return new Vec3d(u.x - v.x, u.y - v.y, u.z - v.z);
        }

        // Method for multiplying vector by scalar
        public static Vec3d operator *(double c, Vec3d v) {
            return new Vec3d(c * v.x, c * v.y, c * v.z);
        }

        public static Vec3d operator *(Vec3d v, double c) {
            return new Vec3d(c * v.x, c * v.y, c * v.z);
        }

        // Method for dot product (scalar product)
        public static double operator *(Vec3d u, Vec3d v) {
            return u.x * v.x + u.y * v.y + u.z * v.z;
        }

        // Method for cross product
        public static Vec3d operator %(Vec3d u, Vec3d v) {
            return new Vec3d(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
        }

        public static Vec3d operator /(Vec3d v, double c) {
            return new Vec3d(v.x / c, v.y / c, v.z / c);
        }

        public double Norm() {
            return Math.Sqrt(x * x + y * y + z * z);
        }

        public Vec3d Unit() {
            double norm = this.Norm();
            return new Vec3d(this.x / norm, this.y / norm, this.z / norm);
        }

        public Vec3d Clone() {
            Vec3d a = new Vec3d(1, 1, 1);
            Vec3d b = new Vec3d(1, 1, 1);

            return new Vec3d(this.x, this.y, this.z);
        }

        public string getString() {
            string s = "(" + this.x + " " + this.y + " " + this.z + ")";
            return s;
        }

        public new string ToString() {
            return getString();
        }
    }
}
