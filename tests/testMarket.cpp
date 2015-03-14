#include "marketdata.h"
#include "ohlcdata.h"
#include "stubplayer.h"
#include <iostream>

int main()
{
    gdm::MarketDataQuote q(100000.12345, 12999, 232);
    q.pretty();
    q.set(100.8, 1);
    q.pretty();

    std::cout << "*******************" << std::endl;

    gdm::MarketData d("SPY");
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
    d.pretty(true);

    d.clearQuotes();
    std::cout << "*******************" << std::endl;

    d.pretty();


    gdm::OHLCData hist("AXP");
    gdm::OHLC daily2("2015/01/23", 120, 130.434, 99.02, 98, 98, 1000300);
    gdm::OHLC daily("2015/01/22", 120, 130.434, 99.02, 98, 98, 1000219);
    hist.addData(daily2);
    hist.addData(daily);
    hist.pretty();


    std::cout << "*****************************************" << std::endl;
    const gdm::OHLCData::date2ohlc_t& dm = hist.getDataMap();
    for(gdm::OHLCData::date2ohlc_cit_t it = dm.begin(); it != dm.end(); it++) {
        it->second.pretty();
    }

    return 0;
}
