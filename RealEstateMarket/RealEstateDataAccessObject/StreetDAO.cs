using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to STREET table in database
    /// </summary>
    public class StreetDAO : DataParent<RealEstateDataContext.STREET>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.STREETs.Count();
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
        /// Get all rows in table STREET
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.STREET> GetAllRows()
        {
            return _db.STREETs.ToList();
        }

        /// <summary>
        /// Insert a row into table STREET
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.STREET entity)
        {
            _db.STREETs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table STREET
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.STREET entity)
        {
            RealEstateDataContext.STREET oldEntity = _db.STREETs.Single(record => record.ID == entity.ID);
            oldEntity.Name = entity.Name;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table STREET
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.STREETs
                         where record.ID.Equals(ID)
                         select record;
            _db.STREETs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table STREET
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.STREET GetARecord(int ID)
        {
            var entity = from record in _db.STREETs
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
            if (_db.STREETs.Count() > 0)
            {
                foreach (RealEstateDataContext.STREET entity in _db.STREETs)
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
