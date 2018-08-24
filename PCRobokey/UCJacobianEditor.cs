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
        int selectedId = 0;

        NumericUpDown[] motorPos = new NumericUpDown[3];
        public UCJacobianEditor()
        {
            InitializeComponent();
            for (int i=0; i<motorPos.Count(); ++i) {
                motorPos[i] = new NumericUpDown();
                flMotor.Controls.Add(motorPos[i]);
            }
            saveDlg.InitialDirectory = System.IO.Directory.GetCurrentDirectory();
            loadDlg.InitialDirectory = System.IO.Directory.GetCurrentDirectory();
            LoadForces(loadDlg.FileName);
        }

        public event EventHandler ValueChanged;

        void UpdateGraph() {
            picPos.Refresh();
            picForce.Refresh();
        }
        void UpdateMotor() {
            if (selectedId >= 0)
            {
                float[] pos = { 0, 0, 0 };
                pos[selectedPlane] = forces[selectedPlane][selectedId].pos.X;
                pos[(selectedPlane+1)%3] = forces[selectedPlane][selectedId].pos.Y;
                //  3つ目は適当に作る
                float pull = pos[selectedPlane] + pos[(selectedPlane + 1) % 3];
                float push = -0.03f;
                if (pull < 0.01f) push *= pull / 0.01f;
                pos[(selectedPlane + 2) % 3] = push;
                NumericUpDown[] ud = motorPos;
                for(int i=0;i<3; ++i) {
                    pos[i] *= (float)udScale.Value;
                    if ((float)ud[i].Maximum < pos[i]) ud[i].Maximum = (Decimal)pos[i];
                    if ((float)ud[i].Minimum > pos[i]) ud[i].Minimum = (Decimal)pos[i];
                    ud[i].Value = (Decimal)pos[i];
                }
                if (ValueChanged != null) ValueChanged(this, EventArgs.Empty);
            }
        }

        public void ReadFromMotors(List<Motor> from)
        {
            int [] ids = new int[3];
            ids[0] = (int)udMotorX.Value;
            ids[1] = (int)udMotorY.Value;
            ids[2] = (int)udMotorZ.Value;
            for (int i = 0; i < motorPos.Count(); ++i) {
                if (ids[i] >= from.Count) return;
            }
            for (int i=0; i < motorPos.Count(); ++i)
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

        private void UCJacobianEditor_Load(object sender, EventArgs e)
        {
            for (int i = 0; i < motorPos.Count(); ++i)
            {
                motorPos[i].Width = 60;
            }
        }
        PictureBox baseBox;
        PointF Screen(PointF np, int n) {
            float h = baseBox.Height;
            float w = baseBox.Width;
            if (baseBox == picPos)
            {
                h /= 3.0f;
            }
            else {
                if (h > w) h = w;
                if (w > h) w = h;
            }
            return new PointF(np.X * w, (1-np.Y + n) * h);
        }
        PointF Graph(float x, float y, int n=0) {
            return Graph(new PointF(x, y), n);
        }
        PointF Graph(PointF np, int n=0)
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
        float Graph(float f) {
            float w = baseBox.Width;
            if (baseBox == picPos)
            {
                return f * 0.94f * w;
            }
            else {
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

        Rectangle Center(float gr) {
            PointF c = Graph(0, 0);
            float s = Graph(gr);
            return new Rectangle((int)(c.X-s), (int)(c.X-s), (int)(2*s), (int)(2*s));
        }
        private void picForce_Paint(object sender, PaintEventArgs e)
        {
            baseBox = (PictureBox)sender;
            e.Graphics.DrawLine(Pens.Gray, Graph(-1, 0), Graph(1, 0));
            e.Graphics.DrawLine(Pens.Gray, Graph(0, -1), Graph(0, 1));
            if (selectedId >= 0)
            {
                PosForce pf = forces[selectedPlane][selectedId];
                Brush[] brs = { Brushes.Red, Brushes.Green, Brushes.Blue };
                Brush[] brs2 = { Brushes.Yellow, Brushes.Cyan, Brushes.Magenta };
                PointF loc = Graph(0, 0);
                float a0 = -pf.GetAngle(0) * 180 / (float)Math.PI;
                float a1 = -pf.GetAngle(1) * 180 / (float)Math.PI;
                float ad = a1 - a0;
                if (ad < -180) ad += 360;
                if (ad > 180) ad -= 360;
                float[] s = { PosForce.Norm(pf.force[0]), (PosForce.Norm(pf.force[0]) + PosForce.Norm(pf.force[1])) / 2, PosForce.Norm(pf.force[1]) };
                float r1 = 0.2f;
                float r2 = 0.8f;
                e.Graphics.FillPie(brs[selectedPlane], Center(s[0]), a0, ad * r1);
                e.Graphics.FillPie(brs2[selectedPlane], Center(s[1]), a0 + ad*r1, ad*(r2-r1));
                e.Graphics.FillPie(brs[(selectedPlane + 1) % 3], Center(s[2]), a0 + ad * r2, ad * (1-r2));
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
                if (dragId == -1 &&  me.Button == MouseButtons.Left)
                {
                    CreateNewData(pg, n);
                    selectedPlane = n;
                    selectedId = forces[n].Count-1;
                    UpdateGraph();
                    UpdateMotor();
                }
            }
        }
        void CreateNewData(PointF pg, int n) {
            PosForce pf = new PosForce(pg);
            forces[n].Add(pf);
        }

        int dragId = -1;
        int dragPlane = 0;

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
            if (e.Button != MouseButtons.Left)
            {
                dragId = -1;
            }else if (dragId >= 0)
            {
                PointF pg = new PointF();
                int n = 0;
                GraphInv(ref pg, ref n, e.Location);
                if (n == dragPlane)
                {
                    forces[n][dragId].pos = pg;
                    UpdateGraph();
                }
            }
        }

        private void picPos_Paint(object sender, PaintEventArgs e)
        {
            baseBox = picPos;
            Pen[] pens = { Pens.Red, Pens.Green, Pens.Blue};

            Brush[] brsS = { Brushes.Gold, Brushes.Cyan, Brushes.Magenta, Brushes.Black};
            Brush[] brsN = { Brushes.DarkGoldenrod, Brushes.DarkCyan, Brushes.DarkMagenta, Brushes.DarkGray};

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
                    } else {
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
            file.Write(udScale.Value); file.WriteLine();
            int id = 0;
            foreach (PosForces fs in forces) {
                file.Write("plane\t");
                file.Write(id);
                file.WriteLine();
                id++;
                foreach (PosForce f in fs) {
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
            System.IO.StreamReader file = new System.IO.StreamReader(fn);
            String[] cells;
            int plane = 0;
            foreach (PosForces fs in forces)
            {
                fs.Clear();
            }
            while (!file.EndOfStream) {
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
                    udScale.Value = decimal.Parse(cells[1]);
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
        }

        int forceDragSel = -1;
        private void picForce_MouseDown(object sender, MouseEventArgs e)
        {
            baseBox = picForce;
            if (selectedId >=0 && e.Button == MouseButtons.Left)
            {
                PosForce pf = forces[selectedPlane][selectedId];
                PointF pg = GraphInv(e.Location);
                forceDragSel = -1;
                if (PosForce.Norm(pg) > 0) {
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
                    else {
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
                    else{
                        forceDragSel = 2;
                    }
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
                    else {
                        pf.force[forceDragSel / 2] = pg;
                    }
                    UpdateGraph();
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
    };
    class PosForces : List<PosForce>
    {
        public int Nearest(PointF p)
        {
            float dist = float.MaxValue;
            int found = -1;
            for (int i = 0; i < Count; ++i)
            {
                float d = this.ElementAt(i).Distance(p);
                if (d < dist)
                {
                    dist = d;
                    found = i;
                }
            }
            return found;
        }
    }
}
