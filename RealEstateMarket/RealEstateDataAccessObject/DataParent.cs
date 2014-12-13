using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    public class DataParent<T>
    {
        protected static RealEstateDataContext.RealEstateDataClassesDataContext 
            _db = new RealEstateDataContext.RealEstateDataClassesDataContext(RealEstateDataContext.Utility.WebConfig.MSSQL);

        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public virtual int CreateID(){return 0;}

        /// <summary>
        /// Get all rows in table
        /// </summary>
        /// <returns>List of entity</returns>
        public virtual ICollection<T> GetAllRows() { return null; }

        /// <summary>
        /// Insert a row to table
        /// </summary>
        /// <param name="entity">Entity</param>
        public virtual void Insert(T entity) { }

        /// <summary>
        /// Update a row to table
        /// </summary>
        /// <param name="entity">Entity</param>
        public virtual void Update(T entity) { }

        /// <summary>
        /// Delete a row in table
        /// </summary>
        /// <param name="ID">ID of row</param>
        public virtual void Delete(int ID) { }

        /// <summary>
        /// Get a row in table
        /// </summary>
        /// <param name="ID">ID of Row</param>
        /// <returns>Entity</returns>
        public virtual T GetARecord(int ID) { return default(T); }

        /// <summary>
        /// Check an ID exist in table or not
        /// </summary>
        /// <param name="ID">ID need to check</param>
        /// <returns>True if ID has exist, false otherwise</returns>
        public virtual bool ValidationID(int ID) { return true; }
    }
}
