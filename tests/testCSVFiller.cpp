#include "csvfiller.h"
#include "ohlcdata.h"
#include <iostream>

int main(int argc, char** argv) {

    std::cout << argv[0] << " invoked" << std::endl;

    gdm::CSVFiller filler("ssss.csv");

    gdm::OHLCData md("SPY");
    filler.fill(md);

    for(gdm::OHLCData::date2ohlc_cit_t it = md.getDataMap().begin(); it != md.getDataMap().end(); it++) {
        it->second.pretty();
    }


    return 0;
}
