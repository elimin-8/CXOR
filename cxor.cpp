#include <iostream> // used for cin and cout
#include <fstream> // used to read files
#include <boost/program_options.hpp> // used for argument processing
#include <string> // used for strings
#include <vector> // use for vectors
#include <time.h> // used to get system time
#include <iomanip> // used for setw and setfill

namespace po = boost::program_options; // use po as shorthand for boost::program_options namespace

std::string randomkey() // function which uses system time to randomly pick 10 characters from the uppercase and lowercase alphabet
{
    std::string sAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // declare string containing alphabet
    srand(time(NULL)); // init srand with seed as current system clock time
    std::string sKey; // declare xor key
    for (int i = 0; i < 11; i++) // loop 10 times
    {
        int iRandomIndex = rand() % 51 +1; // generate a number between 1 and 51
        sKey += sAlphabet[iRandomIndex]; // use this number to pick a random letter and add it to the sKey string
    }
    return sKey; // return xor key
}

std::vector<std::string> parseargs(int argc, char* argv[]) // function which uses boost to parse program arguments
{
    std::string sIFile; // declare input file
    std::string sInputHex = "false"; // declare str serving purpose of bool
    std::string sOFile; // declare output file
    std::string sOutputHex = "false"; // declare str serving purpose of bool
    std::string sKey; // declare xor key

    po::options_description desc("Allowed options");
    desc.add_options() // define options
        ("help", "Print this message")
        ("if", po::value<std::string>(), "Specify an input file")
        ("ix", "Input data is in hex")
        ("of", po::value<std::string>(), "Specify an output file")
        ("ox", "Output data in hex")
        ("k",  po::value<std::string>(), "Specify a key")
    ;

    po::variables_map vm; // create map to insert options into
    po::store(po::parse_command_line(argc, argv, desc), vm); // parse options
    po::notify(vm); // handler for invalid options

    if (vm.count("help")) // if --help was used
    {
        std::cout << desc << std::endl; // print all the options
    }

    if (vm.count("if")) // if --if was used
    {
        sIFile = vm["if"].as<std::string>(); // copy the value into sIFile
    }

    if (vm.count("ix")) // if --ix was used
    {
        sInputHex = "true";
    }

    if (vm.count("of")) // if --of was used
    {
        sOFile = vm["of"].as<std::string>(); // copy the value into OFile
    }

    if (vm.count("ox")) // if --ox was used
    {
        sOutputHex = "true";
    }

    if (vm.count("k")) // if --k was used
    {
        sKey = vm["k"].as<std::string>(); // copy the value into sKey
    }
    else
    {
        sKey = randomkey(); // use the return from the randomkey function as the xor key
        std::cout << "No key provided, using generated key " << sKey << std::endl;
    }

    std::vector<std::string> sParsedArgs {sIFile, sInputHex, sOFile, sOutputHex, sKey}; // init vector with parsed args
    return sParsedArgs;
}

std::string hexify(std::string sMessage, bool bHexToStr) // define hexify, which takes sMessage and converts it to hex or str depending on the value
                                                         // of bHexToStr
{
    std::string sReturn; // define sReturn which is used to return the converted string
    if (bHexToStr) // convert hex to str
    {
        for (int i = 0; i < sMessage.length(); i += 2) // iterate through 2 chars at a time up until the end of the string is reached
        {
            std::string sSlice = sMessage.substr(i, 2); // slice the string to length of two
            char cMessageChar = std::stoul(sSlice, nullptr, 16); // convert hex to base 16?
            sReturn += cMessageChar; // add converted ascii char to sReturn string
        }
    }
    else // convert str to hex
    {
        std::stringstream ss;
        for (const auto &item : sMessage) // define auto which iterates through sMessage
        {
            ss << std::hex << std::setw(2) << std::setfill('0') << int(item); // convert char from string to its int counterpart, re add leading zeros 
                                                                              // and then convert it to hex
        }
        sReturn = ss.str(); // get string value from stringstream and assign it to sReturn
    }
    return sReturn;
}

std::string xormessage(std::string sMessage, std::string sKey) // define xormessage, which takes sMessage and *crypts it with sKey
{
    std::string sXORMessage; // define sXORMessage which is a string used to contain the *crypted message
    int iKeyIndex = 0; // define iKeyIndex which is used to iterate through sKey's chars

    for (int i = 0; i < sMessage.length(); i++) // iterate through sMessage
    {
        sXORMessage += sMessage[i] ^ sKey[iKeyIndex]; // perfrom the xor operation on a char in sMessage using a char in sKey
        iKeyIndex++;
        if (iKeyIndex == sKey.length()) // if iKeyIndex has reached the length of sKey
        {
            iKeyIndex = 0; // then reset iKeyIndex to zero
        }
    }

    return sXORMessage;
}

void cryptio(std::vector<std::string> sParsedArgs) // function handles io for *cryption
{
    std::string sMessage;

    if (sParsedArgs[0] == "") // if no input file path was provided
    {
        std::cout << "No file path provided, please input message:" << std::endl;
        std::cin >> sMessage;
        if (sParsedArgs[1] == "true") // if the inputted text is hex
        {
            sMessage = hexify(sMessage, true); // convert the message from hex to str
        }
    }
    else // if an input file path was provided
    {
        std::ifstream IFile; // define ifstream file handler
        char cMessage; // define char for usage in file reading
        IFile.open(sParsedArgs[0]); // open file
        while (IFile.get(cMessage)) // read file byte by byte
        {
            sMessage += cMessage; // add current byte to sMessage
        }
        IFile.close(); // close file

        if (sParsedArgs[1] == "true") // if the input file is hex
        {
            sMessage = hexify(sMessage, true); // dehexify the file
        }
    }

    std::string sXORMessage = xormessage(sMessage, sParsedArgs[4]); // *crypt the message using the key provided

    if (sParsedArgs[2] == "") // if no output file path was provided
    {
        std::cout << "No file path provided, outputting to stdout in hex" << std::endl;
        std::cout << hexify(sXORMessage, false) << std::endl; // outputs *crypted message to stdout
    }
    else // if an output file path was provided
    {
        std::ofstream OFile; // define ofstream file handler
        OFile.open(sParsedArgs[2]); // open file
        if (sParsedArgs[3] == "true") // if the output should be in hex
        {
            sXORMessage = hexify(sXORMessage, false); // convert message to hex
            OFile << sXORMessage; // write *crypted message in hex to file
            OFile.close(); // close file
        }
        else // if the output should not be in hex
        {
            OFile << sXORMessage; // write *crypted message to file
            OFile.close(); // close file
        }
        std::cout << "*crypted output has been written to " << sParsedArgs[2] << std::endl;
    }
}

int main(int argc, char* argv[])
{
    std::vector<std::string> sParsedArgs = parseargs(argc, argv);
    cryptio(sParsedArgs); // call cryptio with the parsed arguments
}