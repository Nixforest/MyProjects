using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class News_SaleBLO : BusinessParent<RealEstateDataContext.NEWS_SALE>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public News_SaleBLO()
        {
            _db = new RealEstateDataAccessObject.News_SaleDAO();
        }

        /// <summary>
        /// Get all row in table NEWS_SALE
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.NEWS_SALE> GetAllRows()
        {
            return new ObservableCollection<RealEstateDataContext.NEWS_SALE>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into NEWS_SALE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just inserted</returns>
        public override int Insert(RealEstateDataContext.NEWS_SALE entity)
        {
            entity.ID = _db.CreateID();
            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Insert a row into NEWS_SALE table
        /// </summary>
        /// <param name="typeID">ID of type</param>
        /// <param name="title">News sale's title</param>
        /// <param name="content">News sale's content</param>
        /// <param name="realEstateID">Id of real estate</param>
        /// <param name="rate">News sale's rate</param>
        /// <param name="updateTime">News sale's update time</param>
        /// <returns>ID of row has just inserted</returns>
        public int Insert(int typeID, string title, string content,
            int realEstateID, int? rate, DateTime updateTime)
        {
            RealEstateDataContext.NEWS_SALE entity = new RealEstateDataContext.NEWS_SALE();
            entity.ID = _db.CreateID();
            entity.TypeID = typeID;
            entity.Title = title;
            entity.Content = content;
            entity.RealEstateID = realEstateID;
            entity.Rate = rate;
            entity.UpdateTime = updateTime;

            _db.Insert(entity);
            return entity.ID;
        }

        /// <summary>
        /// Update a row in NEWS_SALE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="News_SaleIDException"></exception>
        /// <exception cref="News_Sale_TypeIDException"></exception>
        /// <exception cref="Real_EstateIDException"></exception>
        /// <exception cref="Rate_LimitationException: Rate value must between MinRate and MaxRate"></exception>
        public override int Update(RealEstateDataContext.NEWS_SALE entity)
        {
            if (ValidationID(entity.ID))
            {
                if (new RealEstateDataAccessObject.News_Sale_TypeDAO().ValidationID(entity.TypeID))
                {
                    if (new RealEstateDataAccessObject.Real_EstateDAO().ValidationID(entity.RealEstateID))
                    {
                        if (entity.Rate == null ||
                            (entity.Rate >= RealEstateBusinessLogicObject.Parameter.MinRate && 
                                entity.Rate <= RealEstateBusinessLogicObject.Parameter.MaxRate))
                        {
                            _db.Update(entity);
                            return entity.ID;
                        }
                        else throw new RealEstateDataContext.Utility.Rate_LimitationException();
                    }
                    else throw new RealEstateDataContext.Utility.Real_EstateIDException();
                }
                else throw new RealEstateDataContext.Utility.News_Sale_TypeIDException();
            }
            else throw new RealEstateDataContext.Utility.News_SaleIDException();
        }

        /// <summary>
        /// Update a row in NEWS_SALE table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="typeID">ID of type</param>
        /// <param name="title">News sale's title</param>
        /// <param name="content">News sale's content</param>
        /// <param name="realEstateID">Id of real estate</param>
        /// <param name="rate">News sale's rate</param>
        /// <param name="updateTime">News sale's update time</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="News_SaleIDException"></exception>
        /// <exception cref="News_Sale_TypeIDException"></exception>
        /// <exception cref="Real_EstateIDException"></exception>
        /// <exception cref="Rate_LimitationException: Rate value must between MinRate and MaxRate"></exception>
        public int Update(int id, int typeID, string title, string content,
            int realEstateID, int? rate, DateTime updateTime)
        {
            if (ValidationID(id))
            {
                if (new RealEstateDataAccessObject.News_Sale_TypeDAO().ValidationID(typeID))
                {
                    if (new RealEstateDataAccessObject.Real_EstateDAO().ValidationID(realEstateID))
                    {
                        if (rate == null ||
                            (rate >= RealEstateBusinessLogicObject.Parameter.MinRate && 
                                rate <= RealEstateBusinessLogicObject.Parameter.MaxRate))
                        {
                            RealEstateDataContext.NEWS_SALE entity = new RealEstateDataContext.NEWS_SALE();
                            entity.ID = _db.CreateID();
                            entity.TypeID = typeID;
                            entity.Title = title;
                            entity.Content = content;
                            entity.RealEstateID = realEstateID;
                            entity.Rate = rate;
                            entity.UpdateTime = updateTime;

                            _db.Update(entity);
                            return entity.ID;
                        }
                        else throw new RealEstateDataContext.Utility.Rate_LimitationException();
                    }
                    else throw new RealEstateDataContext.Utility.Real_EstateIDException();
                }
                else throw new RealEstateDataContext.Utility.News_Sale_TypeIDException();
            }
            else throw new RealEstateDataContext.Utility.News_SaleIDException();
        }

        /// <summary>
        /// Delete a row from NEWS_SALE table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row has just deleted</returns>
        /// <exception cref="News_SaleIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.News_SaleIDException();
        }

        /// <summary>
        /// Get a row in NEWS_SALE table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="News_SaleIDException"></exception>
        public override RealEstateDataContext.NEWS_SALE GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.News_SaleIDException();
        }
    }
}
