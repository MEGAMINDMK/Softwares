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
using System.Windows.Forms;


namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (radioButton1.Checked == true)
            {
                Process.Start("LaunchGTAIV.exe", "-windowed 1 -height 600 -width 800 -DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
            }
            else if (radioButton2.Checked == true)
            {
                Process.Start("LaunchGTAIV.exe", "-DX9/high -noprecache -renderquality 0 -shadowdensity 0 -texturequality 0 -viewdistance 0 -detailquality 0 -novblank -percentagevidmem 100 -availablevidmem 30 -novblank -stereo -framelimit 0 -noswapdelay -forcer2vb -monspecaudio -norestriction -noprecache -safemode -fullscreen -memrestrict 188743680 -memrestrict 209715200 -memrestrict 230686720 -minspecaudio -fullscreen -usedirectinput");
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


        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }
        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {

        }
        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {

        }
        private void radioButton4_CheckedChanged(object sender, EventArgs e)
        {

        }
    }
}
