using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace logmanager
{
    public class LogManagement
    {
        /// <summary>
        /// Class for LOG handle
        /// Log file format:
        /// [Date][FileName][Function][Line][Message]
        /// </summary>
        public static void WriteLogFile(string log)
        {
            try
            {
                using (StreamWriter file = new StreamWriter(GlobalVariable.LOG_FILE_PATH, true))
                {
                    file.WriteLine(log);
                }
            }
            catch (UnauthorizedAccessException)
            {
                MessageBox.Show(GlobalVariable.ERR_LOAD_LOG_FILE_UNAUTHORIZED,
                    GlobalVariable.ERR_ERROR,
                    MessageBoxButtons.OK,
                    MessageBoxIcon.Error);
            }
            catch (DirectoryNotFoundException)
            {
                MessageBox.Show(GlobalVariable.ERR_LOAD_LOG_FILE_DIRECTORY_NOT_FOUND,
                   GlobalVariable.ERR_ERROR,
                   MessageBoxButtons.OK,
                   MessageBoxIcon.Error);
            }
            catch (PathTooLongException)
            {
                MessageBox.Show(GlobalVariable.ERR_LOAD_LOG_FILE_DIRECTORY_NOT_FOUND,
                   GlobalVariable.ERR_ERROR,
                   MessageBoxButtons.OK,
                   MessageBoxIcon.Error);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message,
                   GlobalVariable.ERR_ERROR,
                   MessageBoxButtons.OK,
                   MessageBoxIcon.Error);
            }
        }

        /// <summary>
        /// Write message in format:
        /// [Date][FileName][Function][Line][Message]
        /// </summary>
        /// <param name="fileName">File name</param>
        /// <param name="function">Function name</param>
        /// <param name="line">Line of code</param>
        /// <param name="msg">Message content</param>
        public static void WriteMessageFile(string fileName, string function, int line, string msg)
        {
            string date = String.Format(GlobalVariable.DATE_TIME_FORMAT, DateTime.Now);
            string log = String.Format(
                GlobalVariable.LOG_CONTENT_FORMAT,
                date, fileName, function, line, msg);
            WriteLogFile(log);
        }

        /// <summary>
        /// Write message in format:
        /// [Date][FileName][Function][Line][Message]
        /// </summary>
        /// <param name="msg">Message content</param>
        /// <param name="stackTrace">StackTrace object</param>
        public static void WriteMessageFile(string msg, StackTrace stackTrace)
        {
            string fileName = Path.GetFileName(stackTrace.GetFrame(0).GetFileName());
            string function = stackTrace.GetFrame(0).GetMethod().Name;
            int line = stackTrace.GetFrame(0).GetFileLineNumber();
            WriteMessageFile(fileName, function, line, msg);
        }
    }
}
