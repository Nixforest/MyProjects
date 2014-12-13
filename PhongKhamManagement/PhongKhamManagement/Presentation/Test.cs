using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using PhongKhamManagement.BusinessLogic;

namespace PhongKhamManagement.Presentation
{
    public partial class Test : Form
    {
        private CityBLO db = new CityBLO();
        private short selectedId = 0;
        public Test()
        {
            InitializeComponent();
            dgvCity.DataSource = db.GetAllRows();
        }

        private void btnAddCity_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrWhiteSpace(tbxCityName.Text))
            {
                db.Insert(tbxCityName.Text);
                dgvCity.DataSource = db.GetAllRows();
            }
            else
            {
                MessageBox.Show("Bạn chưa nhập tên Thành phố.", "Lỗi", MessageBoxButtons.OK);
                tbxCityName.Focus();
            }
        }

        private void btnUpdateCity_Click(object sender, EventArgs e)
        {
            if (!String.IsNullOrWhiteSpace(tbxCityName.Text))
            {
                if (selectedId != 0)
                {
                    db.Update(selectedId, tbxCityName.Text);
                    dgvCity.DataSource = db.GetAllRows();
                }
                else
                {
                    MessageBox.Show("Bạn chưa chọn Thành phố để cập nhật.", "Lỗi", MessageBoxButtons.OK);
                }
            }
            else
            {
                MessageBox.Show("Bạn chưa nhập tên Thành phố.", "Lỗi", MessageBoxButtons.OK);
                tbxCityName.Focus();
            }
        }

        private void dgvCity_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            int index = e.RowIndex;
            selectedId = Convert.ToInt16(dgvCity.Rows[index].Cells[0].Value);
            try
            {
                DataAccess.CITY entity = db.GetARow(selectedId);
                tbxCityName.Text = entity.Name;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Lỗi", MessageBoxButtons.OK);
            }

        }

        private void btnDeleteCity_Click(object sender, EventArgs e)
        {
            if (selectedId != 0)
            {
                db.Delete(selectedId);
                dgvCity.DataSource = db.GetAllRows();
            }
            else
            {
                MessageBox.Show("Bạn chưa chọn Thành phố để xóa.", "Lỗi", MessageBoxButtons.OK);
            }
        }
    }
}
