using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateBusinessLogicObject
{
    public class BusinessParent<T>
    {
        protected RealEstateDataAccessObject.DataParent<T> _db;

        public virtual ICollection<T> GetAllRows() { return null; }
        public virtual int Insert(T entity) { return 0; }
        public virtual int Update(T entity) { return 0; }
        public virtual void Delete(int ID) { }
        public virtual T GetARecord(int ID) { return default(T); }

        /// <summary>
        /// Check an ID exist in table or not
        /// </summary>
        /// <param name="ID">ID need to check</param>
        /// <returns>True if ID has exist, false otherwise</returns>
        public virtual bool ValidationID(int ID) { return _db.ValidationID(ID); }
    }
}
