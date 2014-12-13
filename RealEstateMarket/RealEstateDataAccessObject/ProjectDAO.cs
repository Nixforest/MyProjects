using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to PROJECT table in database
    /// </summary>
    public class ProjectDAO: DataParent<RealEstateDataContext.PROJECT>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.PROJECTs.Count();
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
        /// Get all rows in table PROJECT
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.PROJECT> GetAllRows()
        {
            return _db.PROJECTs.ToList();
        }

        /// <summary>
        /// Insert a row into table PROJECT
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.PROJECT entity)
        {
            _db.PROJECTs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table PROJECT
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.PROJECT entity)
        {
            RealEstateDataContext.PROJECT oldEntity = _db.PROJECTs.Single(record => record.ID == entity.ID);
            oldEntity.TypeID = entity.TypeID;
            oldEntity.Name = entity.Name;
            oldEntity.BeginDay = entity.BeginDay;
            oldEntity.AddressID = entity.AddressID;
            oldEntity.Description = entity.Description;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table PROJECT
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.PROJECTs
                         where record.ID.Equals(ID)
                         select record;
            _db.PROJECTs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table PROJECT
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.PROJECT GetARecord(int ID)
        {
            var entity = from record in _db.PROJECTs
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
            if (_db.PROJECTs.Count() > 0)
            {
                foreach (RealEstateDataContext.PROJECT entity in _db.PROJECTs)
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
