using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataAccessObject
{
    /// <summary>
    /// Class access to COMPANY table in database
    /// </summary>
    public class CompanyDAO : DataParent<RealEstateDataContext.COMPANY>
    {
        /// <summary>
        /// Create a new ID for new entity in table
        /// </summary>
        /// <returns>ID just create.</returns>
        public override int CreateID()
        {
            int numberRecord;
            int value;
            numberRecord = _db.COMPANies.Count();
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
        /// Get all rows in table COMPANY
        /// </summary>
        /// <returns>List of entity</returns>
        public override ICollection<RealEstateDataContext.COMPANY> GetAllRows()
        {
            return _db.COMPANies.ToList();
        }

        /// <summary>
        /// Insert a row into table COMPANYCOMPANY
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Insert(RealEstateDataContext.COMPANY entity)
        {
            _db.COMPANies.InsertOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Update a row in table COMPANY
        /// </summary>
        /// <param name="entity">Entity</param>
        public override void Update(RealEstateDataContext.COMPANY entity)
        {
            RealEstateDataContext.COMPANY oldEntity = _db.COMPANies.Single(record => record.ID == entity.ID);
            oldEntity.Name = entity.Name;
            oldEntity.AddressID = entity.AddressID;
            oldEntity.Phone = entity.Phone;
            oldEntity.HomePhone = entity.HomePhone;
            oldEntity.Fax = entity.Fax;
            oldEntity.Email = entity.Email;
            oldEntity.Website = entity.Website;
            oldEntity.EstablishDay = entity.EstablishDay;
            oldEntity.ShareCapital = entity.ShareCapital;
            oldEntity.FieldOfAction = entity.FieldOfAction;
            oldEntity.BusinessRegistration = entity.BusinessRegistration;
            oldEntity.Description = entity.Description;

            _db.SubmitChanges();
        }

        /// <summary>
        /// Delete a row in table COMPANY
        /// </summary>
        /// <param name="ID">ID of row</param>
        public override void Delete(int ID)
        {
            var entity = from record in _db.COMPANies
                         where record.ID.Equals(ID)
                         select record;
            _db.COMPANies.DeleteAllOnSubmit(entity);
            _db.SubmitChanges();
        }

        /// <summary>
        /// Get a row from table COMPANY
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        public override RealEstateDataContext.COMPANY GetARecord(int ID)
        {
            var entity = from record in _db.COMPANies
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
            if (_db.COMPANies.Count() > 0)
            {
                foreach (RealEstateDataContext.COMPANY entity in _db.COMPANies)
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
