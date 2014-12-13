using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to CUSTOMER table in database
    /// </summary>
    public class CustomerDAO : DataParent<RealEstateDataContext.CUSTOMER>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.CUSTOMERs.Count();
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
        /// Get all rows in table CUSTOMER
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.CUSTOMER> GetAllRows()
        {
            return _db.CUSTOMERs.ToList();
        }

        /// <summary>
        /// Insert a row into table CUSTOMER
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.CUSTOMER entity)
        {
            _db.CUSTOMERs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table CUSTOMER
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.CUSTOMER entity)
        {
            RealEstateDataContext.CUSTOMER oldEntity = _db.CUSTOMERs.Single(record => record.ID == entity.ID);
            oldEntity.Name = entity.Name;
            oldEntity.AddressID = entity.AddressID;
            oldEntity.IdentityCard = entity.IdentityCard;
            oldEntity.Phone = entity.Phone;
            oldEntity.HomePhone = entity.HomePhone;
            oldEntity.Email = entity.Email;
            oldEntity.UserID = entity.UserID;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table CUSTOMER
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.CUSTOMERs
                         where record.ID.Equals(ID)
                         select record;
            _db.CUSTOMERs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table CUSTOMER
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.CUSTOMER GetARecord(int ID)
        {
            var entity = from record in _db.CUSTOMERs
                         where record.ID.Equals(ID)
                         select record;
            return entity.Single();
        }

        /// <summary>
        /// Check an ID exist in table or not
        /// </summary>
        /// <param name="ID">ID need to check</param>
        /// <returns>True if ID has exist, false otherwise</returns>
        public override bool ValidationID(int ID)
        {
            if (_db.CUSTOMERs.Count() > 0)
            {
                foreach (RealEstateDataContext.CUSTOMER entity in _db.CUSTOMERs)
                {
                    if (entity.ID.Equals(ID))
                    {
                        return true;
                    }
                }
            }
            return false;
        }
    }
}
