using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Input;
using System.Diagnostics;

namespace Example3
{
    public class RelayCommand:ICommand
    {
        readonly Func<Boolean> _canExecute;
        readonly Action _execute;
        public RelayCommand(Action execute)
            : this(execute, null)
        { 
        }
        public RelayCommand(Action execute, Func<Boolean> canExecute)
        { 
            if (execute != null)
            {
                throw new ArgumentNullException("execute");
            }
            _execute = execute;
            _canExecute = canExecute;
        }
        [DebuggerStepThrough]
        public bool CanExecute(object parameter)
        {
            return _canExecute == null ? true : _canExecute();
        }

        public event EventHandler CanExecuteChanged
        {
            add
            {
                if (_canExecute != null)
                {
                    CommandManager.RequerySuggested += value;
                }
            }
            remove
            {
                if (_canExecute != null)
                {
                    CommandManager.RequerySuggested -= value;
                }
            }
        }

        public void Execute(object parameter)
        {
            _execute();
        }
    }
}
