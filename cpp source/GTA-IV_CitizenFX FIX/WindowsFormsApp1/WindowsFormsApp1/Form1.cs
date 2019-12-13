using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;
using System.IO;
using System.Windows.Forms;


namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        private bool drag = false;
        private Point startPoint = new Point(0, 0); 

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (radioButton1.Checked == true)
            {
                Process.Start("LaunchGTAIV.exe", "-windowed 1 -borderless -height 600 -width 800 -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
            }
            else if (radioButton2.Checked == true)
            {
                Process.Start("LaunchGTAIV.exe", "-borderless -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
            }
            else if (radioButton3.Checked == true)
            {
                Process.Start("CitizenMP-IV\\Launcher.exe", "-windowed 1 -height 600 -width 800 -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
            }
            else if (radioButton4.Checked == true)
            {
                Process.Start("CitizenMP-IV\\Launcher.exe", "-DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
            }
            else
            {
                MessageBox.Show("Select an option!");
                return;
            }

        }

 private void button2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (this.WindowState != FormWindowState.Minimized)
            {
                this.WindowState = FormWindowState.Minimized;
            }
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            this.startPoint = e.Location;
            this.drag = true;
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            if (this.drag)
            { // if we should be dragging it, we need to figure out some movement
                Point p1 = new Point(e.X, e.Y);
                Point p2 = this.PointToScreen(p1);
                Point p3 = new Point(p2.X - this.startPoint.X, p2.Y - this.startPoint.Y);
                this.Location = p3;
            }
        }

        private void panel1_MouseUp(object sender, MouseEventArgs e)
        {
            this.drag = false;
        }

        private void label4_MouseDown(object sender, MouseEventArgs e)
        {
            this.startPoint = e.Location;
            this.drag = true;
        }

        private void label4_MouseMove(object sender, MouseEventArgs e)
        {
            if (this.drag)
            { // if we should be dragging it, we need to figure out some movement
                Point p1 = new Point(e.X, e.Y);
                Point p2 = this.PointToScreen(p1);
                Point p3 = new Point(p2.X - this.startPoint.X, p2.Y - this.startPoint.Y);
                this.Location = p3;
            }
        }

        private void label4_MouseUp(object sender, MouseEventArgs e)
        {
            this.drag = false;
        }

        private void pictureBox2_MouseDown(object sender, MouseEventArgs e)
        {
            this.startPoint = e.Location;
            this.drag = true;
        }

        private void pictureBox2_MouseMove(object sender, MouseEventArgs e)
        {
            if (this.drag)
            { // if we should be dragging it, we need to figure out some movement
                Point p1 = new Point(e.X, e.Y);
                Point p2 = this.PointToScreen(p1);
                Point p3 = new Point(p2.X - this.startPoint.X, p2.Y - this.startPoint.Y);
                this.Location = p3;
            }
        }

        private void pictureBox2_MouseUp(object sender, MouseEventArgs e)
        {
            this.drag = false;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Process[] _proceses = null;
            _proceses = Process.GetProcessesByName("GTAIV");
            foreach (Process proces in _proceses)
            {
                proces.Kill();
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Process[] _proceses = null;
            _proceses = Process.GetProcessesByName("Launcher");
            foreach (Process proces in _proceses)
            {
                proces.Kill();
            }
        }

        private void button2_MouseEnter(object sender, EventArgs e)
        {
            button2.BackColor = Color.Red;
        }

        private void button2_MouseLeave(object sender, EventArgs e)
        {
            button2.BackColor = Color.Teal;
        }

        private void button3_MouseEnter(object sender, EventArgs e)
        {
            button3.BackColor = Color.DodgerBlue;
        }

        private void button3_MouseLeave(object sender, EventArgs e)
        {
            button3.BackColor = Color.Teal;
        }
    }
}
