namespace PhongKhamManagement
{
    partial class MainForm
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
            this.btnKhachHang = new System.Windows.Forms.Button();
            this.btnListKH = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnKhachHang
            // 
            this.btnKhachHang.Location = new System.Drawing.Point(13, 13);
            this.btnKhachHang.Name = "btnKhachHang";
            this.btnKhachHang.Size = new System.Drawing.Size(317, 79);
            this.btnKhachHang.TabIndex = 0;
            this.btnKhachHang.Text = "Nhập thông tin Khách hàng";
            this.btnKhachHang.UseVisualStyleBackColor = true;
            this.btnKhachHang.Click += new System.EventHandler(this.btnKhachHang_Click);
            // 
            // btnListKH
            // 
            this.btnListKH.Location = new System.Drawing.Point(13, 98);
            this.btnListKH.Name = "btnListKH";
            this.btnListKH.Size = new System.Drawing.Size(317, 79);
            this.btnListKH.TabIndex = 1;
            this.btnListKH.Text = "Xem thông tin Khách hàng";
            this.btnListKH.UseVisualStyleBackColor = true;
            this.btnListKH.Click += new System.EventHandler(this.btnListKH_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(13, 184);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(317, 105);
            this.button1.TabIndex = 2;
            this.button1.Text = "Test";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(934, 561);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.btnListKH);
            this.Controls.Add(this.btnKhachHang);
            this.Name = "MainForm";
            this.Text = "Quản Lý Phòng Khám";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btnKhachHang;
        private System.Windows.Forms.Button btnListKH;
        private System.Windows.Forms.Button button1;
    }
}

