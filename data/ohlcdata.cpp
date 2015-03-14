#include "ohlcdata.h"
#include <iostream>

namespace gdm
{

void OHLC::pretty() const
{
    std::cout << _date << " O:" << _open << " H:" << _high
        << " L:" << _low << " C:" << _close << " A:" << _adjClose << " V:"
        << _volume << std::endl;
}

void OHLCData::addData(const OHLC& data)
{
    _dataList.push_back(data);
    _dataMap[data.getDate()] = data;
}

void OHLCData::pretty() const
{
    std::cout << "pretty:" << _symbol << std::endl;
    for(ohlclist_cit_t it = _dataList.begin(); it != _dataList.end(); it++) {
        it->pretty();
    }

}

const OHLCData::date2ohlc_t& OHLCData::getDataMap() const
{
    return _dataMap;
}


} // close namespace gdm
