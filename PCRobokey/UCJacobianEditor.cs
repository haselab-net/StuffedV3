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
    public partial class UCJacobianEditor : UserControl
    {
        double[] wireAngles = new double[3];
        public UCJacobianEditor()
        {
            InitializeComponent();
        }

        private void UCJacobianEditor_Load(object sender, EventArgs e)
        {

        }

        private void pic_Paint(object sender, PaintEventArgs e)
        {
            PictureBox pictureBox = (PictureBox)sender;
            int cX = pictureBox.Width / 2;
            int cY = pictureBox.Height / 2;
            Pen penR = new Pen(Color.Red, 1.0F);
            Pen penG = new Pen(Color.Green, 1.0F);
            Pen penB = new Pen(Color.Blue, 1.0F);
            Pen[] pens = { penR, penG, penB };
            Pen penC = new Pen(Color.Cyan, 1.0F);
            Pen penM = new Pen(Color.Magenta, 2.0F);
            Pen penY = new Pen(Color.Yellow, 1.0F);

            e.Graphics.DrawLine(penC, new Point(cX, 0), new Point(cX, cY * 2));
            e.Graphics.DrawLine(penC, new Point(0, cY), new Point(cX * 2, cY));

            e.Graphics.DrawLine(penC, new Point(cX, 0), new Point(cX, cY * 2));
            e.Graphics.DrawLine(penC, new Point(0, cY), new Point(cX * 2, cY));
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void pnForce_Paint(object sender, PaintEventArgs e)
        {

        }

        private void lbWire_Click(object sender, EventArgs e)
        {

        }

        private void UCJacobianEditor_Resize(object sender, EventArgs e)
        {
            picLeft.Width = Width / 2;
            picRight.Width = Width / 2;
        }
    }
}
