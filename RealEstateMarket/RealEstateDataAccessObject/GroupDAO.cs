using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to GROUP table in database
    /// </summary>
    public class GroupDAO : DataParent<RealEstateDataContext.GROUP>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.GROUPs.Count();
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
        /// Get all rows in table group
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.GROUP> GetAllRows()
        {
            return _db.GROUPs.ToList();
        }

        /// <summary>
        /// Insert a row into table GROUP
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.GROUP entity)
        {
            _db.GROUPs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table GROUP
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.GROUP entity)
        {
            RealEstateDataContext.GROUP oldEntity = _db.GROUPs.Single(record => record.ID == entity.ID);

            oldEntity.Name = entity.Name;
            oldEntity.Description = entity.Description;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table GROUP
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.GROUPs
                         where record.ID.Equals(ID)
                         select record;
            _db.GROUPs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table GROUP
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.GROUP GetARecord(int ID)
        {
            var entity = from record in _db.GROUPs
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
            if (_db.GROUPs.Count() > 0)
            {
                foreach (RealEstateDataContext.GROUP entity in _db.GROUPs)
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
