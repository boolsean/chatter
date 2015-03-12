#include "marketdata.h"

#include <iostream>
#include <iomanip>

namespace gdm {
void MarketDataQuote::pretty() const
{
    std::cout << std::setw(8) << _size << "@"
        << std::setw(12) << std::fixed << std::setprecision(5) << _price << " ["
        << std::setw(3) << _num << "] f="
        << std::setw(10) << _flag << std::endl;
}

void MarketDataQuote::set(double price, int size, int num, int flag)
{
    _price = price;
    _size = size;
    _num = num;
    _flag = flag;
}

double MarketDataQuote::getPrice() const
{
    return _price;
}

int MarketDataQuote::getSize() const
{
    return _size;
}

int MarketDataQuote::getNum() const
{
    return _num;
}

int MarketDataQuote::getFlag() const
{
    return _flag;
}

// *********************************************************************************
// *********************************************************************************
// *********************************************************************************

MarketDataSide::MarketDataSide()
    :   _quotes()
{
}

void MarketDataSide::pretty() const
{
}

void MarketDataSide::addQuote(const MarketDataQuote& quote)
{
    _quotes.push_back(quote);
}

void MarketDataSide::addQuote(double price, int size, int num, int flag)
{
    MarketDataQuote quote(price, size, num, flag);
    _quotes.push_back(quote);
}

int MarketDataSide::getNumLevels() const
{
    return _quotes.size();
}

void MarketDataSide::removeLevel(int lvl)
{
    if(_quotes.size() < lvl)
        _quotes.erase(_quotes.begin()+lvl-1);
}

void MarketDataSide::clear()
{
    _quotes.clear();
}

const MarketDataQuote& MarketDataSide::getQuote(int lvl) const
{
    return _quotes[lvl];
}

// *********************************************************************************
// *********************************************************************************
// *********************************************************************************

void MarketData::addQuote(MarketData::SIDE side, const MarketDataQuote& quote)
{
    switch(side) {
        case BID:
        case ASK:
        case TRADE:
            _marketDatas[side].addQuote(quote);
            break;
        default:
            break;
    }
}

void MarketData::addQuote(MarketData::SIDE side, double price, int size, int num, int flag)
{
    switch(side) {
        case BID:
        case ASK:
        case TRADE:
            _marketDatas[side].addQuote(price, size, num, flag);
            break;
        default:
            break;
    }
}

void MarketData::clearQuotes()
{
    _marketDatas[BID].clear();
    _marketDatas[ASK].clear();
    _marketDatas[TRADE].clear();
}

void MarketData::clearQuotes(MarketData::SIDE side)
{
    _marketDatas[side].clear();
}

void MarketData::prettyHelp(const MarketDataQuote* quote, bool printFlag) const
{
    const static std::string space(40, ' ');
    const static std::string spaceNoFlag(27, ' ');
    if(quote != NULL) {
        std::cout << std::setw(8) << quote->getSize() << "@"
            << std::setw(12) << std::fixed << std::setprecision(5) << quote->getPrice() << " ["
            << std::setw(3) << quote->getNum() << "]";
        if(printFlag) {
            std::cout << " f=" << std::setw(10) << quote->getFlag();
        }
    }
    else {
        if(printFlag) {
            std::cout << space;
        }
        else {
            std::cout << spaceNoFlag;
        }
    }
}

void MarketData::pretty(bool printFlag) const
{
    bool more = true;
    int curIdx = 0;
    const MarketDataSide& bids = _marketDatas[BID];
    const MarketDataSide& asks = _marketDatas[ASK];
    const MarketDataSide& trades = _marketDatas[TRADE];

    std::cout << _symbol << "\n";
    while(more == true) {
        more = false;
        if(bids.getNumLevels() > curIdx) {
            more = true;
            const MarketDataQuote& quote = bids.getQuote(curIdx);
            prettyHelp(&quote, printFlag);
        }
        else {
            prettyHelp(NULL, printFlag);
        }

        if(asks.getNumLevels() > curIdx) {
            const MarketDataQuote& quote = asks.getQuote(curIdx);
            prettyHelp(&quote, printFlag);
            more = true;
        }
        else {
            prettyHelp(NULL, printFlag);
        }

        if(trades.getNumLevels() > curIdx) {
            const MarketDataQuote& quote = trades.getQuote(curIdx);
            prettyHelp(&quote, printFlag);
            more = true;
        }
        else {
            prettyHelp(NULL, printFlag);
        }

        std::cout << "\n";
        curIdx++;
    }
    std::cout << std::endl;
}

bool MarketData::serialize(char* buf)
{
}

}
