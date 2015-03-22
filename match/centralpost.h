#ifndef GDM_CENTRALPOST
#define GDM_CENTRALPOST

#include "order.h"


#include <map>
#include <list>

namespace gdm {

class CentralPost
{
public:
    typedef std::map<Order::orderid_t, Order>   id2ordermap_t;
    typedef id2ordermap_t::iterator             id2ordermap_it_t;
    typedef id2ordermap_t::const_iterator       id2ordermap_cit_t;

    CentralPost();

    bool postOrder(const Order& order);
    int getOrders(std::list<Order>& orders);
    int removeOrder();
    int getOrderStatus();
    int clearAllOrders();

protected:

private:
    id2ordermap_t _orders;
};

} // close namespace gdm

#endif
