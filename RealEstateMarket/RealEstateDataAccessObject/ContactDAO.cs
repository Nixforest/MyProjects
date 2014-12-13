using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to CONTACT table in database
    /// </summary>
    public class ContactDAO : DataParent<RealEstateDataContext.CONTACT>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.CONTACTs.Count();
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
        /// Get all rows in table CONTACT
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.CONTACT> GetAllRows()
        {
            return _db.CONTACTs.ToList();
        }

        /// <summary>
        /// Insert a row into table CONTACT
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.CONTACT entity)
        {
            _db.CONTACTs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table CONTACT
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.CONTACT entity)
        {
            RealEstateDataContext.CONTACT oldEntity = _db.CONTACTs.Single(record => record.ID == entity.ID);

            oldEntity.Name = entity.Name;
            oldEntity.AddressID = entity.AddressID;
            oldEntity.Phone = entity.Phone;
            oldEntity.HomePhone = entity.HomePhone;
            oldEntity.Note = entity.Note;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table CONTACT
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.CONTACTs
                         where record.ID.Equals(ID)
                         select record;
            _db.CONTACTs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table CONTACT
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.CONTACT GetARecord(int ID)
        {
            var entity = from record in _db.CONTACTs
                         where record.ID.Equals(ID)
                         select record;
            return entity.Single();
        }
    }
}
