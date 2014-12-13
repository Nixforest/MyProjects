using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to PROPERTY_CUSTOMER table in database
    /// </summary>
    public class Property_CustomerDAO: DataParent<RealEstateDataContext.PROPERTY_CUSTOMER>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.PROPERTY_CUSTOMERs.Count();
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
        /// Get all rows in table PROPERTY_CUSTOMER
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.PROPERTY_CUSTOMER> GetAllRows()
        {
            return _db.PROPERTY_CUSTOMERs.ToList();
        }

        /// <summary>
        /// Insert a row into table PROPERTY_CUSTOMER
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.PROPERTY_CUSTOMER entity)
        {
            _db.PROPERTY_CUSTOMERs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table PROPERTY_CUSTOMER
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.PROPERTY_CUSTOMER entity)
        {
            RealEstateDataContext.PROPERTY_CUSTOMER oldEntity = _db.PROPERTY_CUSTOMERs.Single(record => record.ID == entity.ID);
            oldEntity.CustomerID = entity.CustomerID;
            oldEntity.RealEstateID = entity.RealEstateID;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table PROPERTY_CUSTOMER
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.PROPERTY_CUSTOMERs
                         where record.ID.Equals(ID)
                         select record;
            _db.PROPERTY_CUSTOMERs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table PROPERTY_CUSTOMER
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.PROPERTY_CUSTOMER GetARecord(int ID)
        {
            var entity = from record in _db.PROPERTY_CUSTOMERs
                         where record.ID.Equals(ID)
                         select record;
            return entity.Single();
        }
    }
}
