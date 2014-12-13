using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class Real_Estate_TypeBLO : BusinessParent<RealEstateDataContext.REAL_ESTATE_TYPE>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public Real_Estate_TypeBLO()
        {
            _db = new RealEstateDataAccessObject.Real_Estate_TypeDAO();
        }

        /// <summary>
        /// Get all row in table REAL_ESTATE_TYPE
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.REAL_ESTATE_TYPE> GetAllRows()
        {
            return new ObservableCollection<RealEstateDataContext.REAL_ESTATE_TYPE>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into REAL_ESTATE_TYPE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just inserted</returns>
        public override int Insert(RealEstateDataContext.REAL_ESTATE_TYPE entity)
        {
            entity.ID = _db.CreateID();
            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Insert a row into REAL_ESTATE_TYPE table
        /// </summary>
        /// <param name="name">Name</param>
        /// <param name="description">Description</param>
        /// <returns>ID of row has just inserted</returns>
        public int Insert(string name, string description)
        {
            RealEstateDataContext.REAL_ESTATE_TYPE entity = new RealEstateDataContext.REAL_ESTATE_TYPE();
            entity.ID = _db.CreateID();
            entity.Name = name;
            entity.Description = description;

            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Update a row in REAL_ESTATE_TYPE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="Real_Estate_TypeIDException"></exception>
        public override int Update(RealEstateDataContext.REAL_ESTATE_TYPE entity)
        {
            if (ValidationID(entity.ID))
            {
                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.Real_Estate_TypeIDException();
        }

        /// <summary>
        /// Update a row in REAL_ESTATE_TYPE table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="name">Name</param>
        /// <param name="description">Description</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="Real_Estate_TypeIDException"></exception>
        public int Update(int id, string name, string description)
        {
            if (ValidationID(id))
            {
                RealEstateDataContext.REAL_ESTATE_TYPE entity = new RealEstateDataContext.REAL_ESTATE_TYPE();
                entity.ID = id;
                entity.Name = name;
                entity.Description = description;

                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.Real_Estate_TypeIDException();
        }

        /// <summary>
        /// Delete a row from REAL_ESTATE_TYPE table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row has just deleted</returns>
        /// <exception cref="Real_Estate_TypeIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.Real_Estate_TypeIDException();
        }

        /// <summary>
        /// Get a row in REAL_ESTATE_TYPE table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="Real_Estate_TypeIDException"></exception>
        public override RealEstateDataContext.REAL_ESTATE_TYPE GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.Real_Estate_TypeIDException();
        }
    }
}
