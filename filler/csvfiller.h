#ifndef GDM_CSVFILLER
#define GDM_CSVFILLER

#include "ohlcdata.h"

namespace gdm
{

class CSVFiller
{
public:

    CSVFiller(const std::string& fileName);

    bool fill(OHLCData& md);

protected:


private:
    std::vector<std::string>& tokenize(const std::string& line, char delim, std::vector<std::string>& toks);

    std::string _fileName;
    bool _getOHLC;
};


} // close namespace gdm



#endif
