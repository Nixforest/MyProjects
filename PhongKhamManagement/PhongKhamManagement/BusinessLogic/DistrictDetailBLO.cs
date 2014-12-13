using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PhongKhamManagement.Utilities;
using PhongKhamManagement.DataAccess;

namespace PhongKhamManagement.BusinessLogic
{
    /// <summary>
    /// Business logic class for District Detail object
    /// </summary>
    public class DistrictDetailBLO
    {
        #region Default Methods

        /// <summary>
        /// Insert an entity District Detail to database
        /// </summary>
        /// <param name="entity">Entity to insert</param>
        /// <returns>Id of insert row</returns>
        public short Insert(DISTRICT_DETAIL entity)
        {
            if (DistrictBLO.IsIdValid(entity.DistrictId)
                || StreetBLO.IsIdValid(entity.StreetId))
            {
                GlobalVariable.DATA_CONTEXT.DISTRICT_DETAILs.InsertOnSubmit(entity);
                GlobalVariable.DATA_CONTEXT.SubmitChanges();
                return entity.Id;
            }
            else
            {
                throw new Exception(GlobalVariable.INVALID_ID);
            }
        }

        /// <summary>
        /// Insert an entity District Detail to database
        /// </summary>
        /// <param name="districtId">Id of District</param>
        /// <param name="streetId">Id of Street</param>
        /// <returns>Id of insert row</returns>
        public short Insert(short districtId, short streetId)
        {
            if (DistrictBLO.IsIdValid(districtId)
                || StreetBLO.IsIdValid(streetId))
            {
                DISTRICT_DETAIL entity = new DISTRICT_DETAIL();
                entity.DistrictId = districtId;
                entity.StreetId = streetId;
                GlobalVariable.DATA_CONTEXT.DISTRICT_DETAILs.InsertOnSubmit(entity);
                GlobalVariable.DATA_CONTEXT.SubmitChanges();
                return entity.Id;
            }
            else
            {
                throw new Exception(GlobalVariable.INVALID_ID);
            }
        }

        /// <summary>
        /// Update an entity District Detail to database
        /// </summary>
        /// <param name="entity">Entity to update</param>
        /// <exception cref="System.Exception">Throw when entity has an invalid Id</exception>
        public void Update(DISTRICT_DETAIL entity)
        {
            if (IsIdValid(entity.Id))
            {
                DISTRICT_DETAIL oldEntity =
                    GlobalVariable.DATA_CONTEXT.DISTRICT_DETAILs.Single(record => record.Id == entity.Id);
                oldEntity.DistrictId = entity.DistrictId;
                oldEntity.StreetId = entity.StreetId;
                GlobalVariable.DATA_CONTEXT.SubmitChanges();
            }
            else
            {
                throw new Exception(GlobalVariable.INVALID_ID);
            }
        }

        /// <summary>
        /// Update an entity District Detail to database
        /// </summary>
        /// <param name="id">Id</param>
        /// <param name="districtId">Id of District</param>
        /// <param name="streetId">If of Street</param>
        public void Update(short id, short districtId, short streetId)
        {
            if (IsIdValid(id))
            {
                DISTRICT_DETAIL entity = new DISTRICT_DETAIL();
                entity.Id = id;
                entity.DistrictId = districtId;
                entity.StreetId = streetId;
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
                var entities = from record in GlobalVariable.DATA_CONTEXT.DISTRICT_DETAILs
                               where record.Id.Equals(id)
                               select record;
                GlobalVariable.DATA_CONTEXT.DISTRICT_DETAILs.DeleteAllOnSubmit(entities);
                GlobalVariable.DATA_CONTEXT.SubmitChanges();
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
            if (GlobalVariable.DATA_CONTEXT.DISTRICT_DETAILs.Count() > 0)
            {
                foreach (DISTRICT_DETAIL item in GlobalVariable.DATA_CONTEXT.DISTRICT_DETAILs)
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
        /// Get all Streets in a District
        /// </summary>
        /// <param name="districtId">Id of District</param>
        /// <returns>List of STREET</returns>
        public List<STREET> GetAllStreetInDistrict(short districtId)
        {
            // Result list
            List<STREET> result = new List<STREET>();
            // District Business logic object
            DistrictBLO districtBLO = new DistrictBLO();
            // Get District object
            DISTRICT district = districtBLO.GetARow(districtId);

            // Loop for District Detail list
            foreach (DISTRICT_DETAIL detail in district.DISTRICT_DETAILs)
            {
                result.Add(detail.STREET);
            }
            return result;
        }

        /// <summary>
        /// Get all Districts on a Street
        /// </summary>
        /// <param name="streetId">Id of Street</param>
        /// <returns>List of DISTRICT</returns>
        public List<DISTRICT> GetAllDistrictOnStreet(short streetId)
        {
            // Result list
            List<DISTRICT> result = new List<DISTRICT>();
            // Street Business logic object
            StreetBLO streetBLO = new StreetBLO();
            // Get Street object
            STREET street = streetBLO.GetARow(streetId);

            // Loop for District Detail list
            foreach (DISTRICT_DETAIL detail in street.DISTRICT_DETAILs)
            {
                result.Add(detail.DISTRICT);
            }
            return result;
        }
        #endregion
    }
}
