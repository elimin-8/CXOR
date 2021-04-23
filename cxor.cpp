#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    std::fstream fInput;
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
    return 0;
}