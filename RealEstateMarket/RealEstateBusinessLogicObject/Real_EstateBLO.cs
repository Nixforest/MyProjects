using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace RealEstateBusinessLogicObject
{
    public class Real_EstateBLO : BusinessParent<RealEstateDataContext.REAL_ESTATE>
    {
        /// <summary>
        /// Contructor
        /// </summary>
        public Real_EstateBLO()
        {
            _db = new RealEstateDataAccessObject.Real_EstateDAO();
        }

        /// <summary>
        /// Get all row in table REAL_ESTATE
        /// </summary>
        /// <returns>List of entities</returns>
        public override ICollection<RealEstateDataContext.REAL_ESTATE> GetAllRows()
        {
            return base.GetAllRows();
        }

        /// <summary>
        /// Insert a row into REAL_ESTATE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just inserted</returns>
        /// <exception cref="Real_Estate_TypeIDException"></exception>
        /// <exception cref="AddressIDException"></exception>
        /// <exception cref="RoomNumberException: Room number must greater than 0"></exception>
        /// <exception cref="GreaterZeroException: Price must greater than 0"></exception>
        /// <exception cref="UnitIDException"></exception>
        /// <exception cref="Unit_PriceIDException"></exception>
        /// <exception cref="ProjectIDException"></exception>
        /// <exception cref="ContactIDException"></exception>
        public override int Insert(RealEstateDataContext.REAL_ESTATE entity)
        {
            if (new RealEstateDataAccessObject.Real_Estate_TypeDAO().ValidationID(entity.TypeID))
            {
                if (new RealEstateDataAccessObject.AddressDAO().ValidationID(entity.AddressID))
                {
                    if ((entity.LivingRoom >= 0 || entity.LivingRoom == null) &&
                        (entity.BedRoom >= 0 || entity.BedRoom == null) &&
                        (entity.BathRoom >= 0 || entity.BathRoom == null) &&
                        (entity.Storey >= 0 || entity.Storey == null))
                    {
                        if (entity.Price >= 0)
                        {
                            if (new RealEstateDataAccessObject.UnitDAO().ValidationID(entity.UnitID))
                            {
                                if (new RealEstateDataAccessObject.Unit_PriceDAO().ValidationID(entity.UnitPriceID))
                                {
                                    if (new RealEstateDataAccessObject.ProjectDAO().ValidationID((int)entity.ProjectID) || entity.ProjectID == null)
                                    {
                                        if (new RealEstateDataAccessObject.ContactDAO().ValidationID((int)entity.ContactID) || entity.ContactID == null)
                                        {
                                            entity.ID = _db.CreateID();
                                            _db.Insert(entity);
                                            return entity.ID;
                                        }
                                        else throw new RealEstateDataContext.Utility.ContactIDException();
                                    }
                                    else throw new RealEstateDataContext.Utility.ProjectIDException();
                                }
                                else throw new RealEstateDataContext.Utility.Unit_PriceIDException();
                            }
                            else throw new RealEstateDataContext.Utility.UnitIDException();
                        }
                        else throw new RealEstateDataContext.Utility.GreaterZeroException();
                    }
                    else throw new RealEstateDataContext.Utility.RoomNumberException();
                }
                else throw new RealEstateDataContext.Utility.AddressIDException();
            }
            else throw new RealEstateDataContext.Utility.Real_Estate_TypeIDException();
        }

        /// <summary>
        /// Insert a row into REAL_ESTATE table
        /// </summary>
        /// <param name="typeID">ID of type</param>
        /// <param name="addressID">ID of address</param>
        /// <param name="livingRoom">Number of living room</param>
        /// <param name="bedRoom">Number of bed room</param>
        /// <param name="bathRoom">Number of bath room</param>
        /// <param name="storey">Number of storey (floor)</param>
        /// <param name="totalUseArea">Total use area</param>
        /// <param name="campusFront">Size in front of campus</param>
        /// <param name="campusBehind">Size in behind of campus</param>
        /// <param name="campusLength">Length of campus</param>
        /// <param name="buildFront">Size in front of build area</param>
        /// <param name="buildBehind">Size in behind of build area</param>
        /// <param name="buildLength">Length of build area</param>
        /// <param name="legal">Real estate's legal</param>
        /// <param name="direction">Real estate's direction</param>
        /// <param name="frontStreet">Front street</param>
        /// <param name="location">Location</param>
        /// <param name="price">Price</param>
        /// <param name="unitID">ID of unit</param>
        /// <param name="unitPriceID">ID of unit price</param>
        /// <param name="projectID">ID of project</param>
        /// <param name="contactID">ID of contact</param>
        /// <returns>ID of row has just inserted</returns>
        /// <exception cref="Real_Estate_TypeIDException"></exception>
        /// <exception cref="AddressIDException"></exception>
        /// <exception cref="RoomNumberException: Room number must greater than 0"></exception>
        /// <exception cref="GreaterZeroException: Price must greater than 0"></exception>
        /// <exception cref="UnitIDException"></exception>
        /// <exception cref="Unit_PriceIDException"></exception>
        /// <exception cref="ProjectIDException"></exception>
        /// <exception cref="ContactIDException"></exception>
        public int Insert(int typeID, int addressID, int? livingRoom,
            int? bedRoom, int? bathRoom, int? storey, double? totalUseArea,
            double? campusFront, double? campusBehind, double? campusLength,
            double? buildFront, double? buildBehind, double? buildLength,
            string legal, string direction, string frontStreet, string location,
            decimal price, int unitID, int unitPriceID, int? projectID, int? contactID)
        {
            if (new RealEstateDataAccessObject.Real_Estate_TypeDAO().ValidationID(typeID))
            {
                if (new RealEstateDataAccessObject.AddressDAO().ValidationID(addressID))
                {
                    if ((livingRoom >= 0 || livingRoom == null) &&
                        (bedRoom >= 0 || bedRoom == null) &&
                        (bathRoom >= 0 || bathRoom == null) &&
                        (storey >= 0 || storey == null))
                    {
                        if (price >= 0)
                        {
                            if (new RealEstateDataAccessObject.UnitDAO().ValidationID(unitID))
                            {
                                if (new RealEstateDataAccessObject.Unit_PriceDAO().ValidationID(unitPriceID))
                                {
                                    if (new RealEstateDataAccessObject.ProjectDAO().ValidationID((int)projectID) || projectID == null)
                                    {
                                        if (new RealEstateDataAccessObject.ContactDAO().ValidationID((int)contactID) || contactID == null)
                                        {
                                            RealEstateDataContext.REAL_ESTATE entity = new RealEstateDataContext.REAL_ESTATE();
                                            entity.ID = _db.CreateID();
                                            entity.TypeID = typeID;
                                            entity.AddressID = addressID;
                                            entity.LivingRoom = livingRoom;
                                            entity.BedRoom = bedRoom;
                                            entity.BathRoom = bathRoom;
                                            entity.Storey = storey;
                                            entity.TotalUseArea = totalUseArea;
                                            entity.CampusFront = campusFront;
                                            entity.CampusBehind = campusBehind;
                                            entity.CampusLength = campusLength;
                                            entity.BuildFront = buildFront;
                                            entity.BuildBehind = buildBehind;
                                            entity.BuildLength = buildLength;
                                            entity.Legal = legal;
                                            entity.Direction = direction;
                                            entity.FrontStreet = frontStreet;
                                            entity.Location = location;
                                            entity.Price = price;
                                            entity.UnitID = unitID;
                                            entity.UnitPriceID = unitPriceID;
                                            entity.ProjectID = projectID;
                                            entity.ContactID = contactID;

                                            _db.Insert(entity);
                                            return entity.ID;
                                        }
                                        else throw new RealEstateDataContext.Utility.ContactIDException();
                                    }
                                    else throw new RealEstateDataContext.Utility.ProjectIDException();
                                }
                                else throw new RealEstateDataContext.Utility.Unit_PriceIDException();
                            }
                            else throw new RealEstateDataContext.Utility.UnitIDException();
                        }
                        else throw new RealEstateDataContext.Utility.GreaterZeroException();
                    }
                    else throw new RealEstateDataContext.Utility.RoomNumberException();
                }
                else throw new RealEstateDataContext.Utility.AddressIDException();
            }
            else throw new RealEstateDataContext.Utility.Real_Estate_TypeIDException();
        }

        /// <summary>
        /// Update a row in REAL_ESTATE table
        /// </summary>
        /// <param name="entity">Entity</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="Real_EstateIDException"></exception>
        /// <exception cref="Real_Estate_TypeIDException"></exception>
        /// <exception cref="AddressIDException"></exception>
        /// <exception cref="RoomNumberException: Room number must greater than 0"></exception>
        /// <exception cref="GreaterZeroException: Price must greater than 0"></exception>
        /// <exception cref="UnitIDException"></exception>
        /// <exception cref="Unit_PriceIDException"></exception>
        /// <exception cref="ProjectIDException"></exception>
        /// <exception cref="ContactIDException"></exception>
        public override int Update(RealEstateDataContext.REAL_ESTATE entity)
        {
            if (ValidationID(entity.ID))
            {
                if (new RealEstateDataAccessObject.Real_Estate_TypeDAO().ValidationID(entity.TypeID))
                {
                    if (new RealEstateDataAccessObject.AddressDAO().ValidationID(entity.AddressID))
                    {
                        if ((entity.LivingRoom >= 0 || entity.LivingRoom == null) &&
                            (entity.BedRoom >= 0 || entity.BedRoom == null) &&
                            (entity.BathRoom >= 0 || entity.BathRoom == null) &&
                            (entity.Storey >= 0 || entity.Storey == null))
                        {
                            if (entity.Price >= 0)
                            {
                                if (new RealEstateDataAccessObject.UnitDAO().ValidationID(entity.UnitID))
                                {
                                    if (new RealEstateDataAccessObject.Unit_PriceDAO().ValidationID(entity.UnitPriceID))
                                    {
                                        if (new RealEstateDataAccessObject.ProjectDAO().ValidationID((int)entity.ProjectID) || entity.ProjectID == null)
                                        {
                                            if (new RealEstateDataAccessObject.ContactDAO().ValidationID((int)entity.ContactID) || entity.ContactID == null)
                                            {
                                                _db.Update(entity);
                                                return entity.ID;
                                            }
                                            else throw new RealEstateDataContext.Utility.ContactIDException();
                                        }
                                        else throw new RealEstateDataContext.Utility.ProjectIDException();
                                    }
                                    else throw new RealEstateDataContext.Utility.Unit_PriceIDException();
                                }
                                else throw new RealEstateDataContext.Utility.UnitIDException();
                            }
                            else throw new RealEstateDataContext.Utility.GreaterZeroException();
                        }
                        else throw new RealEstateDataContext.Utility.RoomNumberException();
                    }
                    else throw new RealEstateDataContext.Utility.AddressIDException();
                }
                else throw new RealEstateDataContext.Utility.Real_Estate_TypeIDException();
            }
            else throw new RealEstateDataContext.Utility.Real_EstateIDException();
        }

        /// <summary>
        /// Update a row in REAL_ESTATE table
        /// </summary>
        /// <param name="id">ID of row</param>
        /// <param name="typeID">ID of type</param>
        /// <param name="addressID">ID of address</param>
        /// <param name="livingRoom">Number of living room</param>
        /// <param name="bedRoom">Number of bed room</param>
        /// <param name="bathRoom">Number of bath room</param>
        /// <param name="storey">Number of storey (floor)</param>
        /// <param name="totalUseArea">Total use area</param>
        /// <param name="campusFront">Size in front of campus</param>
        /// <param name="campusBehind">Size in behind of campus</param>
        /// <param name="campusLength">Length of campus</param>
        /// <param name="buildFront">Size in front of build area</param>
        /// <param name="buildBehind">Size in behind of build area</param>
        /// <param name="buildLength">Length of build area</param>
        /// <param name="legal">Real estate's legal</param>
        /// <param name="direction">Real estate's direction</param>
        /// <param name="frontStreet">Front street</param>
        /// <param name="location">Location</param>
        /// <param name="price">Price</param>
        /// <param name="unitID">ID of unit</param>
        /// <param name="unitPriceID">ID of unit price</param>
        /// <param name="projectID">ID of project</param>
        /// <param name="contactID">ID of contact</param>
        /// <returns>ID of row has just updated</returns>
        /// <exception cref="Real_EstateIDException"></exception>
        /// <exception cref="Real_Estate_TypeIDException"></exception>
        /// <exception cref="AddressIDException"></exception>
        /// <exception cref="RoomNumberException: Room number must greater than 0"></exception>
        /// <exception cref="GreaterZeroException: Price must greater than 0"></exception>
        /// <exception cref="UnitIDException"></exception>
        /// <exception cref="Unit_PriceIDException"></exception>
        /// <exception cref="ProjectIDException"></exception>
        /// <exception cref="ContactIDException"></exception>
        public int Update(int id, int typeID, int addressID, int? livingRoom,
            int? bedRoom, int? bathRoom, int? storey, double? totalUseAre,
            double? campusFront, double? campusBehind, double? campusLength,
            double? buildFront, double? buildBehind, double? buildLength,
            string legal, string direction, string frontStreet, string location,
            decimal price, int unitID, int unitPriceID, int? projectID, int? contactID)
        {
            if (ValidationID(id))
            {
                if (new RealEstateDataAccessObject.Real_Estate_TypeDAO().ValidationID(typeID))
                {
                    if (new RealEstateDataAccessObject.AddressDAO().ValidationID(addressID))
                    {
                        if ((livingRoom >= 0 || livingRoom == null) &&
                            (bedRoom >= 0 || bedRoom == null) &&
                            (bathRoom >= 0 || bathRoom == null) &&
                            (storey >= 0 || storey == null))
                        {
                            if (price >= 0)
                            {
                                if (new RealEstateDataAccessObject.UnitDAO().ValidationID(unitID))
                                {
                                    if (new RealEstateDataAccessObject.Unit_PriceDAO().ValidationID(unitPriceID))
                                    {
                                        if (new RealEstateDataAccessObject.ProjectDAO().ValidationID((int)projectID) || projectID == null)
                                        {
                                            if (new RealEstateDataAccessObject.ContactDAO().ValidationID((int)contactID) || contactID == null)
                                            {
                                                RealEstateDataContext.REAL_ESTATE entity = new RealEstateDataContext.REAL_ESTATE();
                                                entity.ID = id;
                                                entity.TypeID = typeID;
                                                entity.AddressID = addressID;
                                                entity.LivingRoom = livingRoom;
                                                entity.BedRoom = bedRoom;
                                                entity.BathRoom = bathRoom;
                                                entity.Storey = storey;
                                                entity.TotalUseArea = totalUseAre;
                                                entity.CampusFront = campusFront;
                                                entity.CampusBehind = campusBehind;
                                                entity.CampusLength = campusLength;
                                                entity.BuildFront = buildFront;
                                                entity.BuildBehind = buildBehind;
                                                entity.BuildLength = buildLength;
                                                entity.Legal = legal;
                                                entity.Direction = direction;
                                                entity.FrontStreet = frontStreet;
                                                entity.Location = location;
                                                entity.Price = price;
                                                entity.UnitID = unitID;
                                                entity.UnitPriceID = unitPriceID;
                                                entity.ProjectID = projectID;
                                                entity.ContactID = contactID;

                                                _db.Update(entity);
                                                return entity.ID;
                                            }
                                            else throw new RealEstateDataContext.Utility.ContactIDException();
                                        }
                                        else throw new RealEstateDataContext.Utility.ProjectIDException();
                                    }
                                    else throw new RealEstateDataContext.Utility.Unit_PriceIDException();
                                }
                                else throw new RealEstateDataContext.Utility.UnitIDException();
                            }
                            else throw new RealEstateDataContext.Utility.GreaterZeroException();
                        }
                        else throw new RealEstateDataContext.Utility.RoomNumberException();
                    }
                    else throw new RealEstateDataContext.Utility.AddressIDException();
                }
                else throw new RealEstateDataContext.Utility.Real_Estate_TypeIDException();
            }
            else throw new RealEstateDataContext.Utility.Real_EstateIDException();
        }

        /// <summary>
        /// Delete a row from REAL_ESTATE table
        /// </summary>
        /// <param name="ID">ID of row want to delete</param>
        /// <returns>ID of row has just deleted</returns>
        /// <exception cref="Real_EstateIDException"></exception>
        public override void Delete(int ID)
        {
            if (ValidationID(ID))
            {
                _db.Delete(ID);
            }
            else throw new RealEstateDataContext.Utility.Real_EstateIDException();
        }

        /// <summary>
        /// Get a row in REAL_ESTATE table
        /// </summary>
        /// <param name="ID">ID of row</param>
        /// <returns>Entity</returns>
        /// <exception cref="Real_EstateIDException"></exception>
        public override RealEstateDataContext.REAL_ESTATE GetARecord(int ID)
        {
            if (ValidationID(ID))
            {
                return _db.GetARecord(ID);
            }
            else throw new RealEstateDataContext.Utility.Real_EstateIDException();
        }
    }
}
