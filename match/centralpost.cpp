#include "centralpost.h"

namespace gdm {

CentralPost::CentralPost()
{
}

bool CentralPost::postOrder(const Order& order)
{
    if(_orders.count(order.getOrderID()) > 0)
        return false;

    _orders[order.getOrderID()] = order;
    return true;
}

int CentralPost::getOrders(std::list<Order>& orders)
{
    orders.clear();

    for(id2ordermap_cit_t it = _orders.begin(); it != _orders.end(); it++) {
        orders.push_back(it->second);
    }
    return 0;
}

int CentralPost::removeOrder()
{
    return 0;
}

int CentralPost::getOrderStatus()
{
    return 0;
}

int CentralPost::clearAllOrders()
{
    return 0;
}

} // close namespace gdm
