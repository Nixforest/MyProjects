using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to PROPERTY_COMPANY table in database
    /// </summary>
    public class Property_CompanyDAO:DataParent<RealEstateDataContext.PROPERTY_COMPANY>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.PROPERTY_COMPANies.Count();
            if (numberRecord == 0)
            {
                value = 1;
            }
            else
            {
                value = numberRecord + 1;
            }
            return value;
        }

        /// <summary>
        /// Get all rows in table PROPERTY_COMPANY
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.PROPERTY_COMPANY> GetAllRows()
        {
            return _db.PROPERTY_COMPANies.ToList();
        }

        /// <summary>
        /// Insert a row into table PROPERTY_COMPANY
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.PROPERTY_COMPANY entity)
        {
            _db.PROPERTY_COMPANies.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table PROPERTY_COMPANY
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.PROPERTY_COMPANY entity)
        {
            RealEstateDataContext.PROPERTY_COMPANY oldEntity = _db.PROPERTY_COMPANies.Single(record => record.ID == entity.ID);
            oldEntity.CompanyID = entity.CompanyID;
            oldEntity.RealEstateID = entity.RealEstateID;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table PROPERTY_COMPANY
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.PROPERTY_COMPANies
                         where record.ID.Equals(ID)
                         select record;
            _db.PROPERTY_COMPANies.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table PROPERTY_COMPANY
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.PROPERTY_COMPANY GetARecord(int ID)
        {
            var entity = from record in _db.PROPERTY_COMPANies
                         where record.ID.Equals(ID)
                         select record;
            return entity.Single();
        }
    }
}
