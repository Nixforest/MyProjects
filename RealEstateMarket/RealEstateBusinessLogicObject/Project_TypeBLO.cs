using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class Project_TypeBLO : BusinessParent<RealEstateDataContext.PROJECT_TYPE>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public Project_TypeBLO()
        {
            _db = new RealEstateDataAccessObject.Project_TypeDAO();
        }

        /// <summary>
        /// Get all row in table PROJECT_TYPE
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.PROJECT_TYPE> GetAllRows()
        {
            return new ObservableCollection<RealEstateDataContext.PROJECT_TYPE>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into PROJECT_TYPE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just inserted</returns>
        public override int Insert(RealEstateDataContext.PROJECT_TYPE entity)
        {
            entity.ID = _db.CreateID();
            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Insert a row into PROJECT_TYPE table
        /// </summary>
        /// <param name="name">Project type's name</param>
        /// <param name="description">Project type's description</param>
        /// <returns>ID of row has just inserted</returns>
        public int Insert(string name, string description)
        {
            RealEstateDataContext.PROJECT_TYPE entity = new RealEstateDataContext.PROJECT_TYPE();
            entity.ID = _db.CreateID();
            entity.Name = name;
            entity.Description = description;

            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Update a row in PROJECT_TYPE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="Project_TypeIDException"></exception>
        public override int Update(RealEstateDataContext.PROJECT_TYPE entity)
        {
            if (ValidationID(entity.ID))
            {
                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.Project_TypeIDException();
        }

        /// <summary>
        /// Update a row in PROJECT_TYPE table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="name">Project type's name</param>
        /// <param name="description">Project type's description</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="Project_TypeIDException"></exception>
        public int Update(int id, string name, string description)
        {
            if (ValidationID(id))
            {
                RealEstateDataContext.PROJECT_TYPE entity = new RealEstateDataContext.PROJECT_TYPE();
                entity.ID = id;
                entity.Name = name;
                entity.Description = description;

                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.Project_TypeIDException();
        }

        /// <summary>
        /// Delete a row from PROJECT_TYPE table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row has just deleted</returns>
        /// <exception cref="Project_TypeIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.Project_TypeIDException();
        }

        /// <summary>
        /// Get a row in PROJECT_TYPE table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="Project_TypeIDException"></exception>
        public override RealEstateDataContext.PROJECT_TYPE GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.Project_TypeIDException();
        }
    }
}
