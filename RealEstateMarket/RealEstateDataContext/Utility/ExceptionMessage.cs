using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace RealEstateDataContext.Utility
{
    public class AddressIDException : Exception { }
    public class NationIDException : Exception { }
    public class CityIDException : Exception { }
    public class DistrictIDException : Exception { }
    public class WardIDException : Exception { }
    public class StreetIDException : Exception { }
    public class ShareCapitalException : Exception { }
    public class RoomNumberException : Exception { }
    public class CompanyIDException : Exception { }
    public class UserIDException : Exception { }
    public class CustomerIDException : Exception { }
    public class GroupIDException : Exception { }
    public class ImageIDException : Exception { }
    public class News_Sale_TypeIDException : Exception { }
    public class News_SaleIDException : Exception { }
    public class Real_EstateIDException : Exception { }
    public class Real_Estate_TypeIDException : Exception { }
    public class Rate_LimitationException : Exception { }
    public class News_TypeIDException : Exception { }
    public class NewsIDException : Exception { }
    public class Project_TypeIDException : Exception { }
    public class ProjectIDException : Exception { }
    public class GreaterZeroException : Exception { }
    public class UnitIDException : Exception { }
    public class Unit_PriceIDException : Exception { }
    public class ContactIDException : Exception { }
    public class RuleIDException : Exception { }
    public class UtilityIDException : Exception { }

    public class ExceptionMessage
    {
        public static string AddressID = "AddressID Not Exist";
        public static string NationID = "NationID Not Exist";
        public static string CityID = "CityID Not Exist";
        public static string DistrictID = "DistrictID Not Exist";
        public static string WardID = "WardID Not Exist";
        public static string StreetID = "StreetID Not Exist";
        public static string ShareCapital = "Share Capital Must Greater Than Zero";
        public static string CompanyID = "CompanyID Not Exist";
        public static string UserID = "UserID Not Exist";
        public static string CustomerID = "CustomerID Not Exist";
        public static string GroupID = "GroupID Not Exist";
    }
}
