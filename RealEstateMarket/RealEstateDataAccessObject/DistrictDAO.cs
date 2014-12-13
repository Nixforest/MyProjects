using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    public class DistrictDAO: DataParent<RealEstateDataContext.DISTRICT>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.DISTRICTs.Count();
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
        /// Get all rows in table DISTRICT
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.DISTRICT> GetAllRows()
        {
            return _db.DISTRICTs.ToList();
        }

        /// <summary>
        /// Insert a row into table DISTRICT
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.DISTRICT entity)
        {
            _db.DISTRICTs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table DISTRICT
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.DISTRICT entity)
        {
            RealEstateDataContext.DISTRICT oldEntity = _db.DISTRICTs.Single(record => record.ID == entity.ID);
            oldEntity.Name = entity.Name;
            oldEntity.CityID = entity.CityID;
            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table DISTRICT
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.DISTRICTs
                         where record.ID.Equals(ID)
                         select record;
            _db.DISTRICTs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table DISTRICT
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.DISTRICT GetARecord(int ID)
        {
            var entity = from record in _db.DISTRICTs
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
            if (_db.DISTRICTs.Count() > 0)
            {
                foreach (RealEstateDataContext.DISTRICT entity in _db.DISTRICTs)
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
