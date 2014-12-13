using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class NewsBLO : BusinessParent<RealEstateDataContext.NEW>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public NewsBLO()
        {
            _db = new RealEstateDataAccessObject.NewsDAO();
        }

        /// <summary>
        /// Get all row in table NEWS
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.NEW> GetAllRows()
        {
            return new ObservableCollection<RealEstateDataContext.NEW>(_db.GetAllRows());
        }

        /// <summary>
        /// Insert a row into NEWS table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just inserted</returns>
        /// <exception cref="News_TypeIDException"></exception>
        /// <exception cref="Rate_LimitationException: Rate value must between MinRate and MaxRate""></exception>
        /// <exception cref="ImageIDException"></exception>
        public override int Insert(RealEstateDataContext.NEW entity)
        {
            if (new RealEstateDataAccessObject.News_TypeDAO().ValidationID(entity.TypeID))
            {
                if (entity.Rate == null ||
                    (entity.Rate >= RealEstateBusinessLogicObject.Parameter.MinRate &&
                    entity.Rate <= RealEstateBusinessLogicObject.Parameter.MaxRate))
                {
                    if (new RealEstateDataAccessObject.ImageDAO().ValidationID(entity.ImageID))
                    {
                        entity.ID = _db.CreateID();
                        _db.Insert(entity);
                        return entity.ID;
                    }
                    else throw new RealEstateDataContext.Utility.ImageIDException();
                }
                else throw new RealEstateDataContext.Utility.Rate_LimitationException();
            }
            else throw new RealEstateDataContext.Utility.News_TypeIDException();
        }

        /// <summary>
        /// Insert a row into NEWS table
        /// </summary>
        /// <param name="typeID">ID of News type</param>
        /// <param name="title">News's title</param>
        /// <param name="content">News's content</param>
        /// <param name="author">News's author</param>
        /// <param name="rate">News's rate</param>
        /// <param name="publishTime">News's publish time</param>
        /// <param name="imageID">ID of image</param>
        /// <returns>ID of row has just inserted</returns>
        /// <exception cref="News_TypeIDException"></exception>
        /// <exception cref="Rate_LimitationException: Rate value must between MinRate and MaxRate""></exception>
        /// <exception cref="ImageIDException"></exception>
        public int Insert(int typeID, string title, string content,
            string author, int? rate, DateTime publishTime, int imageID)
        {
            if (new RealEstateDataAccessObject.News_TypeDAO().ValidationID(typeID))
            {
                if (rate == null || (rate >= RealEstateBusinessLogicObject.Parameter.MinRate &&
                    rate <= RealEstateBusinessLogicObject.Parameter.MaxRate))
                {
                    if (new RealEstateDataAccessObject.ImageDAO().ValidationID(imageID))
                    {
                        RealEstateDataContext.NEW entity = new RealEstateDataContext.NEW();

                        entity.ID = _db.CreateID();
                        entity.TypeID = typeID;
                        entity.Title = title;
                        entity.Content = content;
                        entity.Author = author;
                        entity.Rate = rate;
                        entity.PublishTime = publishTime;
                        entity.ImageID = imageID;

                        _db.Insert(entity);
                        return entity.ImageID;
                    }
                    else throw new RealEstateDataContext.Utility.ImageIDException();
                }
                else throw new RealEstateDataContext.Utility.Rate_LimitationException();
            }
            else throw new RealEstateDataContext.Utility.News_TypeIDException();
        }

        /// <summary>
        /// Update a row in NEWS table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="NewsIDException"></exception>
        /// <exception cref="News_TypeIDException"></exception>
        /// <exception cref="Rate_LimitationException: Rate value must between MinRate and MaxRate""></exception>
        /// <exception cref="ImageIDException"></exception>
        public override int Update(RealEstateDataContext.NEW entity)
        {
            if (ValidationID(entity.ID))
            {
                if (new RealEstateDataAccessObject.News_TypeDAO().ValidationID(entity.TypeID))
                {
                    if (entity.Rate == null ||
                        (entity.Rate >= RealEstateBusinessLogicObject.Parameter.MinRate &&
                        entity.Rate <= RealEstateBusinessLogicObject.Parameter.MaxRate))
                    {
                        if (new RealEstateDataAccessObject.ImageDAO().ValidationID(entity.ImageID))
                        {
                            _db.Update(entity);
                            return entity.ID;
                        }
                        else throw new RealEstateDataContext.Utility.ImageIDException();
                    }
                    else throw new RealEstateDataContext.Utility.Rate_LimitationException();
                }
                else throw new RealEstateDataContext.Utility.News_TypeIDException();
            }
            else throw new RealEstateDataContext.Utility.NewsIDException();
        }

        /// <summary>
        /// Update a row in NEWS table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="typeID">ID of News type</param>
        /// <param name="title">News's title</param>
        /// <param name="content">News's content</param>
        /// <param name="author">News's author</param>
        /// <param name="rate">News's rate</param>
        /// <param name="publishTime">News's publish time</param>
        /// <param name="imageID">ID of image</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="NewsIDException"></exception>
        /// <exception cref="News_TypeIDException"></exception>
        /// <exception cref="Rate_LimitationException: Rate value must between MinRate and MaxRate""></exception>
        /// <exception cref="ImageIDException"></exception>
        public int Update(int id, int typeID, string title, string content,
            string author, int? rate, DateTime publishTime, int imageID)
        {
            if (ValidationID(id))
            {
                if (new RealEstateDataAccessObject.News_TypeDAO().ValidationID(typeID))
                {
                    if (rate == null || (rate >= RealEstateBusinessLogicObject.Parameter.MinRate &&
                        rate <= RealEstateBusinessLogicObject.Parameter.MaxRate))
                    {
                        if (new RealEstateDataAccessObject.ImageDAO().ValidationID(imageID))
                        {
                            RealEstateDataContext.NEW entity = new RealEstateDataContext.NEW();
                            entity.ID = id;
                            entity.TypeID = typeID;
                            entity.Title = title;
                            entity.Content = content;
                            entity.Author = author;
                            entity.Rate = rate;
                            entity.PublishTime = publishTime;
                            entity.ImageID = imageID;

                            _db.Update(entity);
                            return entity.ID;
                        }
                        else throw new RealEstateDataContext.Utility.ImageIDException();
                    }
                    else throw new RealEstateDataContext.Utility.Rate_LimitationException();
                }
                else throw new RealEstateDataContext.Utility.News_TypeIDException();
            }
            else throw new RealEstateDataContext.Utility.NewsIDException();
        }

        /// <summary>
        /// Delete a row from NEWS table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row has just deleted</returns>
        /// <exception cref="NewsIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.NewsIDException();
        }

        /// <summary>
        /// Get a row in NEWS table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="NewsIDException"></exception>
        public override RealEstateDataContext.NEW GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.NewsIDException();
        }
    }
}
