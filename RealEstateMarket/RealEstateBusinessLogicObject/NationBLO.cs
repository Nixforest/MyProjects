using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using RealEstateDataAccessObject;
using RealEstateDataContext;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class NationBLO : BusinessParent<RealEstateDataContext.NATION>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public NationBLO()
        {
            _db = new NationDAO();
        }

        /// <summary>
        /// Get all row in table NATION
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<NATION> GetAllRows()
        {
            return new ObservableCollection<NATION>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into NATION table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row just insert</returns>
        public override int Insert(NATION entity)
        {
            entity.ID = _db.CreateID();
            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Insert a row into NATION table
        /// </summary>
        /// <param name="name">Name of Nation</param>
        /// <param name="nationCode">National code</param>
        /// <returns>ID of row just insert</returns>
        public int Insert(string name, string nationCode)
        {
            NATION entity = new NATION();
            entity.ID = _db.CreateID();
            entity.Name = name;
            entity.NationCode = nationCode;
            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Update a row in NATION table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row just update</returns>
        /// <exception cref="NationIDException"></exception>
        public override int Update(NATION entity)
        {
            if (ValidationID(entity.ID))
            {
                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.NationIDException();
        }

        /// <summary>
        /// Update a row in NATION table
        /// </summary>
        /// <param name="id">ID of Nation</param>
        /// <param name="name">Name of Nation</param>
        /// <param name="nationCode">National code</param>
        /// <returns>ID of row just update</returns>
        /// <exception cref="NationIDException"></exception>
        public int Update(int id, string name, string nationCode)
        {
            if (ValidationID(id))
            {
                NATION entity = new NATION();
                entity.ID = _db.CreateID();
                entity.Name = name;
                entity.NationCode = nationCode;

                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.NationIDException();
        }

        /// <summary>
        /// Delete a row from NATION table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row just delete</returns>
        /// <exception cref="NationIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.NationIDException();
        }

        /// <summary>
        /// Get a row in NATION table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="NationIDException"></exception>
        public override NATION GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.NationIDException();
        }
    }
}
