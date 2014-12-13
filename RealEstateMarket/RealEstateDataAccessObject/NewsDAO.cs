using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to NEWS table in database
    /// </summary>
    public class NewsDAO : DataParent<RealEstateDataContext.NEW>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.NEWs.Count();
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
        /// Get all rows in table NEWS
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.NEW> GetAllRows()
        {
            return _db.NEWs.ToList();
        }

        /// <summary>
        /// Insert a row into table NEWS
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.NEW entity)
        {
            _db.NEWs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table NEWS
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.NEW entity)
        {
            RealEstateDataContext.NEW oldEntity = _db.NEWs.Single(record => record.ID == entity.ID);
            oldEntity.TypeID = entity.TypeID;
            oldEntity.Title = entity.Title;
            oldEntity.Content = entity.Content;
            oldEntity.Author = entity.Author;
            oldEntity.Rate = entity.Rate;
            oldEntity.PublishTime = entity.PublishTime;
            oldEntity.ImageID = entity.ImageID;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table NEWS
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.NEWs
                         where record.ID.Equals(ID)
                         select record;
            _db.NEWs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table NEWS
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.NEW GetARecord(int ID)
        {
            var entity = from record in _db.NEWs
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
            if (_db.NEWs.Count() > 0)
            {
                foreach (RealEstateDataContext.NEW entity in _db.NEWs)
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
