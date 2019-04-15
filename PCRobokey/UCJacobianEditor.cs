using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Robokey
{

    /** Editor for Jacobian used for force control. Each arm with 2-dimensional torque sensor has one instance.
     * Correspondances between each wire and 2D torque are editable.
    */
    public partial class UCJacobianEditor : UserControl
    {
        PosForces[] forces = { new PosForces(), new PosForces(), new PosForces() };
        int selectedPlane = 0;
        int selectedId = -1;
        PointF curForce = new PointF();

        //  propeties
        public string FileName
        {
            set { loadDlg.FileName = saveDlg.FileName = value;
                if (forces[0].Count == 0)
                {
                    LoadForces(loadDlg.FileName);
                }
            }
            get { return  loadDlg.FileName;  }
        }
        //  public methods
        public void Jacobian(short[][] jacob, int off, double[] mPosAll)
        {
            NumericUpDown[] mis = { udMotorX, udMotorY, udMotorZ };
            for (int i = 0; i < 3; ++i) {
                mis[i].Minimum = 0;
                mis[i].Maximum = mPosAll.Count() - 1;
            }
            double[] mPos = { mPosAll[(int)mis[0].Value], mPosAll[(int)mis[1].Value], mPosAll[(int)mis[2].Value] };
            for (int i = 0; i < 3; ++i) {
                mPos[i] /= (double)udMScale.Value;
            }
            double mPosMin = double.MaxValue;
            int minId = -1;
            for (int i = 0; i < 3; ++i)
            {
                if (mPosMin < mPos[i])
                {
                    mPosMin = mPos[i];
                    minId = i;
                }
            }
            int plane = (minId + 1) % 3;
            PointF pos = new PointF((float)mPos[plane], (float)mPos[(plane + 1) % 3]);
            PosForce fInt = Interpolate(forces[plane], pos);
            Matrix2d matForce = new Matrix2d(new Vec2d(fInt.force[0]), new Vec2d(fInt.force[1]));
            Matrix2d matForceInv = matForce.Inv();
            for (int f = 0; f < 2; ++f) {
                for (int i = 0; i < 2; ++i) {
                    jacob[f + off][(plane + i) % 3] = (short) (- matForceInv.cols[f][i] * (float)(f == 0 ? udFXScale.Value: udFYScale.Value));
                }
                jacob[f + off][(plane + 2) % 3] = 0;
            }
        }
        public void SetCurForce(short fx, short fy) {
            curForce.X = fx / (float)udFXScale.Value;
            curForce.Y = fy / (float)udFYScale.Value;
            picForce.Invalidate();
        }

        PosForce Interpolate(PosForces fs, PointF pos)
        {
            Utility.TurnOnFpuException();
            double angle = Math.Atan2(pos.Y, pos.X);
            double dist = PosForce.Norm(pos);
            PosForces[] groups = { new PosForces(), new PosForces(), new PosForces(), new PosForces() };
            foreach (PosForce f in fs)
            {
                if (f.pos.X == 0 && f.pos.Y == 0)
                {
                    groups[0].Add(f);
                    groups[2].Add(f);
                }
                else
                {
                    double a = Math.Atan2(f.pos.Y, f.pos.X);
                    double d = PosForce.Norm(f.pos);
                    int id = 0;
                    if (a > angle) id += 2;
                    if (d > dist) id++;
                    groups[id].Add(f);
                }
            }
#if true
            string sep2 = "";
            foreach (PosForces g in groups)
            {
                System.Diagnostics.Debug.Write(sep2);
                sep2 = ", ";
                string sep = "";
                foreach (PosForce f in g)
                {
                    System.Diagnostics.Debug.Write(sep);
                    sep = " ";
                    System.Diagnostics.Debug.Write(fs.IndexOf(f));
                }
            }
            System.Diagnostics.Debug.WriteLine(".");
#endif
            PosForces pfs4 = new PosForces();
            foreach (PosForces g in groups)
            {
                double dMin = double.MaxValue;
                PosForce fMin = null;
                foreach (PosForce f in g)
                {
                    double df = double.MaxValue;
                    double distF = PosForce.Norm(f.pos) - dist;
                    double angleF = PosForce.IsZero(f) ? -1 : Math.Atan2(f.pos.Y, f.pos.X) - angle;
                    if (angleF == -1)
                    {
                        df = Math.Sqrt(distF * distF);
                    }
                    else {
                        df = Math.Sqrt(distF * distF + 0.01f * angleF * angleF);
                    }
                    if (df < dMin)
                    {
                        dMin = df;
                        fMin = f;
                    }
                }
                pfs4.Add(fMin);
            }
            //  interpolate in dist
            double[] da0 = { pfs4[0] == null ? -1e100 : PosForce.Norm(pfs4[0].pos), pfs4[1] == null ? 1e100 : PosForce.Norm(pfs4[1].pos) };
            double[] da1 = { pfs4[2] == null ? -1e100 : PosForce.Norm(pfs4[2].pos), pfs4[3] == null ? 1e100 : PosForce.Norm(pfs4[3].pos) };
            double ratioDistA0 = (da0[1] - dist) / (da0[1] - da0[0]);
            double ratioDistA1 = (da1[1] - dist) / (da1[1] - da1[0]);

            // interplation in angle
            double a0 = (PosForce.IsZero(pfs4[0]) ? 0 : ratioDistA0 * Math.Atan2(pfs4[0].pos.Y, pfs4[0].pos.X))
                + (PosForce.IsZero(pfs4[1]) ? 0 : (1 - ratioDistA0) * Math.Atan2(pfs4[1].pos.Y, pfs4[1].pos.X));
            double a1 = (PosForce.IsZero(pfs4[2]) ? 0 : ratioDistA1 * Math.Atan2(pfs4[2].pos.Y, pfs4[2].pos.X)) 
                + (PosForce.IsZero(pfs4[3]) ? 0 : (1 - ratioDistA1) * Math.Atan2(pfs4[3].pos.Y, pfs4[3].pos.X));
            double adiff = a1 - a0;
            double ratioAng;
            if (-1e-20 < adiff && adiff < 1e-20)
            {
                ratioAng = 0;
            }
            else
            {
                ratioAng = (a1 - angle) / (a1 - a0);
            }
#if true
            System.Diagnostics.Debug.Write("pfs4:");
            for (int i = 0; i < 4; ++i) {
                if (pfs4[i] == null)
                {
                    System.Diagnostics.Debug.Write(" ,");
                }
                else
                {
                    System.Diagnostics.Debug.Write(fs.IndexOf(pfs4[i]) + ",");
                }
            }
            System.Diagnostics.Debug.WriteLine("");

            System.Diagnostics.Debug.Write("d0:" + ratioDistA0);
            System.Diagnostics.Debug.Write(" d1:" + ratioDistA1);
            System.Diagnostics.Debug.Write(" a0:" + a0);
            System.Diagnostics.Debug.Write(" a1:" + a1);
            System.Diagnostics.Debug.Write(" a:" + angle);
#endif
            if (pfs4[0] == null && pfs4[1] == null) ratioAng = 0;
            if (pfs4[2] == null && pfs4[3] == null) ratioAng = 1;
            if (ratioAng < 0) ratioAng = 0;
            if (ratioAng > 1) ratioAng = 1;
#if true
            System.Diagnostics.Debug.Write(" DA0:" + ratioDistA0);
            System.Diagnostics.Debug.Write(" DA1:" + ratioDistA1);
            System.Diagnostics.Debug.WriteLine(" A:" + ratioAng);
#endif
            PosForce rv = new PosForce();
            rv.force[0] = new PointF(0, 0);  rv.force[1] = new PointF(0, 0);
            if (pfs4[0] != null) rv += (float)(ratioAng * ratioDistA0) * pfs4[0];
            if (pfs4[1] != null) rv += (float)(ratioAng * (1 - ratioDistA0)) * pfs4[1];
            if (pfs4[2] != null) rv += (float)((1-ratioAng) * ratioDistA1) * pfs4[2];
            if (pfs4[3] != null) rv += (float)((1-ratioAng) * (1 - ratioDistA1)) * pfs4[3];
            //            PosForce rv = (float)(ratioAng * ratioDistA0) * pfs4[0] + (float)(ratioAng * (1 - ratioDistA0)) * pfs4[1]
            //                + (float)((1 - ratioAng) * ratioDistA1) * pfs4[2] + (float)((1 - ratioAng) * (1 - ratioDistA1)) * pfs4[3];
            rv.pos = pos;
            Utility.TurnOffFpuException();
            return rv;
        }

        NumericUpDown[] motorPos = new NumericUpDown[3];
        public UCJacobianEditor()
        {
            InitializeComponent();
            for (int i = 0; i < motorPos.Count(); ++i)
            {
                motorPos[i] = new NumericUpDown();
                flMotor.Controls.Add(motorPos[i]);
            }
            saveDlg.InitialDirectory = System.IO.Directory.GetCurrentDirectory();
            loadDlg.InitialDirectory = System.IO.Directory.GetCurrentDirectory();
        }

        private void UCJacobianEditor_Load(object sender, EventArgs e)
        {
            for (int i = 0; i < motorPos.Count(); ++i)
            {
                motorPos[i].Width = 60;
            }
        }
        void CheckForces() {
            foreach (PosForces fs in forces) {
                foreach (PosForce f in fs)
                {
                    if (f.pos.X == 0 && f.pos.Y == 0)
                    {
                        if (f != fs[0]) {
                            fs.Remove(f);
                            fs.Insert(0, f);
                        }
                        break;
                    }
                }
                if (! (fs[0].pos.X == 0 && fs[0].pos.Y == 0))
                {
                    fs.Insert(0, Interpolate(fs, new PointF(0, 0)));
                }
            }
        }

        public event EventHandler ValueChanged;

        void UpdateGraph()
        {
            picPos.Refresh();
            picForce.Refresh();
        }
        void UpdateMotor()
        {
            if (selectedId >= 0)
            {
                float[] pos = { 0, 0, 0 };
                pos[selectedPlane] = forces[selectedPlane][selectedId].pos.X;
                pos[(selectedPlane + 1) % 3] = forces[selectedPlane][selectedId].pos.Y;
                //  3つ目は適当に作る
                float pull = pos[selectedPlane] + pos[(selectedPlane + 1) % 3];
                float push = -0.03f;
                if (pull < 0.01f) push *= pull / 0.01f;
                pos[(selectedPlane + 2) % 3] = push;
                NumericUpDown[] ud = motorPos;
                for (int i = 0; i < 3; ++i)
                {
                    pos[i] *= (float)udMScale.Value;
                    if ((float)ud[i].Maximum < pos[i]) ud[i].Maximum = (Decimal)pos[i];
                    if ((float)ud[i].Minimum > pos[i]) ud[i].Minimum = (Decimal)pos[i];
                    ud[i].Value = (Decimal)pos[i];
                }
                if (ValueChanged != null) ValueChanged(this, EventArgs.Empty);
            }
        }

        public void ReadFromMotors(List<Motor> from)
        {
            int[] ids = new int[3];
            ids[0] = (int)udMotorX.Value;
            ids[1] = (int)udMotorY.Value;
            ids[2] = (int)udMotorZ.Value;
            for (int i = 0; i < motorPos.Count(); ++i)
            {
                if (ids[i] >= from.Count) return;
            }
            for (int i = 0; i < motorPos.Count(); ++i)
            {
                motorPos[i].Maximum = from[ids[i]].Maximum;
                motorPos[i].Minimum = from[ids[i]].Minimum;
                motorPos[i].Value = from[ids[i]].Value;
            }
        }
        public void WriteToMotors(List<Motor> to)
        {
            int[] ids = new int[3];
            ids[0] = (int)udMotorX.Value;
            ids[1] = (int)udMotorY.Value;
            ids[2] = (int)udMotorZ.Value;
            for (int i = 0; i < motorPos.Count(); ++i)
            {
                if (ids[i] >= to.Count) return;
            }
            for (int i = 0; i < motorPos.Count(); ++i)
            {
                to[i].Value = (int)motorPos[ids[i]].Value;
            }
        }
        PictureBox baseBox;
        PointF Screen(PointF np, int n)
        {
            float h = baseBox.Height;
            float w = baseBox.Width;
            if (baseBox == picPos)
            {
                h /= 3.0f;
            }
            else
            {
                if (h > w) h = w;
                if (w > h) w = h;
            }
            return new PointF(np.X * w, (1 - np.Y + n) * h);
        }
        PointF Graph(float x, float y, int n = 0)
        {
            return Graph(new PointF(x, y), n);
        }
        PointF Graph(PointF np, int n = 0)
        {
            if (baseBox == picPos)
            {
                return Screen(new PointF(np.X * 0.94f + 0.03f, np.Y * 0.94f + 0.03f), n);
            }
            else
            {
                return Screen(new PointF(np.X * 0.47f + 0.5f, np.Y * 0.47f + 0.5f), n);
            }
        }
        float Graph(float f)
        {
            float w = baseBox.Width;
            if (baseBox == picPos)
            {
                return f * 0.94f * w;
            }
            else
            {
                if (w > baseBox.Height) w = baseBox.Height;
                return f * 0.47f * w;
            }
        }
        void GraphInv(ref PointF pg, ref int n, Point pos, bool trunc = true)
        {
            if (baseBox == picPos)
            {
                float h = baseBox.Height / 3.0f;
                float w = baseBox.Width;
                n = (int)(pos.Y / h);
                float sy = (h - (pos.Y - n * h)) / h;
                float sx = pos.X / w;
                pg.X = (sx - 0.03f) / 0.94f;
                pg.Y = (sy - 0.03f) / 0.94f;
                if (trunc == true)
                {
                    if (pg.X < 0) pg.X = 0;
                    if (pg.X > 1) pg.X = 1;
                    if (pg.Y < 0) pg.Y = 0;
                    if (pg.Y > 1) pg.Y = 1;
                }
            }
        }
        PointF GraphInv(Point pos, bool trunc = true)
        {
            PointF pg = new PointF();
            if (baseBox == picForce)
            {
                pg = new PointF();
                float h = baseBox.Height;
                float w = baseBox.Width;
                if (w > h) w = h;
                if (w < h) h = w;
                float sy = (h - (pos.Y)) / h;
                float sx = pos.X / w;
                pg.X = (sx - 0.5f) / 0.47f;
                pg.Y = (sy - 0.5f) / 0.47f;
                if (trunc == true)
                {
                    if (pg.X < -1) pg.X = -1;
                    if (pg.X > 1) pg.X = 1;
                    if (pg.Y < -1) pg.Y = -1;
                    if (pg.Y > 1) pg.Y = 1;
                }
            }
            return pg;
        }

        Rectangle Center(float gr)
        {
            PointF c = Graph(0, 0);
            float s = Graph(gr);
            return new Rectangle((int)(c.X - s), (int)(c.X - s), (int)(2 * s), (int)(2 * s));
        }
        private void picForce_Paint(object sender, PaintEventArgs e)
        {
            baseBox = (PictureBox)sender;
            e.Graphics.DrawLine(Pens.Gray, Graph(-1, 0), Graph(1, 0));
            e.Graphics.DrawLine(Pens.Gray, Graph(0, -1), Graph(0, 1));

            //  Force data of the selected point
            if (selectedId >= 0)
            {
                PosForce pf = forces[selectedPlane][selectedId];
                Brush[] brs = { Brushes.LightPink, Brushes.LightGreen, Brushes.LightBlue };
                Brush[] brs2 = { Brushes.LightYellow, Brushes.LightCyan, Brushes.Plum};
                PointF loc = Graph(0, 0);
                float a0 = -pf.GetAngle(0) * 180 / (float)Math.PI;
                float a1 = -pf.GetAngle(1) * 180 / (float)Math.PI;
                float ad = a1 - a0;
                if (ad < -180) ad += 360;
                if (ad > 180) ad -= 360;
                float[] s = { PosForce.Norm(pf.force[0]), (PosForce.Norm(pf.force[0]) + PosForce.Norm(pf.force[1])) / 2, PosForce.Norm(pf.force[1]) };
                for (int i = 0; i < 3; ++i) {
                    if (s[i] == 0) s[i] = 0.01f;
                }
                float r1 = 0.2f;
                float r2 = 0.8f;
                e.Graphics.FillPie(brs[selectedPlane], Center(s[0]), a0, ad * r1);
                e.Graphics.FillPie(brs2[selectedPlane], Center(s[1]), a0 + ad * r1, ad * (r2 - r1));
                e.Graphics.FillPie(brs[(selectedPlane + 1) % 3], Center(s[2]), a0 + ad * r2, ad * (1 - r2));
            }
            //  Interpolated force
            {
                PosForce ipf = Interpolate(forces[mousePlane], gMousePos);
                Pen[] ps = { Pens.Red, Pens.Green, Pens.Blue, Pens.Red };
                e.Graphics.DrawLine(ps[mousePlane], Graph(0, 0), Graph(ipf.force[0]));
                e.Graphics.DrawLine(ps[mousePlane + 1], Graph(0, 0), Graph(ipf.force[1]));
            }
            //  Current force
            {
                e.Graphics.DrawLine(Pens.Black, Graph(0, 0), Graph(curForce));
            }
        }

        const float THRESHOLD = 0.1f;
        private void picPos_Click(object sender, EventArgs e)
        {
            baseBox = picPos;
            MouseEventArgs me = (MouseEventArgs)e;
            Point pos = me.Location;
            PointF pg = new PointF(); int n = 0;
            GraphInv(ref pg, ref n, pos);
            float dist = float.MaxValue;
            int found = forces[n].Nearest(pg);
            if (found >= 0)
            {
                dist = forces[n][found].Distance(pg);
            }
            if (dist < THRESHOLD)   //  choose this
            {
                if (me.Button == MouseButtons.Right)
                {
                    forces[n].RemoveAt(found);
                    selectedId = -1;
                    UpdateGraph();
                }
            }
            else
            {          //  create new
                if (dragId == -1 && me.Button == MouseButtons.Left)
                {
                    forces[n].Add(Interpolate(forces[n], pg));
                    selectedPlane = n;
                    selectedId = forces[n].Count - 1;
                    UpdateGraph();
                    UpdateMotor();
                }
            }
        }

        int dragId = -1;
        int dragPlane = 0;
        PointF gMousePos = new PointF();
        int mousePlane = 0;

        private void picPos_MouseDown(object sender, MouseEventArgs e)
        {
            baseBox = picPos;
            if (e.Button == MouseButtons.Left)
            {
                PointF pg = new PointF();
                int n = 0;
                GraphInv(ref pg, ref n, e.Location);
                int id = forces[n].Nearest(pg);
                dragId = -1;
                if (id >= 0)
                {
                    float dist = forces[n][id].Distance(pg);
                    if (dist < THRESHOLD)
                    {
                        dragId = id;
                        dragPlane = n;
                        selectedPlane = n;
                        selectedId = id;
                        UpdateGraph();
                        UpdateMotor();
                    }
                }
            }
        }
        private void picPos_MouseMove(object sender, MouseEventArgs e)
        {
            baseBox = picPos;
            GraphInv(ref gMousePos, ref mousePlane, e.Location);
            if (e.Button != MouseButtons.Left)
            {
                dragId = -1;
                UpdateGraph();
            }
            else if (dragId >= 0)
            {
                PointF pg = new PointF();
                int n = 0;
                GraphInv(ref pg, ref n, e.Location);
                if (n == dragPlane)
                {
                    if (forces[n][dragId].pos.X == 0) pg.X = 0;
                    if (forces[n][dragId].pos.Y == 0) pg.Y = 0;
                    int nearst = forces[n].Nearest(pg, dragId);
                    if (nearst >= 0 && forces[n][nearst].Distance(pg) < THRESHOLD)
                    {
                        PointF diff = PosForce.Sub(forces[n][nearst].pos, forces[n][dragId].pos);
                        float norm = PosForce.Norm(diff);
                        PointF move = PosForce.Mul(THRESHOLD / norm, diff);
                        pg = PosForce.Sub(forces[n][nearst].pos, move);
                    }
                    if (pg.X == 0)
                    {
                        PosForces next = forces[(n + 1) % 3];
                        int id = next.Find(forces[n][dragId].pos.Y, 0);
                        if (id >= 0)
                        {
                            next[id].pos.X = pg.Y;
                        }
                        else {
                            next.Add(Interpolate(next, new PointF(pg.Y, 0)));
                        }
                    }
                    if (pg.Y == 0)
                    {
                        PosForces prev = forces[(n - 1 + 3) % 3];
                        int id = prev.Find(0, forces[n][dragId].pos.X);
                        if (id >= 0)
                        {
                            prev[id].pos.Y = pg.X;
                        }
                        else {
                            prev.Add(Interpolate(prev, new PointF(0, pg.X)));
                        }
                    }
                    forces[n][dragId].pos = pg;
                    UpdateGraph();
                }
            }
        }

        private void picPos_Paint(object sender, PaintEventArgs e)
        {
            baseBox = picPos;
            Pen[] pens = { Pens.Red, Pens.Green, Pens.Blue };

            Brush[] brsS = { Brushes.Gold, Brushes.Cyan, Brushes.Magenta, Brushes.Black };
            Brush[] brsN = { Brushes.DarkGoldenrod, Brushes.DarkCyan, Brushes.DarkMagenta, Brushes.DarkGray };

            Graphics g = e.Graphics;
            g.DrawLine(pens[0], Graph(0, 0, 0), Graph(1, 0, 0));
            g.DrawLine(pens[1], Graph(0, 0, 0), Graph(0, 1, 0));

            g.DrawLine(pens[1], Graph(0, 0, 1), Graph(1, 0, 1));
            g.DrawLine(pens[2], Graph(0, 0, 1), Graph(0, 1, 1));

            g.DrawLine(pens[2], Graph(0, 0, 2), Graph(1, 0, 2));
            g.DrawLine(pens[0], Graph(0, 0, 2), Graph(0, 1, 2));

            for (int n = 0; n < 3; ++n)
            {
                for (int i = 0; i < forces[n].Count; ++i)
                {
                    PosForce pf = forces[n][i];
                    PointF dO = Graph(pf.pos, n);
                    int sz = (int)Graph(THRESHOLD);
                    Rectangle rect = new Rectangle((int)(dO.X - sz / 2.0f), (int)(dO.Y - sz / 2.0f), sz, sz);
                    float[] angles = { -pf.GetAngle(0), -pf.GetAngle(1) };
                    for (int j = 0; j < 2; ++j)
                    {
                        angles[j] = angles[j] * 180 / (float)Math.PI;
                    }
                    Brush[] brs = null;
                    if (n == selectedPlane && i == selectedId)
                    {
                        brs = brsS;
                    }
                    else
                    {
                        brs = brsN;
                    }
                    float diff = angles[1] - angles[0];
                    if (diff < -180) diff += 360;
                    if (diff > 180) diff -= 360;
                    g.FillPie(brs[n], rect, angles[0], diff);
                    if (diff < 0) diff = 360 + diff;
                    else diff = -360 + diff;
                    g.FillPie(brs[3], rect, angles[0], diff);
                }
            }
        }

        private void UCJacobianEditor_Resize(object sender, EventArgs e)
        {
            Control control = (Control)sender;
            picPos.Width = control.Height / 3;
        }

        private void btLoad_Click(object sender, EventArgs e)
        {
            loadDlg.ShowDialog();
        }
        private void loadDlg_FileOk(object sender, CancelEventArgs e)
        {
            LoadForces(((FileDialog)sender).FileName);
        }

        private void btSave_Click(object sender, EventArgs e)
        {
            saveDlg.ShowDialog();
        }

        private void saveDlg_FileOk(object sender, CancelEventArgs e)
        {
            SaveForces(((FileDialog)sender).FileName);
        }
        void SaveForces(string fn)
        {
            System.IO.StreamWriter file = new System.IO.StreamWriter(fn);
            file.Write("motor\t");
            file.Write(udMotorX.Value); file.Write("\t");
            file.Write(udMotorY.Value); file.Write("\t");
            file.Write(udMotorZ.Value); file.WriteLine();
            file.Write("scale\t");
            file.Write(udMScale.Value); file.Write("\t");
            file.Write(udFXScale.Value); file.Write("\t");
            file.Write(udFYScale.Value); file.WriteLine();
            int id = 0;
            foreach (PosForces fs in forces)
            {
                file.Write("plane\t");
                file.Write(id);
                file.WriteLine();
                id++;
                foreach (PosForce f in fs)
                {
                    file.Write(f.pos.X); file.Write("\t");
                    file.Write(f.pos.Y); file.Write("\t");
                    file.Write(f.force[0].X); file.Write("\t");
                    file.Write(f.force[0].Y); file.Write("\t");
                    file.Write(f.force[1].X); file.Write("\t");
                    file.Write(f.force[1].Y); file.WriteLine();
                }
            }
            file.Close();
        }
        void LoadForces(string fn)
        {
            System.IO.StreamReader file;
            try
            {
                file = new System.IO.StreamReader(fn);
            }
            catch (Exception)
            {
                return;
            }
            String[] cells;
            int plane = 0;
            foreach (PosForces fs in forces)
            {
                fs.Clear();
            }
            while (!file.EndOfStream)
            {
                cells = file.ReadLine().Split('\t');
                if (cells.Length == 0) continue;
                if (cells[0] == "motor")
                {
                    udMotorX.Value = decimal.Parse(cells[1]);
                    udMotorY.Value = decimal.Parse(cells[2]);
                    udMotorZ.Value = decimal.Parse(cells[3]);
                }
                else if (cells[0] == "scale")
                {
                    if (cells.Length >= 4)
                    {
                        udMScale.Value = decimal.Parse(cells[1]);
                        udFXScale.Value = decimal.Parse(cells[2]);
                        udFYScale.Value = decimal.Parse(cells[3]);
                    }
                }
                else if (cells[0] == "plane")
                {
                    plane = int.Parse(cells[1]);
                }
                else
                {
                    PosForce pf = new PosForce();
                    pf.pos.X = float.Parse(cells[0]);
                    pf.pos.Y = float.Parse(cells[1]);
                    pf.force[0].X = float.Parse(cells[2]);
                    pf.force[0].Y = float.Parse(cells[3]);
                    pf.force[1].X = float.Parse(cells[4]);
                    pf.force[1].Y = float.Parse(cells[5]);
                    forces[plane].Add(pf);
                }
            }
            file.Close();
            CheckForces();
        }

        int forceDragSel = -1;
        private void picForce_MouseDown(object sender, MouseEventArgs e)
        {
            baseBox = picForce;
            if (selectedId >= 0 && e.Button == MouseButtons.Left)
            {
                PosForce pf = forces[selectedPlane][selectedId];
                PointF pg = GraphInv(e.Location);
                forceDragSel = -1;
                if (PosForce.Norm(pg) > 0)
                {
                    float angle = (float)(Math.Atan2(pg.Y, pg.X) * 180 / Math.PI);
                    float a0 = pf.GetAngle(0) * 180 / (float)Math.PI;
                    float a1 = pf.GetAngle(1) * 180 / (float)Math.PI;
                    float ad = a1 - a0;
                    if (ad < -180) ad += 360;
                    if (ad > 180) ad -= 360;
                    float diff = angle - a0;
                    if (ad > 0)
                    {
                        if (diff < -90) diff += 360;
                        if (diff > 270) diff -= 360;
                    }
                    else
                    {
                        if (diff < -270) diff += 360;
                        if (diff > 90) diff -= 360;
                    }
                    float ratio = diff / ad;
                    if (ratio < 0) ratio *= -1;
                    if (0.2 <= ratio && ratio <= 0.8)
                    {
                        forceDragSel = 1;
                    }
                    else if (ratio < 0.5)
                    {
                        forceDragSel = 0;
                    }
                    else
                    {
                        forceDragSel = 2;
                    }
                }
            }
        }

        private void picForce_MouseMove(object sender, MouseEventArgs e)
        {
            if (selectedId >= 0 && forceDragSel >= 0 && e.Button == MouseButtons.Left)
            {
                PosForce pf = forces[selectedPlane][selectedId];
                PointF pg = GraphInv(e.Location);
                float angle = (float)(Math.Atan2(pg.Y, pg.X) * 180 / Math.PI);
                float a0 = pf.GetAngle(0) * 180 / (float)Math.PI;
                float a1 = pf.GetAngle(1) * 180 / (float)Math.PI;
                if (forceDragSel == 1)
                {
                    float n0 = PosForce.Norm(pf.force[0]);
                    float n1 = PosForce.Norm(pf.force[1]);
                    float nave = (n0 + n1) / 2;
                    float n = PosForce.Norm(pg);
                    float nmul = n / nave;
                    float aave = (a0 + a1) / 2;
                    float adiff = angle - aave;
                    if (adiff > 90) adiff -= 180;
                    if (adiff < -90) adiff += 180;

                    pf.force[0].X = n0 * nmul * (float)Math.Cos((a0 + adiff) / 180 * Math.PI);
                    pf.force[0].Y = n0 * nmul * (float)Math.Sin((a0 + adiff) / 180 * Math.PI);
                    pf.force[1].X = n1 * nmul * (float)Math.Cos((a1 + adiff) / 180 * Math.PI);
                    pf.force[1].Y = n1 * nmul * (float)Math.Sin((a1 + adiff) / 180 * Math.PI);
                }
                else
                {
                    pf.force[forceDragSel / 2] = pg;
                }
                if (pf.pos.X == 0)
                {
                    PosForces nfs = forces[(selectedPlane + 1) % 3];
                    foreach (PosForce nf in nfs)
                    {
                        if (pf.pos.Y == nf.pos.X)
                        {
                            nf.force[0] = pf.force[1];
                        }
                    }
                }
                if (pf.pos.Y == 0)
                {
                    PosForces nfs = forces[(selectedPlane - 1 + 3) % 3];
                    foreach (PosForce nf in nfs)
                    {
                        if (pf.pos.X == nf.pos.Y)
                        {
                            nf.force[1] = pf.force[0];
                        }
                    }
                }
                UpdateGraph();
            }
            else
            {
                forceDragSel = -1;
            }
        }
    }
    public class PosForce
    {
        public PointF pos;
        public PointF[] force = { new PointF(0, 1), new PointF(0, -1) };
        public PosForce()
        {
        }
        public PosForce(PointF pg)
        {
            pos = pg;
        }
        public static bool IsZero(PosForce p) {
            if (p == null) return true;
            if (p.pos.X == 0 && p.pos.Y == 0) return true;
            return false;
        }
        public static float Norm(PointF p)
        {
            return (float)Math.Sqrt(p.X * p.X + p.Y * p.Y);
        }
        public void SetAngle(int i, float a, float len = -1)
        {
            float norm;
            if (len < 0)
            {
                norm = Norm(force[0]);
            }
            else
            {
                norm = len;
            }
            force[i].X = (float)Math.Sin(a) * norm;
            force[i].Y = (float)Math.Cos(a) * norm;
        }
        public float GetAngle(int i)
        {
            return (float)Math.Atan2(force[i].Y, force[i].X);
        }
        public float GetLen(int i)
        {
            return Norm(force[i]);
        }
        public float Distance(PointF p)
        {
            PointF diff = new PointF(p.X - pos.X, p.Y - pos.Y);
            return Norm(diff);
        }
        public static PointF Mul(float m, PointF p)
        {
            return new PointF(m * p.X, m * p.Y);
        }
        public static PointF Add(PointF a, PointF b)
        {
            return new PointF(a.X + b.X, a.Y + b.Y);
        }
        public static PointF Sub(PointF a, PointF b)
        {
            return new PointF(a.X - b.X, a.Y - b.Y);
        }
        public static PosForce operator +(PosForce a, PosForce b)
        {
            PosForce rv = new PosForce();
            rv.pos = Add(a.pos, b.pos);
            for (int i = 0; i < 2; ++i)
            {
                rv.force[i] = Add(a.force[i], b.force[i]);
            }
            return rv;
        }
        public static PosForce operator *(float m, PosForce b)
        {
            PosForce rv = new PosForce();
            rv.pos = Mul(m, b.pos);
            for (int i = 0; i < 2; ++i)
            {
                rv.force[i] = Mul(m, b.force[i]);
            }
            return rv;
        }
    };
    class PosForces : List<PosForce>
    {
        public int Nearest(PointF p, int except = -1)
        {
            float dist = float.MaxValue;
            int found = -1;
            for (int i = 0; i < Count; ++i)
            {
                if (i == except) continue;
                float d = this.ElementAt(i).Distance(p);
                if (d < dist)
                {
                    dist = d;
                    found = i;
                }
            }
            return found;
        }
        public int Find(float x, float y) {
            for (int i = 0; i < Count; ++i) {
                if (this.ElementAt(i).pos.X == x && this.ElementAt(i).pos.Y == y) {
                    return i;
                } 
            }
            return -1;
        }
     }
}