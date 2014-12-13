using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class UnitBLO : BusinessParent<RealEstateDataContext.UNIT>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public UnitBLO()
        {
            _db = new RealEstateDataAccessObject.UnitDAO();
        }

        /// <summary>
        /// Get all row in table UNIT
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.UNIT> GetAllRows()
        {
            return new ObservableCollection<RealEstateDataContext.UNIT>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into UNIT table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just inserted</returns>
        public override int Insert(RealEstateDataContext.UNIT entity)
        {
            entity.ID = _db.CreateID();
            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Insert a row into UNIT table
        /// </summary>
        /// <param name="name">Name of Unit</param>
        /// <param name="description">Description</param>
        /// <returns>ID of row has just inserted</returns>
        public int Insert(string name, string description)
        {
            RealEstateDataContext.UNIT entity = new RealEstateDataContext.UNIT();
            entity.ID = _db.CreateID();
            entity.Name = name;
            entity.Description = description;

            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Update a row in UNIT table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="UnitIDException"></exception>
        public override int Update(RealEstateDataContext.UNIT entity)
        {
            if (ValidationID(entity.ID))
            {
                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.UnitIDException();
        }

        /// <summary>
        /// Update a row in UNIT table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="name">Name of Unit</param>
        /// <param name="description">Description</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="UnitIDException"></exception>
        public int Update(int id, string name, string description)
        {
            if (ValidationID(id))
            {
                RealEstateDataContext.UNIT entity = new RealEstateDataContext.UNIT();
                entity.ID = _db.CreateID();
                entity.Name = name;
                entity.Description = description;

                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.UnitIDException();
        }

        /// <summary>
        /// Delete a row from UNIT table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row has just deleted</returns>
        /// <exception cref="UnitIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.UnitIDException();
        }

        /// <summary>
        /// Get a row in UNIT table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="UnitIDException"></exception>
        public override RealEstateDataContext.UNIT GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.UnitIDException();
        }
    }
}
