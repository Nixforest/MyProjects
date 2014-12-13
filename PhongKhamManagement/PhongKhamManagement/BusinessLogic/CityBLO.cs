using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PhongKhamManagement.Utilities;

namespace PhongKhamManagement.BusinessLogic
{
    /// <summary>
    /// Business logic class for City object
    /// </summary>
    public class CityBLO
    {
        #region Default Methods
        /// <summary>
        /// Get all rows in City table
        /// </summary>
        /// <returns>List of City object</returns>
        public List<DataAccess.CITY> GetAllRows()
        {
            return GlobalVariable.DATA_CONTEXT.CITies.ToList();
        }

        /// <summary>
        /// Insert an entity City to database
        /// </summary>
        /// <param name="entity">Entity to insert</param>
        /// <returns>Id of insert row</returns>
        public short Insert(DataAccess.CITY entity)
        {
            GlobalVariable.DATA_CONTEXT.CITies.InsertOnSubmit(entity);
            GlobalVariable.DATA_CONTEXT.SubmitChanges();
            return entity.Id;
        }

        /// <summary>
        /// Insert an entity City to database
        /// </summary>
        /// <param name="name">Name of City</param>
        /// <returns>Id of insert row</returns>
        public short Insert(string name)
        {
            DataAccess.CITY entity = new DataAccess.CITY();
            entity.Name = name;
            GlobalVariable.DATA_CONTEXT.CITies.InsertOnSubmit(entity);
            GlobalVariable.DATA_CONTEXT.SubmitChanges();
            return entity.Id;
        }

        /// <summary>
        /// Update an entity City to database
        /// </summary>
        /// <param name="entity">Entity to update</param>
        /// <exception cref="System.Exception">Throw when entity has an invalid Id</exception>
        public void Update(DataAccess.CITY entity)
        {
            if (IsIdValid(entity.Id))
            {
                DataAccess.CITY oldEntity =
                    GlobalVariable.DATA_CONTEXT.CITies.Single(record => record.Id == entity.Id);
                oldEntity.Name = entity.Name;
                GlobalVariable.DATA_CONTEXT.SubmitChanges();
            }
            else
            {
                throw new Exception(GlobalVariable.INVALID_ID);
            }
        }

        /// <summary>
        /// Update an entity City to database
        /// </summary>
        /// <param name="id">Id</param>
        /// <param name="name">Name</param>
        /// <exception cref="System.Exception">Throw when entity has an invalid Id</exception>
        public void Update(short id, string name)
        {
            if (IsIdValid(id))
            {
                DataAccess.CITY entity = new DataAccess.CITY();
                entity.Id = id;
                entity.Name = name;
                Update(entity);
            }
            else
            {
                throw new Exception(GlobalVariable.INVALID_ID);
            }
        }

        /// <summary>
        /// Delete an entity
        /// </summary>
        /// <param name="id">Id of entity to delete</param>
        /// <exception cref="System.Exception">Throw when entity has an invalid Id</exception>
        public void Delete(short id)
        {
            if (IsIdValid(id))
            {
                var entities = from record in GlobalVariable.DATA_CONTEXT.CITies
                             where record.Id.Equals(id)
                             select record;
                GlobalVariable.DATA_CONTEXT.CITies.DeleteAllOnSubmit(entities);
                GlobalVariable.DATA_CONTEXT.SubmitChanges();
            }
            else
            {
                throw new Exception(GlobalVariable.INVALID_ID);
            }
        }

        /// <summary>
        /// Get a row
        /// </summary>
        /// <param name="id">Id of City</param>
        /// <returns>CITY object</returns>
        public DataAccess.CITY GetARow(short id)
        {
            if (IsIdValid(id))
            {
                var entities = from record in GlobalVariable.DATA_CONTEXT.CITies
                             where record.Id.Equals(id)
                             select record;
                return entities.Single();
            }
            else
            {
                throw new Exception(GlobalVariable.INVALID_ID);
            }
        }

        /// <summary>
        /// Check if an Id is valid
        /// </summary>
        /// <param name="id">Id to check</param>
        /// <returns>True if Id is valid, false otherwise</returns>
        public static bool IsIdValid(short id)
        {
            if (GlobalVariable.DATA_CONTEXT.CITies.Count() > 0)
            {
                foreach (DataAccess.CITY item in GlobalVariable.DATA_CONTEXT.CITies)
                {
                    if (item.Id.Equals(id))
                    {
                        return true;
                    }
                }
            }
            return false;
        }
        #endregion

        #region Other Methods

        #endregion
    }
}
