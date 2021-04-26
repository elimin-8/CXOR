#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

void parseargs(int argc, char* argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "Print this message")
        ("input,i", "Specify an input file")
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
        std::cout << "input works";
    }

    /*if (vm.count(""))
    {
        
    }

    if (vm.count(""))
    {
        
    }

    if (vm.count(""))
    {
        
    }*/
}

int main(int argc, char* argv[])
{
    parseargs(argc, argv);

    /*std::fstream fInput;
    fInput.open(argv[1], std::ios::in);
    if (!fInput)
    {
        std::cout << "File does not exist.";
    }
    else
    {
        char ch;
        while (!fInput.eof())
        {
            fInput >> ch;
            std::cout << ch;
        }
        std::cout << std::endl;
        fInput.close();
    }
    return 0;*/
}