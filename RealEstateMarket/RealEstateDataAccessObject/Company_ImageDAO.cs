using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to COMPANY_IMAGE table in database
    /// </summary>
    public class Company_ImageDAO: DataParent<RealEstateDataContext.COMPANY_IMAGE>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.COMPANY_IMAGEs.Count();
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
        /// Get all rows in table COMPANY_IMAGE
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.COMPANY_IMAGE> GetAllRows()
        {
            return _db.COMPANY_IMAGEs.ToList();
        }

        /// <summary>
        /// Insert a row into table COMPANY_IMAGE
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.COMPANY_IMAGE entity)
        {
            _db.COMPANY_IMAGEs.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table COMPANY_IMAGE
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.COMPANY_IMAGE entity)
        {
            RealEstateDataContext.COMPANY_IMAGE oldEntity = _db.COMPANY_IMAGEs.Single(record => record.ID == entity.ID);
            oldEntity.CompanyID = entity.CompanyID;
            oldEntity.ImageID = entity.ImageID;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table COMPANY_IMAGE
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.COMPANY_IMAGEs
                         where record.ID.Equals(ID)
                         select record;
            _db.COMPANY_IMAGEs.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table COMPANY_IMAGE
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.COMPANY_IMAGE GetARecord(int ID)
        {
            var entity = from record in _db.COMPANY_IMAGEs
                         where record.ID.Equals(ID)
                         select record;
            return entity.Single();
        }
    }
}
