#ifndef GDM_ORDER
#define GDM_ORDER

#include <stdint.h>
#include <string.h>
#include <string>

namespace gdm
{

class Order
{
public:
    enum OrderType  { NEW=0, CANCEL, MODIFY };
    enum SideType   { BUY=0, SELL, SSHORT };
    enum PriceType  { LMT=0, MKT };
    enum ExecType   { DAY=0, IOC, GTD };

    typedef uint64_t symbolid_t;
    typedef uint64_t orderid_t;

    Order(uint64_t symbolID, const char* symbol, double price, int qty, OrderType orderType,
            SideType sideType, PriceType priceType, ExecType execType, uint64_t orderID)
    :   _symbolID(symbolID), _price(price), _qty(qty),
        _orderType(orderType), _sideType(sideType), _priceType(priceType),
        _execType(execType), _orderID(orderID)
    {
        strncpy(_symbol, symbol, sizeof(_symbol));
    }

    Order()
    :   _symbolID(0), _price(.0), _qty(0),
        _orderType(0), _sideType(0), _priceType(0),
        _execType(0), _orderID(0)
    {
    }

    // define static utility methods
    static const char* getSideTypeStr(SideType st);
    static const char* getOrderTypeStr(OrderType ot);
    static const char* getPriceTypeStr(PriceType pt);
    static const char* getExecTypeStr(ExecType et);


    // printers
    void pretty() const;

    // gettors
    inline symbolid_t   getSymbolID()   const { return _symbolID; }
    inline std::string  getSymbol()     const { return std::string(_symbol); }
    inline double       getPrice()      const { return _price; }
    inline int          getQty()        const { return _qty; }
    inline OrderType    getOrderType()  const { return static_cast<OrderType>(_orderType); }
    inline SideType     getSideType()   const { return static_cast<SideType>(_sideType); }
    inline PriceType    getPriceType()  const { return static_cast<PriceType>(_priceType); }
    inline ExecType     getExecType()   const { return static_cast<ExecType>(_execType); }
    inline orderid_t    getOrderID()    const { return _orderID; }

    // settors
    inline void setSymbolID(symbolid_t v)   { _symbolID = v; }
    inline void setSymbol(const char* v)    { strncpy(_symbol, v, sizeof(_symbol)); }
    inline void setPrice(double v)          { _price = v; }
    inline void setQty(int v)               { _qty = v; }
    inline void setOrderType(OrderType v)   { _orderType = static_cast<char>(v); }
    inline void setSideType(SideType v)     { _sideType = static_cast<char>(v); }
    inline void setPriceType(PriceType v)   { _priceType = static_cast<char>(v); }
    inline void setExecType(ExecType v)     { _execType =  static_cast<char>(v); }
    inline void setOrderID(orderid_t v)     { _orderID = v; }


protected:
private:
    symbolid_t  _symbolID;
    char        _symbol[8];
    char        _pad[32];       // for future use
    double      _price;
    int         _qty;
    char        _orderType;     // 0:New;1:Cancel:2:Mod
    char        _sideType;      // 0:buy;1=sell,2=sellshort
    char        _priceType;     // 0:LMT;1=MKT
    char        _execType;
    uint64_t    _orderID;
};

} // close namespace gdm
#endif

