using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace Example2
{
    /// <summary>
    /// This class is a view model of a song.
    /// </summary>
    public class SongViewModel : INotifyPropertyChanged
    {
        #region Construction
        /// <summary>
        /// Constructs the default instance of a SongViewModel
        /// </summary>
        public SongViewModel()
        {
            _song = new Song { ArtistName = "Unknown", SongTitle = "Unknown" };
        }
        #endregion

        #region Members
        Song _song;
        #endregion

        #region Properties
        public Song Song
        {
            get
            {
                return _song;
            }
            set
            {
                _song = value;
            }
        }

        public string ArtistName
        {
            get { return Song.ArtistName; }
            set
            {
                if (Song.ArtistName != value)
                {
                    Song.ArtistName = value;
                    RaisePropertyChange("ArtistName");
                }
            }
        }
        #endregion
        #region INotifyPropertyChanged Members
        public event PropertyChangedEventHandler PropertyChanged;
        #endregion
        #region Methods
        private void RaisePropertyChange(string propertyName)
        { 
            // Take a copy
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(propertyName));
            }
        }
        #endregion
    }
}
