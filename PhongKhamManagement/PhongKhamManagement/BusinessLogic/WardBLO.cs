using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PhongKhamManagement.Utilities;
using PhongKhamManagement.DataAccess;

namespace PhongKhamManagement.BusinessLogic
{
    /// <summary>
    /// Business logic class for Ward object
    /// </summary>
    public class WardBLO
    {
        #region Default Methods
        /// <summary>
        /// Get all rows in Ward table
        /// </summary>
        /// <returns>List of Ward object</returns>
        public List<WARD> GetAllRows()
        {
            return GlobalVariable.DATA_CONTEXT.WARDs.ToList();
        }

        /// <summary>
        /// Insert an entity Ward to database
        /// </summary>
        /// <param name="entity">Entity to insert</param>
        /// <returns>Id of insert row</returns>
        public short Insert(WARD entity)
        {
            if (DistrictBLO.IsIdValid(entity.DistrictId))
            {
                GlobalVariable.DATA_CONTEXT.WARDs.InsertOnSubmit(entity);
                GlobalVariable.DATA_CONTEXT.SubmitChanges();
                return entity.Id;
            }
            else
            {
                throw new Exception(GlobalVariable.INVALID_ID);
            }
        }

        /// <summary>
        /// Insert an entity Ward to database
        /// </summary>
        /// <param name="name">Name of Ward</param>
        /// <param name="districtId">Id of District</param>
        /// <returns>Id of insert row</returns>
        public short Insert(string name, short districtId)
        {
            if (DistrictBLO.IsIdValid(districtId))
            {
                WARD entity = new WARD();
                entity.Name = name;
                entity.DistrictId = districtId;
                GlobalVariable.DATA_CONTEXT.WARDs.InsertOnSubmit(entity);
                GlobalVariable.DATA_CONTEXT.SubmitChanges();
                return entity.Id;
            }
            else
            {
                throw new Exception(GlobalVariable.INVALID_ID);
            }
        }

        /// <summary>
        /// Update an entity Ward to database
        /// </summary>
        /// <param name="entity">Entity to update</param>
        /// <exception cref="System.Exception">Throw when entity has an invalid Id</exception>
        public void Update(WARD entity)
        {
            if (IsIdValid(entity.Id))
            {
                if (DistrictBLO.IsIdValid(entity.DistrictId))
                {
                    WARD oldEntity =
                        GlobalVariable.DATA_CONTEXT.WARDs.Single(record => record.Id == entity.Id);
                    oldEntity.Name = entity.Name;
                    oldEntity.DistrictId = entity.DistrictId;
                    GlobalVariable.DATA_CONTEXT.SubmitChanges();
                }
                else
                {
                    throw new Exception(GlobalVariable.INVALID_ID);
                }
            }
            else
            {
                throw new Exception(GlobalVariable.INVALID_ID);
            }
        }

        /// <summary>
        /// Update an entity Ward to database
        /// </summary>
        /// <param name="id">Id</param>
        /// <param name="name">Name</param>
        /// <param name="districtId">Id of District</param>
        /// <exception cref="System.Exception">Throw when entity has an invalid Id</exception>
        public void Update(short id, string name, short districtId)
        {
            if (IsIdValid(id))
            {
                if (DistrictBLO.IsIdValid(districtId))
                {
                    WARD entity = new WARD();
                    entity.Id = id;
                    entity.Name = name;
                    entity.DistrictId = districtId;
                    Update(entity);
                }
                else
                {
                    throw new Exception(GlobalVariable.INVALID_ID);
                }
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
                var entities = from record in GlobalVariable.DATA_CONTEXT.WARDs
                               where record.Id.Equals(id)
                               select record;
                GlobalVariable.DATA_CONTEXT.WARDs.DeleteAllOnSubmit(entities);
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
        /// <param name="id">Id of Ward</param>
        /// <returns>WARD object</returns>
        public WARD GetARow(short id)
        {
            if (IsIdValid(id))
            {
                var entities = from record in GlobalVariable.DATA_CONTEXT.WARDs
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
            if (GlobalVariable.DATA_CONTEXT.WARDs.Count() > 0)
            {
                foreach (WARD item in GlobalVariable.DATA_CONTEXT.WARDs)
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
