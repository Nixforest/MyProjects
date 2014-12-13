using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace logmanager
{
    /// <summary>
    /// Class Global Variable.
    /// </summary>
    public class GlobalVariable
    {
        #region Config value
        /// <summary>
        /// File path of Log file.
        /// </summary>
        public static string LOG_FILE_PATH = "";

        /// <summary>
        /// Date time format to log file
        /// </summary>
        public static string DATE_TIME_FORMAT = "{0:yyyy/MM/dd HH:mm:ss}";

        /// <summary>
        /// Log content format
        /// </summary>
        public static string LOG_CONTENT_FORMAT = "[{0, -19}][{1, -50}][{2, -50}][{3, 6}] {4}";
        #endregion

        #region Global String
        /// <summary>
        /// Error string
        /// </summary>
        public static string ERR_ERROR = "Error";

        /// <summary>
        /// String: Load config file error
        /// </summary>
        public static string ERR_LOAD_CONFIG_FILE = "Load configuration file error";

        /// <summary>
        /// String: Load log file error: Unanthorized
        /// </summary>
        public static string ERR_LOAD_LOG_FILE_UNAUTHORIZED = "Load configuration file error: Can not access";

        /// <summary>
        /// String: Load log file error: Directory not found
        /// </summary>
        public static string ERR_LOAD_LOG_FILE_DIRECTORY_NOT_FOUND = "Load configuration file error: Directory not found";
        #endregion
    }
}
