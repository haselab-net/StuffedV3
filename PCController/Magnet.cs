using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Windows.Forms;
using System.Drawing;
using System.Windows.Forms.DataVisualization.Charting;

namespace PCController
{
    public class Magnet
    {
        public Series mcos = null, msin = null;
        public Chart chart = null;
        public ChartArea area = null;
        public Magnet(Control parent) {
            chart = new Chart();
            mcos = new Series();
            mcos.ChartType = SeriesChartType.Line;
            msin = new Series();
            msin.ChartType = SeriesChartType.Line;
            area = new ChartArea();
            parent.Controls.Add(chart);
            chart.ChartAreas.Add(area);
            chart.Series.Add(mcos);
            chart.Series.Add(msin);
            mcos.ChartArea = area.Name;
            msin.ChartArea = area.Name;
        }
        public void AddData(double t, double c, double s) {
            mcos.Points.AddXY(t, c);
            msin.Points.AddXY(t, s);
        }
        public void ClearData() {
            mcos.Points.Clear();
            msin.Points.Clear();
        }
    }
    public partial class MainForm {
        List<Magnet> magnets = new List<Magnet>();
        void ResetMagnet() {
            pnMagnet.Controls.Clear();
            magnets.Clear();
            for(int i=0; i<motors.Count; ++i)
            {
                Magnet m = new Magnet(pnMagnet);
                magnets.Add(m);
                pnMagnet.Controls.Add(m.chart);
                /*for (int t = 0; t < 5; ++t)
                {
                    m.AddData(t, i + t, 10 - i - t);
                }*/
            }
            for(int i=0; i<boards.NForce; i+=2)
            {
                Magnet m = new Magnet(pnMagnet);
                magnets.Add(m);
                pnMagnet.Controls.Add(m.chart);
            }
            pnMagnet_Resize(this, new EventArgs());
        }
        private void pnMagnet_Resize(object sender, EventArgs e)
        {
            Size sz = pnMagnet.ClientSize;
            for (int i=0; i<magnets.Count; ++i){
                Magnet m = magnets[i];
                m.chart.Left = (i % 3) * ((sz.Width) / 3);
                m.chart.Top = (i / 3) * ((sz.Height) / 4);
                m.chart.Width = sz.Width / 3 - 1;
                m.chart.Height = sz.Height / 4 - 1;
            }
        }
        int magnetCount = 0;
        bool magnetDriveMotor = false;
        private void btMeasure_Click(object sender, EventArgs e)
        {
            magnetDriveMotor = false;
            ResetMagnet();
            if (magnetCount == 0) {
                magnetCount = 1;
            }
        }
        private void btDriveMeasure_Click(object sender, EventArgs e)
        {
            magnetDriveMotor = true;
            boards.SendResetMotor();
            ResetMagnet();
            if (magnetCount == 0)
            {
                magnetCount = 1;
            }
        }

        short[] initialPos;
        short[] magnetSensors;
        int timerIntervalBackup;
        private void UpdateMagnet()
        {
            if (magnetCount == 0) return;
            txMsg.Text = (magnetDriveMotor ? "Drive and Measure" : "Measure") + " " + magnetCount + "\r\n";
            if (magnetCount == 1)
            {
                timerIntervalBackup = timer.Interval;
                timer.Interval = 10;
                boards.SendSense();
                initialPos = new short [motors.Count];
                for (int i = 0; i != motors.Count; ++i) initialPos[i] = boards.GetPos(i);
                magnetSensors = new short[motors.Count * 2 + (boards.NForce+1) / 2 * 2];
                boards.RecvParamMagnetSensor(ref magnetSensors);
            }
            //  Set motor control pattern 
            const int duration = 30;       //  duration to test in 10ms 
            const int motion = 1024;    //  amount of motion (1024 = 1 rotation)
            const int C1 = 2, C2 = C1+duration, C3 = C2+duration*2, C4 = C3+duration;
            if (C1 <= magnetCount && magnetCount <= C4)
            {
                boards.RecvParamMagnetSensor(ref magnetSensors);
                for (int i = 0; i < magnets.Count; ++i) {
                    magnets[i].AddData(magnetCount - C1, magnetSensors[i * 2], magnetSensors[i * 2 + 1]);
                }
            }
            if (C1 <= magnetCount && magnetCount < C4)
            {
                short[] targets = new short[boards.NMotor];
                for (int i = 0; i < motors.Count; ++i)
                {
                    if (magnetCount < C2) targets[i] = (short)(initialPos[i] + motion * (magnetCount-C1)/(C2-C1));
                    else if (magnetCount < C3) targets[i] = (short)(initialPos[i] + motion - 2* motion* (magnetCount - C2) / (C3 - C2));
                    else targets[i] = (short)(initialPos[i] - motion + motion * (magnetCount - C3) / (C4 - C3));
                }
                if (magnetDriveMotor)
                {
                    boards.SendPosDirect(targets);
                }
            }
            if (magnetCount == C4) {
                timer.Interval = timerIntervalBackup;
                magnetCount = 0;
                if (magnetDriveMotor)
                {
                    short[] currents = new short[boards.NMotor];
                    for (int i = 0; i < boards.NMotor; ++i) currents[i] = 0;
                    boards.SendCurrent(currents);
                }
                txMsg.Text = "";
                return;
            }
            magnetCount++;
        }
    }
}
