namespace ProcStart
{
    partial class ProcStart
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnClone = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.txtChildPID = new System.Windows.Forms.TextBox();
            this.txtExitCode = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.txtArgs = new System.Windows.Forms.TextBox();
            this.btnStart = new System.Windows.Forms.Button();
            this.btnBrowse = new System.Windows.Forms.Button();
            this.txtThisApp = new System.Windows.Forms.TextBox();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.label1 = new System.Windows.Forms.Label();
            this.txtPID = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnClone
            // 
            this.btnClone.Location = new System.Drawing.Point(22, 253);
            this.btnClone.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.btnClone.Name = "btnClone";
            this.btnClone.Size = new System.Drawing.Size(138, 42);
            this.btnClone.TabIndex = 0;
            this.btnClone.Text = "Clone";
            this.btnClone.UseVisualStyleBackColor = true;
            this.btnClone.Click += new System.EventHandler(this.OnCloneClick);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.txtChildPID);
            this.groupBox1.Controls.Add(this.txtExitCode);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.txtArgs);
            this.groupBox1.Controls.Add(this.btnStart);
            this.groupBox1.Controls.Add(this.btnBrowse);
            this.groupBox1.Controls.Add(this.txtThisApp);
            this.groupBox1.Location = new System.Drawing.Point(22, 22);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.groupBox1.Size = new System.Drawing.Size(1140, 194);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Open this application";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(358, 150);
            this.label4.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(100, 25);
            this.label4.TabIndex = 7;
            this.label4.Text = "Child PID:";
            // 
            // txtChildPID
            // 
            this.txtChildPID.Location = new System.Drawing.Point(468, 146);
            this.txtChildPID.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.txtChildPID.Name = "txtChildPID";
            this.txtChildPID.ReadOnly = true;
            this.txtChildPID.Size = new System.Drawing.Size(154, 29);
            this.txtChildPID.TabIndex = 6;
            // 
            // txtExitCode
            // 
            this.txtExitCode.Location = new System.Drawing.Point(803, 146);
            this.txtExitCode.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.txtExitCode.Name = "txtExitCode";
            this.txtExitCode.ReadOnly = true;
            this.txtExitCode.Size = new System.Drawing.Size(175, 29);
            this.txtExitCode.TabIndex = 5;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(691, 151);
            this.label2.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(103, 25);
            this.label2.TabIndex = 4;
            this.label2.Text = "Exit Code:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(28, 89);
            this.label3.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(113, 25);
            this.label3.TabIndex = 3;
            this.label3.Text = "Arguments:";
            // 
            // txtArgs
            // 
            this.txtArgs.Location = new System.Drawing.Point(149, 83);
            this.txtArgs.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.txtArgs.Name = "txtArgs";
            this.txtArgs.Size = new System.Drawing.Size(829, 29);
            this.txtArgs.TabIndex = 2;
            // 
            // btnStart
            // 
            this.btnStart.Enabled = false;
            this.btnStart.Location = new System.Drawing.Point(11, 131);
            this.btnStart.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(138, 42);
            this.btnStart.TabIndex = 1;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.OnStartClick);
            // 
            // btnBrowse
            // 
            this.btnBrowse.Location = new System.Drawing.Point(992, 30);
            this.btnBrowse.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.btnBrowse.Name = "btnBrowse";
            this.btnBrowse.Size = new System.Drawing.Size(138, 42);
            this.btnBrowse.TabIndex = 1;
            this.btnBrowse.Text = "Browse";
            this.btnBrowse.UseVisualStyleBackColor = true;
            this.btnBrowse.Click += new System.EventHandler(this.OnBrowseClick);
            // 
            // txtThisApp
            // 
            this.txtThisApp.Location = new System.Drawing.Point(11, 35);
            this.txtThisApp.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.txtThisApp.Name = "txtThisApp";
            this.txtThisApp.Size = new System.Drawing.Size(967, 29);
            this.txtThisApp.TabIndex = 0;
            this.txtThisApp.TextChanged += new System.EventHandler(this.txtThisApp_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(721, 264);
            this.label1.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(93, 25);
            this.label1.TabIndex = 2;
            this.label1.Text = "This PID:";
            // 
            // txtPID
            // 
            this.txtPID.Location = new System.Drawing.Point(825, 258);
            this.txtPID.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.txtPID.Name = "txtPID";
            this.txtPID.ReadOnly = true;
            this.txtPID.Size = new System.Drawing.Size(175, 29);
            this.txtPID.TabIndex = 3;
            // 
            // ProcStart
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1184, 318);
            this.Controls.Add(this.txtPID);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btnClone);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(6, 6, 6, 6);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ProcStart";
            this.Text = "ProcStart";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnClone;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.Button btnBrowse;
        private System.Windows.Forms.TextBox txtThisApp;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtPID;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtExitCode;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtArgs;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtChildPID;
    }
}

