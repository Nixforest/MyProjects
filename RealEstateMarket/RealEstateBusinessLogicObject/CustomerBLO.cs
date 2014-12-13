using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class CustomerBLO : BusinessParent<RealEstateDataContext.CUSTOMER>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public CustomerBLO()
        {
            _db = new RealEstateDataAccessObject.CustomerDAO();
        }

        /// <summary>
        /// Get all row in table CUSTOMER
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.CUSTOMER> GetAllRows()
        {
            return new ObservableCollection<RealEstateDataContext.CUSTOMER>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into CUSTOMER table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row have just inserted</returns>
        /// <exception cref="AddressIDException: ID not exist in ADDRESS table"></exception>
        /// <exception cref="UserIDException: ID not exist in USER table"></exception>
        public override int Insert(RealEstateDataContext.CUSTOMER entity)
        {
            if (new RealEstateDataAccessObject.AddressDAO().ValidationID(entity.AddressID))
            {
                if (new RealEstateDataAccessObject.UserDAO().ValidationID((int)entity.UserID) || entity.UserID == null)
                {
                    entity.ID = _db.CreateID();
                    _db.Insert(entity);
                    return entity.ID;
                }
                else throw new RealEstateDataContext.Utility.UserIDException();
            }
            else throw new RealEstateDataContext.Utility.AddressIDException();
        }

        /// <summary>
        /// Insert a row into CUSTOMER table
        /// </summary>
        /// <param name="name">Customer's full name</param>
        /// <param name="addressID">ID of address</param>
        /// <param name="identityCard">Customer's identity card</param>
        /// <param name="phone">Customer's phone</param>
        /// <param name="homePhone">Customer's home phone</param>
        /// <param name="email">Customer's email</param>
        /// <param name="userID">Customer's user id</param>
        /// <returns>ID of row have just inserted</returns>
        /// <exception cref="AddressIDException: ID not exist in ADDRESS table"></exception>
        /// <exception cref="UserIDException: ID not exist in USER table"></exception>
        public int Insert(string name, int addressID, string identityCard,
            string phone, string homePhone, string email, int? userID)
        {
            if (new RealEstateDataAccessObject.AddressDAO().ValidationID(addressID))
            {
                if (new RealEstateDataAccessObject.UserDAO().ValidationID((int)userID) || userID == null)
                {
                    RealEstateDataContext.CUSTOMER entity = new RealEstateDataContext.CUSTOMER();
                    entity.ID = _db.CreateID();
                    entity.Name = name;
                    entity.AddressID = addressID;
                    entity.IdentityCard = identityCard;
                    entity.Phone = phone;
                    entity.HomePhone = homePhone;
                    entity.Email = email;
                    entity.UserID = userID;

                    _db.Insert(entity);
                    return entity.ID;
                }
                else throw new RealEstateDataContext.Utility.UserIDException();
            }
            else throw new RealEstateDataContext.Utility.AddressIDException();
        }

        /// <summary>
        /// Update a row in CUSTOMER table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row have just updated</returns>
        /// <exception cref="CustomerIDException: ID not exist in CUSTOMER table"></exception>
        /// <exception cref="AddressIDException: ID not exist in ADDRESS table"></exception>
        /// <exception cref="UserIDException: ID not exist in USER table"></exception>
        public override int Update(RealEstateDataContext.CUSTOMER entity)
        {
            if (ValidationID(entity.ID))
            {
                if (new RealEstateDataAccessObject.AddressDAO().ValidationID(entity.AddressID))
                {
                    if (new RealEstateDataAccessObject.UserDAO().ValidationID((int)entity.UserID) || entity.UserID == null)
                    {
                        _db.Update(entity);
                        return entity.ID;
                    }
                    else throw new RealEstateDataContext.Utility.UserIDException();
                }
                else throw new RealEstateDataContext.Utility.AddressIDException();
            }
            else throw new RealEstateDataContext.Utility.CustomerIDException();
        }

        /// <summary>
        /// Update a row in CUSTOMER table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="name">Customer's full name</param>
        /// <param name="addressID">ID of address</param>
        /// <param name="identityCard">Customer's identity card</param>
        /// <param name="phone">Customer's phone</param>
        /// <param name="homePhone">Customer's home phone</param>
        /// <param name="email">Customer's email</param>
        /// <param name="userID">Customer's user id</param>
        /// <returns>ID of row have just updated</returns>
        /// <exception cref="CustomerIDException: ID not exist in CUSTOMER table"></exception>
        /// <exception cref="AddressIDException: ID not exist in ADDRESS table"></exception>
        /// <exception cref="UserIDException: ID not exist in USER table"></exception>
        public int Update(int id, string name, int addressID, string identityCard,
            string phone, string homePhone, string email, int? userID)
        {
            if (ValidationID(id))
            {
                if (new RealEstateDataAccessObject.AddressDAO().ValidationID(addressID))
                {
                    if (new RealEstateDataAccessObject.UserDAO().ValidationID((int)userID) || userID == null)
                    {
                        RealEstateDataContext.CUSTOMER entity = new RealEstateDataContext.CUSTOMER();
                        entity.ID = id;
                        entity.Name = name;
                        entity.AddressID = addressID;
                        entity.IdentityCard = identityCard;
                        entity.Phone = phone;
                        entity.HomePhone = homePhone;
                        entity.Email = email;
                        entity.UserID = userID;

                        _db.Update(entity);
                        return entity.ID;
                    }
                    else throw new RealEstateDataContext.Utility.UserIDException();
                }
                else throw new RealEstateDataContext.Utility.AddressIDException();
            }
            else throw new RealEstateDataContext.Utility.CustomerIDException();
        }

        /// <summary>
        /// Delete a row from CUSTOMER table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row just delete</returns>
        /// <exception cref="CustomerIDException: ID not exist in CUSTOMER table"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.CustomerIDException();
        }

        /// <summary>
        /// Get a row in CUSTOMER table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="CustomerIDException: ID not exist in CUSTOMER table"></exception>
        public override RealEstateDataContext.CUSTOMER GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.CustomerIDException();
        }
    }
}
