namespace PhongKhamManagement.Presentation
{
    partial class Test
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
            this.dgvCity = new System.Windows.Forms.DataGridView();
            this.btnAddCity = new System.Windows.Forms.Button();
            this.tbxCityName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btnUpdateCity = new System.Windows.Forms.Button();
            this.btnDeleteCity = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dgvCity)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvCity
            // 
            this.dgvCity.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvCity.Location = new System.Drawing.Point(13, 13);
            this.dgvCity.Name = "dgvCity";
            this.dgvCity.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dgvCity.Size = new System.Drawing.Size(510, 150);
            this.dgvCity.TabIndex = 0;
            this.dgvCity.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dgvCity_CellClick);
            // 
            // btnAddCity
            // 
            this.btnAddCity.Location = new System.Drawing.Point(331, 173);
            this.btnAddCity.Name = "btnAddCity";
            this.btnAddCity.Size = new System.Drawing.Size(75, 23);
            this.btnAddCity.TabIndex = 1;
            this.btnAddCity.Text = "&Thêm";
            this.btnAddCity.UseVisualStyleBackColor = true;
            this.btnAddCity.Click += new System.EventHandler(this.btnAddCity_Click);
            // 
            // tbxCityName
            // 
            this.tbxCityName.Location = new System.Drawing.Point(99, 175);
            this.tbxCityName.Name = "tbxCityName";
            this.tbxCityName.Size = new System.Drawing.Size(196, 20);
            this.tbxCityName.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 178);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(81, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Tên Thành phố";
            // 
            // btnUpdateCity
            // 
            this.btnUpdateCity.Location = new System.Drawing.Point(425, 172);
            this.btnUpdateCity.Name = "btnUpdateCity";
            this.btnUpdateCity.Size = new System.Drawing.Size(75, 23);
            this.btnUpdateCity.TabIndex = 4;
            this.btnUpdateCity.Text = "Cập nhật";
            this.btnUpdateCity.UseVisualStyleBackColor = true;
            this.btnUpdateCity.Click += new System.EventHandler(this.btnUpdateCity_Click);
            // 
            // btnDeleteCity
            // 
            this.btnDeleteCity.Location = new System.Drawing.Point(331, 203);
            this.btnDeleteCity.Name = "btnDeleteCity";
            this.btnDeleteCity.Size = new System.Drawing.Size(75, 23);
            this.btnDeleteCity.TabIndex = 5;
            this.btnDeleteCity.Text = "Xóa";
            this.btnDeleteCity.UseVisualStyleBackColor = true;
            this.btnDeleteCity.Click += new System.EventHandler(this.btnDeleteCity_Click);
            // 
            // Test
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(535, 310);
            this.Controls.Add(this.btnDeleteCity);
            this.Controls.Add(this.btnUpdateCity);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tbxCityName);
            this.Controls.Add(this.btnAddCity);
            this.Controls.Add(this.dgvCity);
            this.Name = "Test";
            this.Text = "Test";
            ((System.ComponentModel.ISupportInitialize)(this.dgvCity)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dgvCity;
        private System.Windows.Forms.Button btnAddCity;
        private System.Windows.Forms.TextBox tbxCityName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btnUpdateCity;
        private System.Windows.Forms.Button btnDeleteCity;
    }
}