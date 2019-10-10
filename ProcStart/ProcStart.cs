using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

namespace ProcStart
{
    public partial class ProcStart : Form
    {
        private delegate void SetTextCallback(string text);

        public ProcStart()
        {
            InitializeComponent();
        }

        private void OnCloneClick(object sender, EventArgs e)
        {
            // Get location of executing assembly
            string thisExe = Assembly.GetExecutingAssembly().Location;
            //MessageBox.Show(thisExe);

            ProcessStartInfo psi = new ProcessStartInfo();
            psi.FileName = thisExe;

            Process p = Process.Start(psi);
        }

        private void OnBrowseClick(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "EXE files (*.exe)|*.exe";
            DialogResult dr = openFileDialog1.ShowDialog();
            txtThisApp.Text = openFileDialog1.FileName;
            btnStart.Enabled = true;
        }

        private void OnStartClick(object sender, EventArgs e)
        {
            ProcessStartInfo psi = new ProcessStartInfo();
            psi.FileName = txtThisApp.Text;
            psi.Arguments = txtArgs.Text;

            Process p = Process.Start(psi);
            p.EnableRaisingEvents = true;
            p.Exited += new EventHandler(ProcessExited);
            txtChildPID.Text = p.Id.ToString();
        }

        /// <summary>
        /// Sets the text of the txtExitCode control.
        /// </summary>
        /// <param name="text">Text to display in the txtExitCode control.</param>
        /// <remarks>This method will invoke a delegate if called from a worker thread.</remarks>
        private void SetText(string text)
        {
            if (this.txtExitCode.InvokeRequired) {
                Trace.WriteLine("SetText called by event handler.");
                SetTextCallback d = new SetTextCallback(SetText);
                this.Invoke(d, new object[] { text });
            }
            else {
                Trace.WriteLine("SetText invoked by delegate.");
                txtExitCode.Text = text;
            }
        }

        // This event is called when a process has exited
        void ProcessExited(object sender, EventArgs e)
        {
            Process p = (Process)sender;
            int exitCode = p.ExitCode;
            p.Exited -= ProcessExited;
            p.Close();
            SetText(exitCode.ToString());
        }

        private void txtThisApp_TextChanged(object sender, EventArgs e)
        {
            if (System.IO.File.Exists(txtThisApp.Text)) {
                btnStart.Enabled = true;
                btnStart.Focus();
            }
            else {
                btnStart.Enabled = false;
            }
        }

        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);

            Process p = Process.GetCurrentProcess();
            txtPID.Text = p.Id.ToString();
        }
    }
}