using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using RealEstateDataContext;
using System.Collections.ObjectModel;

namespace RealEstateDataAccessObject
{
    public class NationDAO: DataParent<NATION>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.NATIONs.Count();
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
        /// Get all rows in table NATION
        /// </summary>
        /// <returns>List of Nation</returns>
        public override ICollection<NATION> GetAllRows()
        {
            return _db.NATIONs.ToList();
        }

        /// <summary>
        /// Insert a entity
        /// </summary>
        /// <param name="entity">A Nation entity</param>
        public override void Insert(NATION entity)
        {
            _db.NATIONs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a entity
        /// </summary>
        /// <param name="entity">A Nation entity</param>
        public override void Update(NATION entity)
        {
            NATION oldEntity = _db.NATIONs.Single(record => record.ID == entity.ID);
            oldEntity.Name = entity.Name;
            oldEntity.NationCode = entity.NationCode;
            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row
        /// </summary>
        /// <param name="ID">ID of Nation</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.NATIONs
                         where record.ID.Equals(ID)
                         select record;
            _db.NATIONs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row
        /// </summary>
        /// <param name="ID">ID of Nation</param>
        /// <returns>A Nation Entity</returns>
        public override NATION GetARecord(int ID)
        {
            var entity = from record in _db.NATIONs
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
            if (_db.NATIONs.Count() > 0)
            {
                foreach (RealEstateDataContext.NATION entity in _db.NATIONs)
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
