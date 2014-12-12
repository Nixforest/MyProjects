using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using logmanager;
using System.Diagnostics;

namespace DataBindingWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            logmanager.GlobalVariable.LOG_FILE_PATH = Properties.Settings.Default.LOGFILEPATH;
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            logmanager.LogManagement.WriteMessageFile("Click button 1", new StackTrace(new StackFrame(true)));
        }
    }
}
