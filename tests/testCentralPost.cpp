#include "order.h"
#include "centralpost.h"

#include "timeutils.h"
#include <stdlib.h>
#include <list>
#include <iostream>

using namespace gdm;


gdm::CentralPost centralPost;

const gdm::Order::symbolid_t SID = 1;
const char* SYM = "SPY";
const gdm::Order::orderid_t OID = 100000;
const double PX_INC = .01;

static Order genNewOrder(Order::symbolid_t sid=1, const char* sym="SPY")
{
    static const Order::OrderType ot = Order::NEW;
    static const Order::PriceType pt = Order::LMT;
    static const Order::ExecType et = Order::DAY;

    static Order::SideType st = Order::BUY;
    static double price = 210.23;
    static int qty = 20;
    static Order::orderid_t oid = 100005;

    Order order(sid, sym, price, qty, ot, st, pt, et, oid);

    price += .01;
    qty += 1;
    st = (st == Order::BUY) ? Order::SELL : Order::BUY;
    oid += 1;

    return order;
}



int main()
{

    gdmtime_t before = getTimeNow();
    gdmtime_t after = getTimeNow();

    centralPost.postOrder(genNewOrder());
    centralPost.postOrder(genNewOrder());
    centralPost.postOrder(genNewOrder());
    centralPost.postOrder(genNewOrder());
    centralPost.postOrder(genNewOrder());
    centralPost.postOrder(genNewOrder());
    centralPost.postOrder(genNewOrder());

    std::cout << "curtime:" << getTimeAsStr(before) << std::endl;
    std::cout << "curtime:" << getTimeAsStr(after) << std::endl;

    std::list<Order> orders;

    centralPost.getOrders(orders);


    for(std::list<Order>::const_iterator it = orders.begin(); it != orders.end(); it++)
    {
        it->pretty();
    }


    return 0;
}
