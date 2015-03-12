#ifndef MARKET_H
#define MARKET_H

#include <vector>
#include <string>

class MarketLevel {
public:
    MarketLevel();
    void clear();
    void addLevel(double price, int size);
    int getNumLevels();
    double getPrice(int i);
    int getSize(int i);
    void pretty();
    std::vector<double>& getPrices();
    std::vector<int>& getSizes();

private:
    std::vector<double> prices;
    std::vector<int> sizes;
};

class Market {
public:
    enum {
        BID=0,
        ASK,
        TRADE,
        MAX
    };
    Market(const char* symbol);
    ~Market();

    void pretty();

    int getNumBids();
    int getNumAsks();
    int getNumTrades();

    MarketLevel& getBids();
    MarketLevel& getAsks();
    MarketLevel& getTrades();

private:
    MarketLevel _marketLevels[MAX];
};

#endif
