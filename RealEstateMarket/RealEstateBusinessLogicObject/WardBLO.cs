using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class WardBLO : BusinessParent<RealEstateDataContext.WARD>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public WardBLO()
        {
            _db = new RealEstateDataAccessObject.WardDAO();
        }

        /// <summary>
        /// Get all row in table WARD
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.WARD> GetAllRows()
        {
            return new ObservableCollection<RealEstateDataContext.WARD>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into WARD table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just inserted</returns>
        /// <exception cref="DistrictIDException"></exception>
        public override int Insert(RealEstateDataContext.WARD entity)
        {
            if (new RealEstateDataAccessObject.DistrictDAO().ValidationID(entity.DistrictID))
            {
                entity.ID = _db.CreateID();
                _db.Insert(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.DistrictIDException();
        }

        /// <summary>
        /// Insert a row into WARD table
        /// </summary>
        /// <param name="name">Name of ward</param>
        /// <param name="districtID">ID of district</param>
        /// <returns>ID of row has just inserted</returns>
        /// <exception cref="DistrictIDException"></exception>
        public int Insert(string name, int districtID)
        {
            if (new RealEstateDataAccessObject.DistrictDAO().ValidationID(districtID))
            {
                RealEstateDataContext.WARD entity = new RealEstateDataContext.WARD();
                entity.ID = _db.CreateID();
                entity.Name = name;
                entity.DistrictID = districtID;

                _db.Insert(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.DistrictIDException();
        }

        /// <summary>
        /// Update a row in WARD table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="WardIDException"></exception>
        /// <exception cref="DistrictIDException"></exception>
        public override int Update(RealEstateDataContext.WARD entity)
        {
            if (ValidationID(entity.ID))
            {
                if (new RealEstateDataAccessObject.DistrictDAO().ValidationID(entity.DistrictID))
                {
                    _db.Update(entity);
                    return entity.ID;
                }
                else throw new RealEstateDataContext.Utility.DistrictIDException();
            }
            else throw new RealEstateDataContext.Utility.WardIDException();
        }

        /// <summary>
        /// Update a row in WARD table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="name">Name of ward</param>
        /// <param name="districtID">ID of district</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="WardIDException"></exception>
        /// <exception cref="DistrictIDException"></exception>
        public int Update(int id, string name, int districtID)
        {
            if (ValidationID(id))
            {
                if (new RealEstateDataAccessObject.DistrictDAO().ValidationID(districtID))
                {
                    RealEstateDataContext.WARD entity = new RealEstateDataContext.WARD();
                    entity.ID = id;
                    entity.Name = name;
                    entity.DistrictID = districtID;

                    _db.Update(entity);
                    return entity.ID;
                }
                else throw new RealEstateDataContext.Utility.DistrictIDException();
            }
            else throw new RealEstateDataContext.Utility.WardIDException();
        }

        /// <summary>
        /// Delete a row from WARD table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row has just deleted</returns>
        /// <exception cref="WardIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.WardIDException();
        }

        /// <summary>
        /// Get a row in WARD table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="WardIDException"></exception>
        public override RealEstateDataContext.WARD GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.WardIDException();
        }
    }
}
