using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to GROUP_DETAIL table in database
    /// </summary>
    public class Group_DetailDAO : DataParent<RealEstateDataContext.GROUP_DETAIL>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.GROUP_DETAILs.Count();
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
        /// Get all rows in table GROUP_DETAIL
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.GROUP_DETAIL> GetAllRows()
        {
            return _db.GROUP_DETAILs.ToList();
        }

        /// <summary>
        /// Insert a row into table GROUP_DETAIL
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.GROUP_DETAIL entity)
        {
            _db.GROUP_DETAILs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table GROUP_DETAIL
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.GROUP_DETAIL entity)
        {
            RealEstateDataContext.GROUP_DETAIL oldEntity = _db.GROUP_DETAILs.Single(record => record.ID == entity.ID);
            oldEntity.GroupID = entity.GroupID;
            oldEntity.RuleID = entity.RuleID;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table GROUP_DETAIL
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.GROUP_DETAILs
                         where record.ID.Equals(ID)
                         select record;
            _db.GROUP_DETAILs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table GROUP_DETAIL
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.GROUP_DETAIL GetARecord(int ID)
        {
            var entity = from record in _db.GROUP_DETAILs
                         where record.ID.Equals(ID)
                         select record;
            return entity.Single();
        }
    }
}
