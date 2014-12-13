using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PhongKhamManagement.Utilities;
using PhongKhamManagement.DataAccess;

namespace PhongKhamManagement.BusinessLogic
{
    /// <summary>
    /// Business logic class for District object
    /// </summary>
    public class DistrictBLO
    {
        #region Default Methods
        /// <summary>
        /// Get all rows in District table
        /// </summary>
        /// <returns>List of District object</returns>
        public List<DISTRICT> GetAllRows()
        {
            return GlobalVariable.DATA_CONTEXT.DISTRICTs.ToList();
        }

        /// <summary>
        /// Insert an entity District to database
        /// </summary>
        /// <param name="entity">Entity to insert</param>
        /// <returns>Id of insert row</returns>
        public short Insert(DISTRICT entity)
        {
            if (CityBLO.IsIdValid(entity.CityId))
            {
                GlobalVariable.DATA_CONTEXT.DISTRICTs.InsertOnSubmit(entity);
                GlobalVariable.DATA_CONTEXT.SubmitChanges();
                return entity.Id;
            }
            else
            {
                throw new Exception(GlobalVariable.INVALID_ID);
            }
        }

        /// <summary>
        /// Insert an entity District to database
        /// </summary>
        /// <param name="name">Name of District</param>
        /// <param name="cityId">Id of City</param>
        /// <returns>Id of insert row</returns>
        public short Insert(string name, short cityId)
        {
            if (CityBLO.IsIdValid(cityId))
            {
                DISTRICT entity = new DISTRICT();
                entity.Name = name;
                entity.CityId = cityId;
                GlobalVariable.DATA_CONTEXT.DISTRICTs.InsertOnSubmit(entity);
                GlobalVariable.DATA_CONTEXT.SubmitChanges();
                return entity.Id;
            }
            else
            {
                throw new Exception(GlobalVariable.INVALID_ID);
            }
        }

        /// <summary>
        /// Update an entity District to database
        /// </summary>
        /// <param name="entity">Entity to update</param>
        /// <exception cref="System.Exception">Throw when entity has an invalid Id</exception>
        public void Update(DISTRICT entity)
        {
            if (IsIdValid(entity.Id))
            {
                if (CityBLO.IsIdValid(entity.CityId))
                {
                    DISTRICT oldEntity =
                        GlobalVariable.DATA_CONTEXT.DISTRICTs.Single(record => record.Id == entity.Id);
                    oldEntity.Name = entity.Name;
                    oldEntity.CityId = entity.CityId;
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
        /// Update an entity District to database
        /// </summary>
        /// <param name="id">Id</param>
        /// <param name="name">Name</param>
        /// <param name="cityId">Id of City</param>
        /// <exception cref="System.Exception">Throw when entity has an invalid Id</exception>
        public void Update(short id, string name, short cityId)
        {
            if (IsIdValid(id))
            {
                if (CityBLO.IsIdValid(cityId))
                {
                    DISTRICT entity = new DISTRICT();
                    entity.Id = id;
                    entity.Name = name;
                    entity.CityId = cityId;
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
                var entities = from record in GlobalVariable.DATA_CONTEXT.DISTRICTs
                               where record.Id.Equals(id)
                               select record;
                GlobalVariable.DATA_CONTEXT.DISTRICTs.DeleteAllOnSubmit(entities);
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
        /// <param name="id">Id of District</param>
        /// <returns>DISTRICT object</returns>
        public DISTRICT GetARow(short id)
        {
            if (IsIdValid(id))
            {
                var entities = from record in GlobalVariable.DATA_CONTEXT.DISTRICTs
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
            if (GlobalVariable.DATA_CONTEXT.DISTRICTs.Count() > 0)
            {
                foreach (DISTRICT item in GlobalVariable.DATA_CONTEXT.DISTRICTs)
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
        /// <summary>
        /// Get all Branches in a District
        /// </summary>
        /// <param name="districtId">Id of District</param>
        /// <returns>List of Branches</returns>
        //public List<BRANCH> GetAllBranchesInDistrict(short districtId)
        //{
        //    if (IsIdValid(districtId))
        //    {
        //        var entities = from record in GlobalVariable.DATA_CONTEXT.DISTRICTs
        //                       where record.Id.Equals(districtId)
        //                       select record;
        //        return entities.Single().BRANCHes.ToList();
        //    }
        //    else
        //    {
        //        throw new Exception(GlobalVariable.INVALID_ID);
        //    }
        //}
        //public List<>
        #endregion
    }
}
