using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to DISTRICT_DETAIL table in database
    /// </summary>
    public class District_DetailDAO : DataParent<RealEstateDataContext.DISTRICT_DETAIL>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.DISTRICT_DETAILs.Count();
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
        /// Get all rows in table CITY
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.DISTRICT_DETAIL> GetAllRows()
        {
            return _db.DISTRICT_DETAILs.ToList();
        }

        /// <summary>
        /// Insert a row into table DISTRICT_DETAIL
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.DISTRICT_DETAIL entity)
        {
            _db.DISTRICT_DETAILs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table DISTRICT_DETAIL
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.DISTRICT_DETAIL entity)
        {
            RealEstateDataContext.DISTRICT_DETAIL oldEntity = _db.DISTRICT_DETAILs.Single(record => record.ID == entity.ID);
            oldEntity.DistrictID = entity.DistrictID;
            oldEntity.StreetID = entity.StreetID;
            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table DISTRICT_DETAIL
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.DISTRICT_DETAILs
                         where record.ID.Equals(ID)
                         select record;
            _db.DISTRICT_DETAILs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table DISTRICT_DETAIL
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.DISTRICT_DETAIL GetARecord(int ID)
        {
            var entity = from record in _db.DISTRICT_DETAILs
                         where record.ID.Equals(ID)
                         select record;
            return entity.Single();
        }
    }
}
