using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to UTILITY table in database
    /// </summary>
    public class UtilityDAO : DataParent<RealEstateDataContext.UTILITY>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.UTILITies.Count();
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
        /// Get all rows in table UTILITY
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.UTILITY> GetAllRows()
        {
            return _db.UTILITies.ToList();
        }

        /// <summary>
        /// Insert a row into table UTILITY
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.UTILITY entity)
        {
            _db.UTILITies.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table UTILITY
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.UTILITY entity)
        {
            RealEstateDataContext.UTILITY oldEntity = _db.UTILITies.Single(record => record.ID == entity.ID);
            oldEntity.Name = entity.Name;
            oldEntity.Description = entity.Description;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table UTILITY
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.UTILITies
                         where record.ID.Equals(ID)
                         select record;
            _db.UTILITies.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table UTILITY
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.UTILITY GetARecord(int ID)
        {
            var entity = from record in _db.UTILITies
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
            if (_db.UTILITies.Count() > 0)
            {
                foreach (RealEstateDataContext.UTILITY entity in _db.UTILITies)
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
