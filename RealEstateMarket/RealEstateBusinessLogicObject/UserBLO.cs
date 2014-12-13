using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class UserBLO: BusinessParent<RealEstateDataContext.USER>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public UserBLO()
        {
            _db = new RealEstateDataAccessObject.UserDAO();
        }

        /// <summary>
        /// Get all row in table USER
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.USER> GetAllRows()
        {
            return new ObservableCollection<RealEstateDataContext.USER>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into USER table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just inserted</returns>
        /// <exception cref="GroupIDException"></exception>
        public override int Insert(RealEstateDataContext.USER entity)
        {
            if (new RealEstateDataAccessObject.GroupDAO().ValidationID((int)entity.GroupID) || entity.GroupID == null)
            {
                entity.ID = _db.CreateID();
                _db.Insert(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.GroupIDException();
        }

        /// <summary>
        /// Insert a row into USER table
        /// </summary>
        /// <param name="username">User name</param>
        /// <param name="password">Password</param>
        /// <param name="email">Email</param>
        /// <param name="phone">Phone</param>
        /// <param name="groupID">ID of group user belong</param>
        /// <returns>ID of row has just inserted</returns>
        /// <exception cref="GroupIDException"></exception>
        public int Insert(string username, string password,
            string email, string phone, int? groupID)
        {
            if (new RealEstateDataAccessObject.GroupDAO().ValidationID((int)groupID) || groupID == null)
            {
                RealEstateDataContext.USER entity = new RealEstateDataContext.USER();
                entity.ID = _db.CreateID();
                entity.Username = username;
                entity.Password = password;
                entity.Email = email;
                entity.Phone = phone;
                entity.GroupID = groupID;

                _db.Insert(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.GroupIDException();
        }

        /// <summary>
        /// Update a row in USER table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="UserIDException"></exception>
        /// <exception cref="GroupIDException"></exception>
        public override int Update(RealEstateDataContext.USER entity)
        {
            if (ValidationID(entity.ID))
            {
                if (new RealEstateDataAccessObject.GroupDAO().ValidationID((int)entity.GroupID) || entity.GroupID == null)
                {
                    _db.Update(entity);
                    return entity.ID;
                }
                else throw new RealEstateDataContext.Utility.GroupIDException();
            }
            else throw new RealEstateDataContext.Utility.UserIDException();
        }

        /// <summary>
        /// Update a row in USER table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="username">User name</param>
        /// <param name="password">Password</param>
        /// <param name="email">Email</param>
        /// <param name="phone">Phone</param>
        /// <param name="groupID">ID of group user belong</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="UserIDException"></exception>
        /// <exception cref="GroupIDException"></exception>
        public int Update(int id, string username, string password,
            string email, string phone, int groupID)
        {
            if (ValidationID(id))
            {
                if (new RealEstateDataAccessObject.GroupDAO().ValidationID((int)groupID) || groupID == null)
                {
                    RealEstateDataContext.USER entity = new RealEstateDataContext.USER();
                    entity.ID = id;
                    entity.Username = username;
                    entity.Password = password;
                    entity.Email = email;
                    entity.Phone = phone;
                    entity.GroupID = groupID;

                    _db.Update(entity);
                    return entity.ID;
                }
                else throw new RealEstateDataContext.Utility.GroupIDException();
            }
            else throw new RealEstateDataContext.Utility.UserIDException();
        }

        /// <summary>
        /// Delete a row from USER table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row has just deleted</returns>
        /// <exception cref="UserIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.UserIDException();
        }

        /// <summary>
        /// Get a row in USER table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="UserIDException"></exception>
        public override RealEstateDataContext.USER GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.UserIDException();
        }
    }
}
