#include "csvfiller.h"
#include "ohlcdata.h"
#include <iostream>

int main(int argc, char** argv) {

    std::cout << argv[0] << " invoked" << std::endl;

    if(argc <= 1)
    {
        std::cerr << "no enough inputs" << std::endl;
        return 0;
    }

    std::string fileName(argv[1]);
    std::cout << "filename:" << fileName << std::endl;

    gdm::CSVFiller filler(fileName);

    gdm::OHLCData md("SPY");
    filler.fill(md);

    for(gdm::OHLCData::date2ohlc_cit_t it = md.getDataMap().begin(); it != md.getDataMap().end(); it++) {
        it->second.pretty();
    }


    return 0;
}
