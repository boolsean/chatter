
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
namespace gdm
{

class OHLCData
{
public:
    OHLCData(const std::string& symbol, const std::string& date, double open, double high,
            double low, double close, double adjClose, int64_t volume)
        :   _symbol(symbol), _date(boost::gregorian::from_string(date)), _open(open), _high(high),
            _low(low), _close(close), _adjClose(adjClose), _volume(volume)
    {
    }

    void pretty() const;


protected:


private:
    std::string _symbol;
    boost::gregorian::date _date;
    double _open;
    double _high;
    double _low;
    double _close;
    double _adjClose;
    int64_t _volume;

};
}
