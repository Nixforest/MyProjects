using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class CompanyBLO : BusinessParent<RealEstateDataContext.COMPANY>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public CompanyBLO()
        {
            _db = new RealEstateDataAccessObject.CompanyDAO();
        }

        /// <summary>
        /// Get all row in table COMPANY
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.COMPANY> GetAllRows()
        {
            return new ObservableCollection<RealEstateDataContext.COMPANY>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into COMPANY table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row just insert</returns>
        /// <exception cref="AddressIDException: ID not exist in ADDRESS table"></exception>
        /// <exception cref="ShareCapitalException: Share capital must greater than zero"></exception>
        public override int Insert(RealEstateDataContext.COMPANY entity)
        {
            if (new RealEstateDataAccessObject.AddressDAO().ValidationID(entity.AddressID))
            {
                if (entity.ShareCapital == null || entity.ShareCapital > 0)
                {
                    entity.ID = _db.CreateID();
                    _db.Insert(entity);
                    return entity.ID;
                }
                else throw new RealEstateDataContext.Utility.ShareCapitalException();
            }
            else throw new RealEstateDataContext.Utility.AddressIDException();
        }
        /// <summary>
        /// Insert a row into COMPANY table
        /// </summary>
        /// <param name="name">Name of company</param>
        /// <param name="addressID">ID of address</param>
        /// <param name="phone">Company's phone</param>
        /// <param name="homePhone">Company's Home Phone</param>
        /// <param name="fax">Company's fax</param>
        /// <param name="email">Company's email</param>
        /// <param name="website">Company's website</param>
        /// <param name="establishDay">Company's establish day</param>
        /// <param name="shareCapital">Company's share capital</param>
        /// <param name="fieldOfAction">Company's field of action</param>
        /// <param name="businessRegistration">Company's business registration</param>
        /// <param name="description">Description</param>
        /// <returns>ID of row just insert</returns>
        /// <exception cref="AddressIDException: ID not exist in ADDRESS table"></exception>
        /// <exception cref="ShareCapitalException: Share capital must greater than zero"></exception>
        public int Insert(string name, int addressID, string phone, string homePhone,
            string fax, string email, string website, DateTime? establishDay,
            decimal? shareCapital, string fieldOfAction, bool businessRegistration, string description)
        {
            if (new RealEstateDataAccessObject.AddressDAO().ValidationID(addressID))
            {
                if (shareCapital == null || shareCapital > 0)
                {
                    RealEstateDataContext.COMPANY entity = new RealEstateDataContext.COMPANY();

                    entity.ID = _db.CreateID();
                    entity.Name = name;
                    entity.AddressID = addressID;
                    entity.Phone = phone;
                    entity.HomePhone = homePhone;
                    entity.Fax = fax;
                    entity.Email = email;
                    entity.Website = website;
                    entity.EstablishDay = establishDay;
                    entity.ShareCapital = shareCapital;
                    entity.FieldOfAction = fieldOfAction;
                    entity.BusinessRegistration = businessRegistration;
                    entity.Description = description;

                    _db.Insert(entity);
                    return entity.ID;
                }
                else throw new RealEstateDataContext.Utility.ShareCapitalException();
            }
            else throw new RealEstateDataContext.Utility.AddressIDException();
        }

        /// <summary>
        /// Update a row in NATION table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row just update</returns>
        /// <exception cref="CompanyIDException: ID not exist in COMPANY table"></exception>
        /// <exception cref="AddressIDException: ID not exist in ADDRESS table"></exception>
        /// <exception cref="ShareCapitalException: Share capital must greater than zero"></exception>
        public override int Update(RealEstateDataContext.COMPANY entity)
        {
            if (ValidationID(entity.ID))
            {
                if (new RealEstateDataAccessObject.AddressDAO().ValidationID(entity.AddressID))
                {
                    if (entity.ShareCapital == null || entity.ShareCapital > 0)
                    {
                        _db.Update(entity);
                        return entity.ID;
                    }
                    else throw new RealEstateDataContext.Utility.ShareCapitalException();
                }
                else throw new RealEstateDataContext.Utility.AddressIDException();
            }
            else throw new RealEstateDataContext.Utility.CompanyIDException();
        }

        /// <summary>
        /// Update a row in COMPANY table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="name">Name of company</param>
        /// <param name="addressID">ID of address</param>
        /// <param name="phone">Company's phone</param>
        /// <param name="homePhone">Company's Home Phone</param>
        /// <param name="fax">Company's fax</param>
        /// <param name="email">Company's email</param>
        /// <param name="website">Company's website</param>
        /// <param name="establishDay">Company's establish day</param>
        /// <param name="shareCapital">Company's share capital</param>
        /// <param name="fieldOfAction">Company's field of action</param>
        /// <param name="businessRegistration">Company's business registration</param>
        /// <param name="description">Description</param>
        /// <returns>ID of row just update</returns>
        /// <exception cref="CompanyIDException: ID not exist in COMPANY table"></exception>
        /// <exception cref="AddressIDException: ID not exist in ADDRESS table"></exception>
        /// <exception cref="ShareCapitalException: Share capital must greater than zero"></exception>
        public int Update(int id, string name, int addressID, string phone, string homePhone,
            string fax, string email, string website, DateTime? establishDay,
            decimal? shareCapital, string fieldOfAction, bool businessRegistration, string description)
        {
            if (ValidationID(id))
            {
                if (new RealEstateDataAccessObject.AddressDAO().ValidationID(addressID))
                {
                    if (shareCapital == null || shareCapital > 0)
                    {
                        RealEstateDataContext.COMPANY entity = new RealEstateDataContext.COMPANY();
                        entity.ID = id;
                        entity.Name = name;
                        entity.AddressID = addressID;
                        entity.Phone = phone;
                        entity.HomePhone = homePhone;
                        entity.Fax = fax;
                        entity.Email = email;
                        entity.Website = website;
                        entity.EstablishDay = establishDay;
                        entity.ShareCapital = shareCapital;
                        entity.FieldOfAction = fieldOfAction;
                        entity.BusinessRegistration = businessRegistration;
                        entity.Description = description;

                        _db.Update(entity);
                        return entity.ID;
                    }
                    else throw new RealEstateDataContext.Utility.ShareCapitalException();
                }
                else throw new RealEstateDataContext.Utility.AddressIDException();
            }
            else throw new RealEstateDataContext.Utility.CompanyIDException();
        }

        /// <summary>
        /// Delete a row from COMPANY table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row just delete</returns>
        /// <exception cref="CompanyIDException: ID not exist in COMPANY table"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.CompanyIDException();
        }

        /// <summary>
        /// Get a row in COMPANY table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="CompanyIDException: ID not exist in COMPANY table"></exception>
        public override RealEstateDataContext.COMPANY GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.CompanyIDException();
        }
    }
}
