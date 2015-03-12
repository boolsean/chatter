#include "marketdata.h"
#include <iostream>

int main()
{
    gdm::MarketDataQuote q(100000.12345, 12999, 232);
    q.pretty();
    q.set(100.8, 1);
    q.pretty();

    std::cout << "*******************" << std::endl;

    gdm::MarketData d;
    d.addQuote(gdm::MarketData::BID, 100, 200);
    d.addQuote(gdm::MarketData::BID, 99.98, 500);
    d.addQuote(gdm::MarketData::ASK, 100.10, 100);
    d.addQuote(gdm::MarketData::ASK, 100.12, 2000);
    d.addQuote(gdm::MarketData::ASK, 100.20, 3500);
    d.addQuote(gdm::MarketData::TRADE, q);
    d.addQuote(gdm::MarketData::TRADE, q);
    d.addQuote(gdm::MarketData::TRADE, q);
    d.addQuote(gdm::MarketData::TRADE, q);

    d.pretty(false);

    d.clearQuotes();
    std::cout << "*******************" << std::endl;

    d.pretty();
    return 0;
}
