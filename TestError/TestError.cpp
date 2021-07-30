#include <iostream>
#include <fstream>
#include <string>


class NumberLinesReader
{
public:
    bool Open(const std::string& fileName);
    int ReadNextNumber();
private:
    std::ifstream Stream;
};

bool NumberLinesReader::Open(const std::string& fileName)
{
    Stream.open(fileName);
    if (!Stream.is_open())
        throw std::string("File not opened");
}

int NumberLinesReader::ReadNextNumber()
{
    int temp;
    try
    {
        //if(eof)
        //    throw std::string("EOF");
        Stream >> temp;

    }
    catch (...)
    {
        throw;
    }
    return temp;
}

int main()
{
    NumberLinesReader reader;
    int sum = 0;
    try
    { 
        reader.Open("numbers.txt");
      
        while (true)
            sum += reader.ReadNextNumber();
    }
    catch (const std::string& str)
    {
        if(str == "File not opened")
            std::cout << "Cannot open file\n";
        if (str == "EPF")
            std::cout << "File read\n";
    }
    catch (...)
    {
        std::cout << "Another exep\n";
    }
    std::cout << "Sum is: " << sum << std::endl;
}