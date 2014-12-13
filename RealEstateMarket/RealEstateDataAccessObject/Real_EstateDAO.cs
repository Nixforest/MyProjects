using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to REAL_ESTATE table in database
    /// </summary>
    public class Real_EstateDAO: DataParent<RealEstateDataContext.REAL_ESTATE>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.REAL_ESTATEs.Count();
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
        /// Get all rows in table REAL_ESTATE
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.REAL_ESTATE> GetAllRows()
        {
            return _db.REAL_ESTATEs.ToList();
        }

        /// <summary>
        /// Insert a row into table REAL_ESTATE
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.REAL_ESTATE entity)
        {
            _db.REAL_ESTATEs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table REAL_ESTATE
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.REAL_ESTATE entity)
        {
            RealEstateDataContext.REAL_ESTATE oldEntity = _db.REAL_ESTATEs.Single(record => record.ID == entity.ID);
            oldEntity.TypeID = entity.TypeID;
            oldEntity.AddressID = entity.AddressID;
            oldEntity.LivingRoom = entity.LivingRoom;
            oldEntity.BedRoom = entity.BedRoom;
            oldEntity.BathRoom = entity.BathRoom;
            oldEntity.Storey = entity.Storey;
            oldEntity.TotalUseArea = entity.TotalUseArea;
            oldEntity.CampusFront = entity.CampusFront;
            oldEntity.CampusBehind = entity.CampusBehind;
            oldEntity.CampusLength = entity.CampusLength;
            oldEntity.BuildFront = entity.BuildFront;
            oldEntity.BuildBehind = entity.BuildBehind;
            oldEntity.BuildLength = entity.BuildLength;
            oldEntity.Legal = entity.Legal;
            oldEntity.Direction = entity.Direction;
            oldEntity.FrontStreet = entity.FrontStreet;
            oldEntity.Location = entity.Location;
            oldEntity.Price = entity.Price;
            oldEntity.UnitID = entity.UnitID;
            oldEntity.UnitPriceID = entity.UnitPriceID;
            oldEntity.ProjectID = entity.ProjectID;
            oldEntity.ContactID = entity.ContactID;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table REAL_ESTATE
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.REAL_ESTATEs
                         where record.ID.Equals(ID)
                         select record;
            _db.REAL_ESTATEs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table REAL_ESTATE
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.REAL_ESTATE GetARecord(int ID)
        {
            var entity = from record in _db.REAL_ESTATEs
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
            if (_db.REAL_ESTATEs.Count() > 0)
            {
                foreach (RealEstateDataContext.REAL_ESTATE entity in _db.REAL_ESTATEs)
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
