using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    public class News_SaleDAO : DataParent<RealEstateDataContext.NEWS_SALE>
    {
        /// <summary>
        /// Class access to NEWS_SALE table in database
        /// </summary>
        public override int CreateID()
        {
            /// <summary>
            /// Create a new ID for new entity in table
            /// </summary>
            /// <returns>ID just create.</returns>
            int numberRecord;
            int value;
            numberRecord = _db.NEWS_SALEs.Count();
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
        /// Get all rows in table NEWS_SALE
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.NEWS_SALE> GetAllRows()
        {
            return _db.NEWS_SALEs.ToList();
        }

        /// <summary>
        /// Insert a row into table NEWS_SALE
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.NEWS_SALE entity)
        {
            _db.NEWS_SALEs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table NEWS_SALE
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.NEWS_SALE entity)
        {
            RealEstateDataContext.NEWS_SALE oldEntity = _db.NEWS_SALEs.Single(record => record.ID == entity.ID);
            oldEntity.TypeID = entity.TypeID;
            oldEntity.Title = entity.Title;
            oldEntity.Content = entity.Content;
            oldEntity.RealEstateID = entity.RealEstateID;
            oldEntity.Rate = entity.Rate;
            oldEntity.UpdateTime = entity.UpdateTime;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table NEWS_SALE
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.NEWS_SALEs
                         where record.ID.Equals(ID)
                         select record;
            _db.NEWS_SALEs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table NEWS_SALE
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.NEWS_SALE GetARecord(int ID)
        {
            var entity = from record in _db.NEWS_SALEs
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
            if (_db.NEWS_SALEs.Count() > 0)
            {
                foreach (RealEstateDataContext.NEWS_SALE entity in _db.NEWS_SALEs)
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
