using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PhongKhamManagement.Utilities;
using PhongKhamManagement.DataAccess;

namespace PhongKhamManagement.BusinessLogic
{
    /// <summary>
    /// Business logic class for Job object
    /// </summary>
    public class JobBLO
    {
        #region Default Methods
        /// <summary>
        /// Get all rows in Job table
        /// </summary>
        /// <returns>List of Job object</returns>
        public List<JOB> GetAllRows()
        {
            return GlobalVariable.DATA_CONTEXT.JOBs.ToList();
        }

        /// <summary>
        /// Insert an entity Job to database
        /// </summary>
        /// <param name="entity">Entity to insert</param>
        /// <returns>Id of insert row</returns>
        public short Insert(JOB entity)
        {
            GlobalVariable.DATA_CONTEXT.JOBs.InsertOnSubmit(entity);
            GlobalVariable.DATA_CONTEXT.SubmitChanges();
            return entity.Id;
        }

        /// <summary>
        /// Insert an entity Job to database
        /// </summary>
        /// <param name="name">Name of Job</param>
        /// <param name="detail">Detail</param>
        /// <returns>Id of insert row</returns>
        public short Insert(string name, string detail)
        {
            JOB entity = new JOB();
            entity.Name = name;
            entity.Detail = detail;
            GlobalVariable.DATA_CONTEXT.JOBs.InsertOnSubmit(entity);
            GlobalVariable.DATA_CONTEXT.SubmitChanges();
            return entity.Id;
        }

        /// <summary>
        /// Update an entity Job to database
        /// </summary>
        /// <param name="entity">Entity to update</param>
        /// <exception cref="System.Exception">Throw when entity has an invalid Id</exception>
        public void Update(JOB entity)
        {
            if (IsIdValid(entity.Id))
            {
                JOB oldEntity =
                    GlobalVariable.DATA_CONTEXT.JOBs.Single(record => record.Id == entity.Id);
                oldEntity.Name = entity.Name;
                oldEntity.Detail = entity.Detail;
                GlobalVariable.DATA_CONTEXT.SubmitChanges();
            }
            else
            {
                throw new Exception(GlobalVariable.INVALID_ID);
            }
        }

        /// <summary>
        /// Update an entity Job to database
        /// </summary>
        /// <param name="id">Id</param>
        /// <param name="name">Name</param>
        /// <param name="detail">Detail</param>
        /// <exception cref="System.Exception">Throw when entity has an invalid Id</exception>
        public void Update(short id, string name, string detail)
        {
            if (IsIdValid(id))
            {
                JOB entity = new JOB();
                entity.Id = id;
                entity.Name = name;
                entity.Detail = detail;
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
                var entities = from record in GlobalVariable.DATA_CONTEXT.JOBs
                               where record.Id.Equals(id)
                               select record;
                GlobalVariable.DATA_CONTEXT.JOBs.DeleteAllOnSubmit(entities);
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
        /// <param name="id">Id of Job</param>
        /// <returns>JOB object</returns>
        public JOB GetARow(short id)
        {
            if (IsIdValid(id))
            {
                var entities = from record in GlobalVariable.DATA_CONTEXT.JOBs
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
            if (GlobalVariable.DATA_CONTEXT.JOBs.Count() > 0)
            {
                foreach (JOB item in GlobalVariable.DATA_CONTEXT.JOBs)
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
