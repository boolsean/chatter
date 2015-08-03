#include "json.h"

#include <iostream>
#include <string>


int main(int argc, char** argv) {

    std::cout << "testJSON.cpp" << std::endl;

    Json::Value root;

    {
        Json::Value subtree;
        subtree["name"] = "MS";
        subtree["high"] = 1.023;
        subtree["low"] = 1.012;

        root[0] = subtree;
    }

    {
        Json::Value subtree;
        subtree["name"] = "GS";
        subtree["high"] = 10.02;
        subtree["low"] = 10.01;

        root[1] = subtree;
    }


    std::cout << root << std::endl;

    for(Json::ValueIterator it = root.begin(); it != root.end(); it++) {
        std::cout << *it << std::endl;
    }

/*    Json::Value copy(root.asString());*/
/**/
/*    std::cout << copy << std::endl;*/

    Json::FastWriter writer;
    std::cout << writer.write(root) << std::endl;

    std::string out = writer.write(root);

/*    Json::Value copy(writer.write(root));*/
/**/
/*    std::cout << copy << std::endl;*/

    Json::Value copy;
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    std::string errs;
    bool ret = reader->parse(out.c_str(), out.c_str()+out.size(), &copy, &errs);

    std::cout << "ret:" << ret << " errs:" << errs << std::endl;
    std::cout << copy << std::endl;


    return 0;
}


