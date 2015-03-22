#ifndef GDM_CENTRALPOST
#define GDM_CENTRALPOST

namespace gdm {

class CentralPost
{
public:
    CentralPost();

    bool postOrder();
    int getOrders();
    int removeOrder();
    int getOrderStatus();
    int clearAllOrders();

protected:

private:
};

} // close namespace gdm

#endif
