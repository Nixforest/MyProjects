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
    public partial class FrmNhapKH : Form
    {
        public FrmNhapKH()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Visible = false;
            FrmNhapKH1 form = new FrmNhapKH1(this);
            form.Show();
        }
    }
}
