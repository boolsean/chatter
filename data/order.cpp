#include "order.h"
#include <iostream>
#include <iomanip>


namespace gdm
{
const char* Order::getSideTypeStr(Order::SideType st)
{
    switch(st) {
        case BUY:
            return "BUY";
        case SELL:
            return "SEL";
        case SSHORT:
            return "SHT";
        default:
            return "???";
    }
}
const char* Order::getOrderTypeStr(Order::OrderType ot)
{
    switch(ot) {
        case NEW:
            return "NEW";
        case CANCEL:
            return "CXL";
        case MODIFY:
            return "MOD";
        default:
            return "???";
    }
}

const char* Order::getPriceTypeStr(Order::PriceType pt)
{
    switch(pt) {
        case LMT:
            return "LMT";
        case MKT:
            return "MKT";
        default:
            return "???";
    }
}

const char* Order::getExecTypeStr(Order::ExecType et)
{
    switch(et) {
        case DAY:
            return "DAY";
        case IOC:
            return "IOC";
        case GTD:
            return "GTD";
        default:
            return "???";
    }
}

void Order::pretty() const
{
    std::cout << _symbolID
        << "|" << _symbol
        << "|" << getOrderTypeStr(static_cast<OrderType>(_orderType))
        << "|" << getSideTypeStr(static_cast<SideType>(_sideType))
        << "|" << getPriceTypeStr(static_cast<PriceType>(_priceType))
        << "|" << getExecTypeStr(static_cast<ExecType>(_execType))
        << "|" << (_sideType == BUY ? _qty : _qty*-1)
        << "|" << _price
        << "|" << _orderID << std::endl;
}

} // close namespace gdm
