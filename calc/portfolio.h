#ifndef GDM_PORTFOLIO
#define GDM_PORTFOLIO

class Order {
public:

protected:

private:
    const std::string& _symbol;

};

class Portfolio
{
public:
    Portfolio();
    virtual ~Portfolio();

    bool addOrder(const std::string& symbol, int quantity, double price);
    std::vector<
    void pretty();

protected:


private:
};

#endif
