using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to UNIT_PRICE table in database
    /// </summary>
    public class Unit_PriceDAO : DataParent<RealEstateDataContext.UNIT_PRICE>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.UNIT_PRICEs.Count();
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
        /// Get all rows in table UNIT_PRICE
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.UNIT_PRICE> GetAllRows()
        {
            return _db.UNIT_PRICEs.ToList();
        }

        /// <summary>
        /// Insert a row into table UNIT_PRICE
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.UNIT_PRICE entity)
        {
            _db.UNIT_PRICEs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table UNIT_PRICE
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.UNIT_PRICE entity)
        {
            RealEstateDataContext.UNIT_PRICE oldEntity = _db.UNIT_PRICEs.Single(record => record.ID == entity.ID);
            oldEntity.Name = entity.Name;
            oldEntity.Description = entity.Description;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table UNIT_PRICE
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.UNIT_PRICEs
                         where record.ID.Equals(ID)
                         select record;
            _db.UNIT_PRICEs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table UNIT_PRICE
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.UNIT_PRICE GetARecord(int ID)
        {
            var entity = from record in _db.UNIT_PRICEs
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
            if (_db.UNIT_PRICEs.Count() > 0)
            {
                foreach (RealEstateDataContext.UNIT_PRICE entity in _db.UNIT_PRICEs)
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
