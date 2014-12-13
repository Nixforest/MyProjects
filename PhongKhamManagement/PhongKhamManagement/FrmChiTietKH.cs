using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace PhongKhamManagement
{
    public partial class FrmChiTietKH : Form
    {
        public FrmChiTietKH()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void FrmChiTietKH_Load(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {


        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            FrmNhapKH frm = new FrmNhapKH();
            frm.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            DataGridViewRow row = new DataGridViewRow();
            DataGridViewCell cell = new DataGridViewTextBoxCell();
            cell.Value = "15/07/2013";
            row.Cells.Add(cell);
            DataGridViewCell cell2 = new DataGridViewTextBoxCell();
            cell2.Value = "48";
            row.Cells.Add(cell2);
            DataGridViewCell cell3 = new DataGridViewTextBoxCell();
            cell3.Value = "Đặt AS bọc 1 sứ Titan";
            row.Cells.Add(cell3);
            DataGridViewCell cell4 = new DataGridViewTextBoxCell();
            cell4.Value = "1500";
            row.Cells.Add(cell4);
            DataGridViewCell cell5 = new DataGridViewTextBoxCell();
            cell5.Value = "1000";
            row.Cells.Add(cell5);
            DataGridViewCell cell6 = new DataGridViewTextBoxCell();
            cell6.Value = "500";
            row.Cells.Add(cell6);
            DataGridViewCell cell7 = new DataGridViewTextBoxCell();
            cell7.Value = "Huyền Linh";
            row.Cells.Add(cell7);
            DataGridViewCell cell8 = new DataGridViewTextBoxCell();
            cell8.Value = "Tuấn";
            row.Cells.Add(cell8);
            DataGridViewCell cell9 = new DataGridViewTextBoxCell();
            cell9.Value = "18/07/2013";
            row.Cells.Add(cell9);
            dgvTreatmentDetail.Rows.Add(row);
        }
    }
}
