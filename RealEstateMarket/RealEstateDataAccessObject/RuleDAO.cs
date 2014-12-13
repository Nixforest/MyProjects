using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to RULE table in database
    /// </summary>
    public class RuleDAO : DataParent<RealEstateDataContext.RULE>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.RULEs.Count();
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
        /// Get all rows in table RULE
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.RULE> GetAllRows()
        {
            return _db.RULEs.ToList();
        }

        /// <summary>
        /// Insert a row into table RULE
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.RULE entity)
        {
            _db.RULEs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table RULE
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.RULE entity)
        {
            RealEstateDataContext.RULE oldEntity = _db.RULEs.Single(record => record.ID == entity.ID);
            oldEntity.Name = entity.Name;
            oldEntity.Description = entity.Description;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table RULE
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.RULEs
                         where record.ID.Equals(ID)
                         select record;
            _db.RULEs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table RULE
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.RULE GetARecord(int ID)
        {
            var entity = from record in _db.RULEs
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
            if (_db.RULEs.Count() > 0)
            {
                foreach (RealEstateDataContext.RULE entity in _db.RULEs)
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
