using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to NEWS_TYPE table in database
    /// </summary>
    public class News_TypeDAO : DataParent<RealEstateDataContext.NEWS_TYPE>
    {
        public override int CreateID()
        {
            /// <summary>
            /// Create a new ID for new entity in table
            /// </summary>
            /// <returns>ID just create.</returns>
            int numberRecord;
            int value;
            numberRecord = _db.NEWS_TYPEs.Count();
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
        /// Get all rows in table NEWS_TYPE
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.NEWS_TYPE> GetAllRows()
        {
            return _db.NEWS_TYPEs.ToList();
        }

        /// <summary>
        /// Insert a row into table NEWS_TYPE
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.NEWS_TYPE entity)
        {
            _db.NEWS_TYPEs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table NEWS_TYPE
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.NEWS_TYPE entity)
        {
            RealEstateDataContext.NEWS_TYPE oldEntity = _db.NEWS_TYPEs.Single(record => record.ID == entity.ID);
            oldEntity.Name = entity.Name;
            oldEntity.Description = entity.Description;
            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table NEWS_TYPE
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.NEWS_TYPEs
                         where record.ID.Equals(ID)
                         select record;
            _db.NEWS_TYPEs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table NEWS_TYPE
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.NEWS_TYPE GetARecord(int ID)
        {
            var entity = from record in _db.NEWS_TYPEs
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
            if (_db.NEWS_TYPEs.Count() > 0)
            {
                foreach (RealEstateDataContext.NEWS_TYPE entity in _db.NEWS_TYPEs)
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
