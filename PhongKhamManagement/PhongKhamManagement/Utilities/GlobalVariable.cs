using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace PhongKhamManagement.Utilities
{
    /// <summary>
    /// Class Global Variable
    /// </summary>
    public class GlobalVariable
    {
        /// <summary>
        /// Connection string for SaiGonDental database
        /// </summary>
        public static string CONNECTION_STRING =
            "Data Source=.\\SQLEXPRESS;Initial Catalog=SaiGonDental;Integrated Security=True";

        /// <summary>
        /// Data context for SaiGonDental database
        /// </summary>
        public static DataAccess.Database_ConnectionDataContext DATA_CONTEXT =
            new DataAccess.Database_ConnectionDataContext(CONNECTION_STRING);

        #region Global String
        /// <summary>
        /// Invalid Id string
        /// </summary>
        public static string INVALID_ID = "Id is invalid";
        #endregion
    }
}
