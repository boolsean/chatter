
#include <string>
#include <map>
#include <boost/date_time/gregorian/gregorian.hpp>
namespace gdm
{

class OHLC
{
public:
    OHLC()
        :   _date(), _open(.0), _high(.0), _low(.0), _close(.0), _adjClose(.0), _volume(0)
    {
    }

    OHLC(const std::string& date, double open, double high,
            double low, double close, double adjClose, int64_t volume)
        :   _date(boost::gregorian::from_string(date)), _open(open), _high(high),
            _low(low), _close(close), _adjClose(adjClose), _volume(volume)
    {
    }

    void pretty() const;

    const boost::gregorian::date& getDate() const   { return _date; }
    double getOpen()                        const   { return _open; }
    double getHigh()                        const   { return _high; }
    double getLow()                         const   { return _low; }
    double getClose()                       const   { return _close; }
    double getAdjClose()                    const   { return _adjClose; }
    int64_t getVolume()                     const   { return _volume; }

protected:

private:
    boost::gregorian::date _date;
    double _open;
    double _high;
    double _low;
    double _close;
    double _adjClose;
    int64_t _volume;

};

class OHLCData
{
public:
    typedef std::vector<OHLC> ohlclist_t;
    typedef ohlclist_t::iterator ohlclist_it_t;
    typedef ohlclist_t::const_iterator ohlclist_cit_t;

    typedef std::map<boost::gregorian::date, OHLC> date2ohlc_t;
    typedef date2ohlc_t::iterator date2ohlc_it_t;
    typedef date2ohlc_t::const_iterator date2ohlc_cit_t;


    OHLCData(const std::string& symbol)
        :   _symbol(symbol), _dataList()
    {
    }

    void addData(const OHLC& data);
    void pretty() const;

    const date2ohlc_t& getDataMap() const;

protected:
private:
    std::string     _symbol;
    ohlclist_t      _dataList;
    date2ohlc_t     _dataMap;
};

} // close namespace gdm
