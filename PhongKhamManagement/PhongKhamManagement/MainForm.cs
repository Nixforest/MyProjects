using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PhongKhamManagement.Presentation;

namespace PhongKhamManagement
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void btnKhachHang_Click(object sender, EventArgs e)
        {
            FrmNhapKH form = new FrmNhapKH();
            form.Show();
        }

        private void btnListKH_Click(object sender, EventArgs e)
        {
            FrmListKhachHang form = new FrmListKhachHang();
            form.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Test form = new Test();
            form.Show();
        }
    }
}
