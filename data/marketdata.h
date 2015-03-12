#ifndef GDM_MARKETDATA_H
#define GDM_MARKETDATA_H

#include <vector>
#include <string>

// most basic marketdata quote (can be single or aggregated)
namespace gdm {
class MarketDataQuote
{
public:
    MarketDataQuote(double price, int size, int num=1, int flag=0)
        :   _price(price), _size(size), _num(num), _flag(flag)
    {
    }

    void pretty() const;
    void set(double price, int size, int num=1, int flag=0);
    double getPrice() const;
    int getSize() const;
    int getNum() const;
    int getFlag() const;

private:
    double _price;
    int _size;
    int _num;
    int _flag;

};

class MarketDataSide
{
public:
    typedef std::vector<MarketDataQuote> quotes_t;
    typedef quotes_t::iterator quotes_itr_t;
    typedef quotes_t::const_iterator quotes_citr_t;

    MarketDataSide();
    void pretty() const;
    void addQuote(const MarketDataQuote& quote);
    void addQuote(double price, int size, int num=1, int flag=0);
    int getNumLevels() const;
    void removeLevel(int idx);
    void clear();
    const MarketDataQuote& getQuote(int idx) const;

private:

    quotes_t _quotes;
};

class MarketData
{
public:
    enum SIDE {
        BID = 0,
        ASK,
        TRADE,
        MAX
    };

    MarketData(const std::string& symbol="N/A")
    :   _symbol(symbol)
    {
    }

    void addQuote(SIDE side, const MarketDataQuote& quote);
    void addQuote(SIDE side, double price, int size, int num=1, int flag=0);
    void clearQuotes();
    void clearQuotes(SIDE side);
    void pretty(bool printFlag=false) const;
    bool serialize(char* buf);

protected:
    void prettyHelp(const MarketDataQuote* quote, bool printFlag) const;

private:
    std::string _symbol;
    MarketDataSide _marketDatas[MAX];
};

} // close namespace gdm
#endif
