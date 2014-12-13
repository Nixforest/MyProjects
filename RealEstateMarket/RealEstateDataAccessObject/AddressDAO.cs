using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to ADDRESS table in database
    /// </summary>
    public class AddressDAO : DataParent<RealEstateDataContext.ADDRESS>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.ADDRESSes.Count();
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
        /// Get all rows in table ADDRESS
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.ADDRESS> GetAllRows()
        {
            return _db.ADDRESSes.ToList();
        }

        /// <summary>
        /// Insert a row into table ADDRESS
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.ADDRESS entity)
        {
            _db.ADDRESSes.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table ADDRESS
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.ADDRESS entity)
        {
            RealEstateDataContext.ADDRESS oldEntity = _db.ADDRESSes.Single(record => record.ID == entity.ID);
            oldEntity.NationID = entity.NationID;
            oldEntity.CityID = entity.CityID;
            oldEntity.DistrictID = entity.DistrictID;
            oldEntity.WardID = entity.WardID;
            oldEntity.StreetID = entity.StreetID;
            oldEntity.Detail = entity.Detail;
            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table ADDRESS
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.ADDRESSes
                         where record.ID.Equals(ID)
                         select record;
            _db.ADDRESSes.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table ADDRESS
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.ADDRESS GetARecord(int ID)
        {
            var entity = from record in _db.ADDRESSes
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
            if (_db.ADDRESSes.Count() > 0)
            {
                foreach (RealEstateDataContext.ADDRESS entity in _db.ADDRESSes)
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
