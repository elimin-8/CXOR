#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <string>
#include <vector>
#include <time.h>

namespace po = boost::program_options;

std::string randomkey()
{
    std::string sAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    srand(time(NULL)); // init srand with seed as current system clock time
    std::string sKey;
    for (int i = 0; i != 10; i++)
    {
        int iRandomIndex = rand() % 51 +1; // generate a number between 1 and 26
        sKey.insert(sKey.length(), 1, sAlphabet[iRandomIndex]);
    }
    return sKey;
}

std::vector<std::string> parseargs(int argc, char* argv[])
{
    std::string sIFile;
    std::string bInputHex = "false";
    std::string sOFile;
    std::string bOutputHex = "false";
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
        bool bInputHex = "true";
    }

    if (vm.count("of"))
    {
        sOFile = vm["of"].as<std::string>();
        sOFile = sOFile.substr(1, sOFile.length());
    }

    if (vm.count("oh"))
    {
        bool bOutputHex = "true";
    }

    if (vm.count("k"))
    {
        sKey = vm["k"].as<std::string>();
    }
    else
    {
        std::string sKey = randomkey();
        std::cout << "No key provided, using generated key " << sKey << std::endl;
    }

    std::vector<std::string> sParsedArgs {sIFile, bInputHex, sOFile, bOutputHex, sKey}; // init vector with parsed args
    return sParsedArgs;
}

void encryptio(std::vector<std::string> sParsedArgs)
{
    std::string sMessage;

    if (sParsedArgs[0] == "") // if no file path was provided
    {
        std::cout << "No file path provided, please input message:";
        std::cin >> sMessage;
    }
    else // if a file path was provided
    {
        // TODO WRITE HEX CASE TO CONVERT HEX BACK TO ORIGINAL FORM!!!!!!
        std::ifstream IFile;
        IFile.open(sParsedArgs[0]); // open file
        IFile >> sMessage;
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
    std::vector<std::string> sParsedArgs = parseargs(argc, argv);
    encryptio(sParsedArgs);
    xormessage("hello  ", "key");


}