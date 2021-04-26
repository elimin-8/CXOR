#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <string>
#include <vector>

namespace po = boost::program_options;

void parseargs(int argc, char* argv[])
{
    std::string sIFile;
    bool bInputHex = false;
    std::string sOFile;
    bool bOutputHex = false;
    std::string sKey;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "Print this message")
        ("if", po::value<std::string>(), "Specify an input file")
        ("ih", "Input data is in hex")
        ("of", po::value<std::string>(), "Specify an output file")
        ("oh", "Output data in hex")
        ("k",  po::value<std::string>(), "Specify a key")
    ;

    /*po::positional_options_description p;
    p.add("input", -1);*/

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
    }

    if (vm.count("if"))
    {
        sIFile = vm["if"].as<std::string>();
        sIFile = sIFile.substr(1, sIFile.length());
    }

    if (vm.count("ih"))
    {
        bool bInputHex = true;
    }

    if (vm.count("of"))
    {
        sOFile = vm["of"].as<std::string>();
        sOFile = sOFile.substr(1, sOFile.length());
    }

    if (vm.count("oh"))
    {
        bool bOutputHex = true;
    }

    if (vm.count("k"))
    {
        sKey = vm["k"].as<std::string>();
    }
    else
    {
        std::cout << "A key must be specified";
        exit(0);
    }

}

std::vector<char> xormessage(std::string sMessage, std::string sKey)
{
    std::vector<char> cXORMessage;
    int iKeyIndex = 0;

    for (int iMessageIndex = 0; iMessageIndex < sMessage.length(); iMessageIndex++)
    {
        cXORMessage.push_back(sMessage[iMessageIndex] ^ sKey[iKeyIndex]);
        iKeyIndex++;
        if (iKeyIndex == sKey.length())
        {
            iKeyIndex = 0;
        }
    }
    return cXORMessage;
}

int main(int argc, char* argv[])
{
    //parseargs(argc, argv);
    xormessage("hello  ", "key");


}