using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class UtilityBLO : BusinessParent<RealEstateDataContext.UTILITY>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public UtilityBLO()
        {
            _db = new RealEstateDataAccessObject.UtilityDAO();
        }

        /// <summary>
        /// Get all row in table UTILITY
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.UTILITY> GetAllRows()
        {
            return new ObservableCollection<RealEstateDataContext.UTILITY>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into UTILITY table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just inserted</returns>
        public override int Insert(RealEstateDataContext.UTILITY entity)
        {
            entity.ID = _db.CreateID();
            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Insert a row into UTILITY table
        /// </summary>
        /// <param name="name">Name of Utility</param>
        /// <param name="description">Description</param>
        /// <returns>ID of row has just inserted</returns>
        public int Insert(string name, string description)
        {
            RealEstateDataContext.UTILITY entity = new RealEstateDataContext.UTILITY();
            entity.ID = _db.CreateID();
            entity.Name = name;
            entity.Description = description;

            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Update a row in UTILITY table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="UtilityIDException"></exception>
        public override int Update(RealEstateDataContext.UTILITY entity)
        {
            if (ValidationID(entity.ID))
            {
                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.UtilityIDException();
        }

        /// <summary>
        /// Update a row in UTILITY table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="name">Name of Utility</param>
        /// <param name="description">Description</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="UtilityIDException"></exception>
        public int Update(int id, string name, string description)
        {
            if (ValidationID(id))
            {
                RealEstateDataContext.UTILITY entity = new RealEstateDataContext.UTILITY();
                entity.ID = _db.CreateID();
                entity.Name = name;
                entity.Description = description;

                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.UtilityIDException();
        }

        /// <summary>
        /// Delete a row from UTILITY table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row has just deleted</returns>
        /// <exception cref="UtilityIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.UtilityIDException();
        }

        /// <summary>
        /// Get a row in UTILITY table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="UtilityIDException"></exception>
        public override RealEstateDataContext.UTILITY GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.UtilityIDException();
        }
    }
}
