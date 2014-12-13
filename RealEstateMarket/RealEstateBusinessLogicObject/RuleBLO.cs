using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class RuleBLO : BusinessParent<RealEstateDataContext.RULE>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public RuleBLO()
        {
            _db = new RealEstateDataAccessObject.RuleDAO();
        }

        /// <summary>
        /// Get all row in table RULE
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.RULE> GetAllRows()
        {
            return new ObservableCollection<RealEstateDataContext.RULE>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into RULE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just inserted</returns>
        public override int Insert(RealEstateDataContext.RULE entity)
        {
            entity.ID = _db.CreateID();
            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Insert a row into RULE table
        /// </summary>
        /// <param name="name">Name of rule</param>
        /// <param name="description">Description of rule</param>
        /// <returns>ID of row has just inserted</returns>
        public int Insert(string name, string description)
        {
            RealEstateDataContext.RULE entity = new RealEstateDataContext.RULE();
            entity.ID = _db.CreateID();
            entity.Name = name;
            entity.Description = description;

            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Update a row in RULE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="RuleIDException"></exception>
        public override int Update(RealEstateDataContext.RULE entity)
        {
            if (ValidationID(entity.ID))
            {
                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.RuleIDException();
        }

        /// <summary>
        /// Update a row in RULE table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="name">Name of rule</param>
        /// <param name="description">Description of rule</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="RuleIDException"></exception>
        public int Update(int id, string name, string description)
        {
            if (ValidationID(id))
            {
                RealEstateDataContext.RULE entity = new RealEstateDataContext.RULE();
                entity.ID = id;
                entity.Name = name;
                entity.Description = description;

                _db.Update(entity);
                return entity.ID;
            }
            else throw new RealEstateDataContext.Utility.RuleIDException();
        }

        /// <summary>
        /// Delete a row from RULE table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row has just deleted</returns>
        /// <exception cref="RuleIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.RuleIDException();
        }

        /// <summary>
        /// Get a row in RULE table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="RuleIDException"></exception>
        public override RealEstateDataContext.RULE GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.RuleIDException();
        }
    }
}
