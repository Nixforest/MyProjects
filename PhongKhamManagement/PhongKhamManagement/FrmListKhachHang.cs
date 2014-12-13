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
    public partial class FrmListKhachHang : Form
    {
        public FrmListKhachHang()
        {
            InitializeComponent();
        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            DataGridViewRow row = new DataGridViewRow();
            DataGridViewCell cell = new DataGridViewTextBoxCell();
            cell.Value = "1";
            row.Cells.Add(cell);
            DataGridViewCell cell2 = new DataGridViewTextBoxCell();
            cell2.Value = "KH150713001";
            row.Cells.Add(cell2);
            DataGridViewCell cell3 = new DataGridViewTextBoxCell();
            cell3.Value = "Hoàng Văn Nam";
            row.Cells.Add(cell3);
            DataGridViewCell cell4 = new DataGridViewTextBoxCell();
            cell4.Value = "03/07/1987";
            row.Cells.Add(cell4);
            DataGridViewCell cell5 = new DataGridViewTextBoxCell();
            cell5.Value = "Nam";
            row.Cells.Add(cell5);
            DataGridViewCell cell6 = new DataGridViewTextBoxCell();
            cell6.Value = "33 Tôn Đức Thắng - Bình Dương";
            row.Cells.Add(cell6);
            DataGridViewCell cell7 = new DataGridViewTextBoxCell();
            cell7.Value = "01686534271";
            row.Cells.Add(cell7);
            DataGridViewCell cell8 = new DataGridViewTextBoxCell();
            cell8.Value = "namhv@gmail.com";
            row.Cells.Add(cell8);
            DataGridViewCell cell9 = new DataGridViewTextBoxCell();
            cell9.Value = "158478563";
            row.Cells.Add(cell9);
            DataGridViewCell cell10 = new DataGridViewTextBoxCell();
            cell10.Value = "Cán Bộ";
            row.Cells.Add(cell10);
            DataGridViewCell cell11 = new DataGridViewTextBoxCell();
            cell11.Value = "11";
            row.Cells.Add(cell11);
            DataGridViewCell cell12 = new DataGridViewTextBoxCell();
            cell12.Value = "12";
            row.Cells.Add(cell12);
            dgvUsers.Rows.Add(row);
            
        }

        private void dgvUsers_CellMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            FrmChiTietKH form = new FrmChiTietKH();
            form.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            FrmNhapKH frm = new FrmNhapKH();
            frm.Show();
        }
    }
}
