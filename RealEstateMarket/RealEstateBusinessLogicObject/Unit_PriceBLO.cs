using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class Unit_PriceBLO: BusinessParent<RealEstateDataContext.UNIT_PRICE>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public Unit_PriceBLO()
        {
            _db = new RealEstateDataAccessObject.Unit_PriceDAO();
        }

        /// <summary>
        /// Get all row in table UNIT_PRICE
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.UNIT_PRICE> GetAllRows()
        {
            return new ObservableCollection<RealEstateDataContext.UNIT_PRICE>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into UNIT_PRICE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just inserted</returns>
        public override int Insert(RealEstateDataContext.UNIT_PRICE entity)
        {
            entity.ID = _db.CreateID();
            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Insert a row into UNIT_PRICE table
        /// </summary>
        /// <param name="name">Name of Unit price</param>
        /// <param name="description">Description</param>
        /// <returns>ID of row has just inserted</returns>
        public int Insert(string name, string description)
        {
            RealEstateDataContext.UNIT_PRICE entity = new RealEstateDataContext.UNIT_PRICE();
            entity.ID = _db.CreateID();
            entity.Name = name;
            entity.Description = description;

            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Update a row in UNIT_PRICE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="Unit_PriceIDException"></exception>
        public override int Update(RealEstateDataContext.UNIT_PRICE entity)
        {
            if (ValidationID(entity.ID))
            {
                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.Unit_PriceIDException();
        }

        /// <summary>
        /// Update a row in UNIT_PRICE table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="name">Name of Unit</param>
        /// <param name="description">Description</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="Unit_PriceIDException"></exception>
        public int Update(int id, string name, string description)
        {
            if (ValidationID(id))
            {
                RealEstateDataContext.UNIT_PRICE entity = new RealEstateDataContext.UNIT_PRICE();
                entity.ID = _db.CreateID();
                entity.Name = name;
                entity.Description = description;

                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.Unit_PriceIDException();
        }

        /// <summary>
        /// Delete a row from UNIT_PRICE table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row has just deleted</returns>
        /// <exception cref="Unit_PriceIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.Unit_PriceIDException();
        }

        /// <summary>
        /// Get a row in UNIT_PRICE table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="Unit_PriceIDException"></exception>
        public override RealEstateDataContext.UNIT_PRICE GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.Unit_PriceIDException();
        }
    }
}
