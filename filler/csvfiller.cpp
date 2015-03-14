#include "csvfiller.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h> // atof


namespace gdm
{

CSVFiller::CSVFiller(const std::string& fileName)
    :   _fileName(fileName)
{
}

bool CSVFiller::fill(OHLCData& md)
{
    if(_fileName.empty()) {
        return false;
    }

    std::ifstream inStream(_fileName);
    if(inStream == false) {
        std::cerr << "failed to open file:" << _fileName << " for read"
            << std::endl;
        return false;
    }

    std::cout << "parsing csvfile:" << _fileName << std::endl;

    std::string line;
    std::vector<std::string> toks;

    // skip first line
    std::getline(inStream, line);

    while(std::getline(inStream, line)) {
        toks.clear();
        tokenize(line, ',', toks);

        if(toks.size() != 7) {
            std::cerr << "not expected token count:" << toks.size()
                << " line:" << line << std::endl;
            continue;
        }

        std::string date = toks[0];
        double dblOpen = atof(toks[1].c_str());
        double high = atof(toks[2].c_str());
        double low = atof(toks[3].c_str());
        double close = atof(toks[4].c_str());
        int64_t volume = atoll(toks[5].c_str());
        double adjClose = atof(toks[6].c_str());

        gdm::OHLC d(date, dblOpen, high, low, close, adjClose, volume);
        md.addData(d);
    }

    return true;
}

std::vector<std::string>& CSVFiller::tokenize(const std::string& line, char delim, std::vector<std::string>& toks)
{
    std::stringstream ss(line);
    std::string item;
    while(std::getline(ss, item, delim)) {
        toks.push_back(item);
    }
    return toks;
}


} // close namespace gdm
