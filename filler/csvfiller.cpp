#include "csvfiller.h"
#include <iostream>

namespace gdm
{

CSVFiller::CSVFiller(const std::string& fileName)
    :   _fileName(fileName)
{
    std::cout << "CSVFiller CTOR" << std::endl;
}

bool CSVFiller::fill(OHLCData& md)
{
    if(_fileName.empty()) {
        return false;
    }

    gdm::OHLC d2("2015/01/23", 120, 130.434, 99.02, 98, 98, 1000300);
    gdm::OHLC d("2015/01/22", 120, 130.434, 99.02, 98, 98, 1000219);

    md.addData(d);
    md.addData(d2);

    return true;
}


} // close namespace gdm
