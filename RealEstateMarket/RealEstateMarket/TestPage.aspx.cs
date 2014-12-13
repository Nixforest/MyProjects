using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using RealEstateBusinessLogicObject;
using RealEstateDataContext;

namespace RealEstateMarket
{
    public partial class TestPage : System.Web.UI.Page
    {

        private NationBLO _db;
        protected void Page_Load(object sender, EventArgs e)
        {
            RealEstateDataContext.Utility.WebConfig.MSSQL = @"Data Source=.\SQLEXPRESS;Initial Catalog=RealEstate;Integrated Security=True";
            _db = new NationBLO();
            listNationX.DataSource = _db.GetAllRows();
            listNationX.DataBind();
            try
            {
                new RealEstateBusinessLogicObject.AddressBLO().Insert(new RealEstateDataContext.ADDRESS());
            }
            catch (Exception)
            {
                
                throw;
            }
         
        }

        protected void btnInsert_Click(object sender, EventArgs e)
        {
            if (txbName.Text != "" && txbCode.Text != "")
            {
                _db.Insert(txbName.Text, txbCode.Text);
            }
            listNationX.DataSource = _db.GetAllRows();
            listNationX.DataBind();
        }
    }
}