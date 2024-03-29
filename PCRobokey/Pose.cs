﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections;
using System.Windows.Forms;
using System.Drawing;

namespace Robokey
{
    public class PoseData : IComparable
    {
        public int nMotor;
        public int[] values;
        protected int time_ = 0;
        public PoseData(int nM) {
            nMotor = nM;
            values = new int[nMotor];
        }
        public int Time
        {
            set { time_ = value; }
            get { return time_; }
        }
        public int CompareTo(object o)
        {
            return time_ - ((PoseData)o).time_;
        }
        public static PoseData operator +(PoseData a, PoseData b)
        {
            if (a == null || b == null) return null;
            PoseData rv = new PoseData(a.nMotor);
            for (int i = 0; i < rv.nMotor; i++)
            {
                rv.values[i] = a.values[i] + b.values[i];
                rv.time_ = a.time_;
            }
            return rv;
        }
        public static PoseData operator +(PoseData a, int [] b)
        {
            PoseData rv = new PoseData(a.nMotor);
            for (int i = 0; i < rv.nMotor; i++)
            {
                rv.values[i] = a.values[i] + b[i];
                rv.time_ = a.time_;
            }
            return rv;
        }
    }
    public class Pose : PoseData
    {
        public new int Time
        {
            set
            {
                time_ = value;
                if (button.Parent != null)
                {
                    MainForm f = (MainForm)button.Parent;
                    TrackBar track = (TrackBar)f.Controls.Find("track", true)[0];
                    button.Left = (int)(Time * Scale + Offset);
                    button.Top = track.Top + track.Height / 2 - 5;
                }
            }
            get
            {
                return time_;
            }
        }
        public double Scale
        {
            get
            {
                if (button.Parent == null) return 1;
                MainForm f = (MainForm)button.Parent;
                return f.TrackScale();
            }
        }
        public double Offset
        {
            get
            {
                if (button.Parent == null) return 0;
                MainForm f = (MainForm)button.Parent;
                return f.TrackOffset() - button.Size.Width / 2.0;
            }
        }
        public Button button;
        public Pose(int nMotor): base(nMotor)
        {
            button = new Button();
            button.FlatStyle = FlatStyle.Flat;
            button.FlatAppearance.BorderSize = 10;
            button.FlatAppearance.BorderColor = Color.Blue;
            button.Size = new Size(5, 12);
        }
    }
}
