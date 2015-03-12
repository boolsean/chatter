#include "ohlcdata.h"
#include <iostream>

namespace gdm
{

void OHLCData::pretty() const {
    std::cout << _symbol << " " << _date << " O:" << _open << " H:" << _high
        << " L:" << _low << " C:" << _close << " A:" << _adjClose << " V:"
        << _volume << std::endl;
}
}
