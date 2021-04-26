#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <string>
#include <vector>

namespace po = boost::program_options;

void parseargs(int argc, char* argv[])
{
    bool bInputHex = false;
    bool bOutputHex = false;
    std::string sInputFile;
    std::string sOutputFile;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "Print this message")
        ("input,i", po::value<std::string>(), "Specify an input file")
        ("ih", "Input data is in hex")
        ("output,o", "Specify an output file")
        ("oh", "Output data in hex")
    ;

    po::positional_options_description p;
    p.add("input", -1);

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
    }

    if (vm.count("input"))
    {
        std::string file = vm["input"].as<std::string>();
        std::string filecut = file.substr(1, file.length());
        std::cout << filecut;
    }

    if (vm.count("ih"))
    {
        bool bInputHex = true;
    }

    if (vm.count("output"))
    {
        std::string file = vm["output"].as<std::string>();
        std::string filecut = file.substr(1, file.length());
        std::cout << filecut;
    }

    if (vm.count("oh"))
    {
        bool bOutputHex = true;
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