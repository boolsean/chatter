#include "market.h"
#include <iostream>
#include <string>
#include <sstream>

MarketLevel::MarketLevel() {
}

void MarketLevel::clear() {
    prices.clear();
    sizes.clear();
}

void MarketLevel::addLevel(double price, int size) {
    prices.push_back(price);
    sizes.push_back(size);
}

int MarketLevel::getNumLevels() {
    return prices.size();
}

double MarketLevel::getPrice(int i) {
    return prices[i];
}

int MarketLevel::getSize(int i) {
    return sizes[i];
}

void MarketLevel::pretty() {
}

void Market::pretty() {
    std::ostringstream oss;

    bool done = true;
    int bidIdx = 0;
    int askIdx = 0;
    int tradeIdx = 0;

    MarketLevel& bids = _marketLevels[BID];
    MarketLevel& asks = _marketLevels[ASK];
    MarketLevel& trades = _marketLevels[TRADE];
    for(;;) {
        if(bidIdx < bids.getNumLevels()) {
            oss << bids.getPrice(bidIdx) << "@" << bids.getSize(bidIdx);
            ++bidIdx;
            done = true;
        }
        oss << "     ";

        if(askIdx < asks.getNumLevels()) {
            oss << asks.getPrice(askIdx) << "@" << asks.getSize(askIdx);
            ++askIdx;
            done = true;
        }
        oss << "     ";

        if(tradeIdx < trades.getNumLevels()) {
            oss << trades.getPrice(tradeIdx) << "@" << trades.getSize(tradeIdx);
            ++tradeIdx;
            done = true;
        }

        oss << std::endl;

        if(done == false)
            break;
        done = false;
    }
}




