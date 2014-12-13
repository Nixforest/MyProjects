using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class GroupBLO : BusinessParent<RealEstateDataContext.GROUP>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public GroupBLO()
        {
            _db = new RealEstateDataAccessObject.GroupDAO();
        }

        /// <summary>
        /// Get all row in table GROUP
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.GROUP> GetAllRows()
        {
            return new ObservableCollection<RealEstateDataContext.GROUP>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into GROUP table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row have just inserted</returns>
        public override int Insert(RealEstateDataContext.GROUP entity)
        {
            entity.ID = _db.CreateID();
            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Insert a row into GROUP table
        /// </summary>
        /// <param name="name">Group's name</param>
        /// <param name="description">Description</param>
        /// <returns>ID of row have just inserted</returns>
        public int Insert(string name, string description)
        {
            RealEstateDataContext.GROUP entity = new RealEstateDataContext.GROUP();
            entity.ID = _db.CreateID();
            entity.Name = name;
            entity.Description = description;

            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Update a row in GROUP table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row have just updated</returns>
        /// <exception cref="GroupIDException"></exception>
        public override int Update(RealEstateDataContext.GROUP entity)
        {
            if (ValidationID(entity.ID))
            {
                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.GroupIDException();
        }

        /// <summary>
        /// Update a row in GROUP table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="name">Group's name</param>
        /// <param name="description">Description</param>
        /// <returns>ID of row have just updated</returns>
        /// <exception cref="GroupIDException"></exception>
        public int Update(int id, string name, string description)
        {
            if (ValidationID(id))
            {
                RealEstateDataContext.GROUP entity = new RealEstateDataContext.GROUP();
                entity.ID = id;
                entity.Name = name;
                entity.Description = description;

                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.GroupIDException();
        }

        /// <summary>
        /// Delete a row from GROUP table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row just delete</returns>
        /// <exception cref="GroupIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.GroupIDException();
        }

        /// <summary>
        /// Get a row in GROUP table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="GroupIDException"></exception>
        public override RealEstateDataContext.GROUP GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.GroupIDException();
        }
    }
}
