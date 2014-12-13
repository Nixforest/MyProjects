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
    public partial class FrmNhapKH1 : Form
    {
        private FrmNhapKH m_FrmNhapKH;
        public FrmNhapKH1(FrmNhapKH frmNhapKH)
        {
            this.m_FrmNhapKH = frmNhapKH;
            InitializeComponent();
        }

        private void btnBack_Click(object sender, EventArgs e)
        {
            this.Visible = false;
            this.m_FrmNhapKH.Visible = true;
        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void checkBox14_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void checkBox11_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            this.Close();
            this.m_FrmNhapKH.Close();
        }
    }
}
