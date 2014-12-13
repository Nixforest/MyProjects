using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to CITY table in database
    /// </summary>
    public class CityDAO: DataParent<RealEstateDataContext.CITY>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.CITies.Count();
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
        public override ICollection<RealEstateDataContext.CITY> GetAllRows()
        {
            return _db.CITies.ToList();
        }

        /// <summary>
        /// Insert a row into table CITY
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.CITY entity)
        {
            _db.CITies.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table CITY
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.CITY entity)
        {
            RealEstateDataContext.CITY oldEntity = _db.CITies.Single(record => record.ID == entity.ID);
            oldEntity.Name = entity.Name;
            oldEntity.NationID = entity.NationID;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table CITY
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.CITies
                         where record.ID.Equals(ID)
                         select record;
            _db.CITies.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table CITY
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.CITY GetARecord(int ID)
        {
            var entity = from record in _db.CITies
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
            if (_db.CITies.Count() > 0)
            {
                foreach (RealEstateDataContext.CITY entity in _db.CITies)
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
