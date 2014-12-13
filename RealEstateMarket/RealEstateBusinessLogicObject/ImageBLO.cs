using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateBusinessLogicObject
{
    public class ImageBLO : BusinessParent<RealEstateDataContext.IMAGE>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public ImageBLO()
        {
            _db = new RealEstateDataAccessObject.ImageDAO();
        }

        /// <summary>
        /// Get all row in table IMAGE
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.IMAGE> GetAllRows()
        {
            return new System.Collections.ObjectModel.ObservableCollection<RealEstateDataContext.IMAGE>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into IMAGE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row have just inserted</returns>
        public override int Insert(RealEstateDataContext.IMAGE entity)
        {
            entity.ID = _db.CreateID();
            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Insert a row into IMAGE table
        /// </summary>
        /// <param name="name">Image's name</param>
        /// <param name="path">Image's source path</param>
        /// <param name="description">Image's description</param>
        /// <returns>ID of row have just inserted</returns>
        public int Insert(string name, string path, string description)
        {
            RealEstateDataContext.IMAGE entity = new RealEstateDataContext.IMAGE();
            entity.ID = _db.CreateID();
            entity.Name = name;
            entity.Path = path;
            entity.Description = description;

            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Update a row in IMAGE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row have just updated</returns>
        /// <exception cref="ImageIDException"></exception>
        public override int Update(RealEstateDataContext.IMAGE entity)
        {
            if (ValidationID(entity.ID))
            {
                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.ImageIDException();
        }

        /// <summary>
        /// Update a row in IMAGE table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="name">Image's name</param>
        /// <param name="path">Image's source path</param>
        /// <param name="description">Image's description</param>
        /// <returns>ID of row have just updated</returns>
        /// <exception cref="ImageIDException"></exception>
        public int Update(int id, string name, string path, string description)
        {
            if (ValidationID(id))
            {
                RealEstateDataContext.IMAGE entity = new RealEstateDataContext.IMAGE();
                entity.ID = id;
                entity.Name = name;
                entity.Path = path;
                entity.Description = description;

                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.ImageIDException();
        }

        /// <summary>
        /// Delete a row from IMAGE table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row has just deleted</returns>
        /// <exception cref="ImageIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.ImageIDException();
        }

        /// <summary>
        /// Get a row in IMAGE table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="ImageIDException"></exception>
        public override RealEstateDataContext.IMAGE GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.ImageIDException();
        }
    }
}
