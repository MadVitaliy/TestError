#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <optional>


class FileNotOpenedEx : public std::exception
{
public:
    FileNotOpenedEx()
    {};
    ~FileNotOpenedEx() 
    {};

    const char* what() const override 
    {
        return "File not opened";
    }
};

class NumberLinesReader
{
public:
    NumberLinesReader(const std::string& fileName);
    std::optional<int> ReadNextNumber();
private:
    std::ifstream Stream;
};

NumberLinesReader::NumberLinesReader(const std::string& fileName) : Stream(fileName)
{
    if (!Stream.good())
        throw FileNotOpenedEx();
}

std::optional<int> NumberLinesReader::ReadNextNumber()
{
    std::optional<int> res;
    try
    {
        if (!Stream.is_open())
            throw FileNotOpenedEx();
        if(Stream.eof( ))
            return res; //return empty std::optional

        int temp;
        Stream >> temp;
        res = temp;
        return res;
    }
    catch (...)
    {
        throw;
    }
}

int main()
{
    int sum = 0;
    try
    { 
        NumberLinesReader reader(std::move(std::string("C:/Users/vomelchenko/source/repos/TestError/Text.txt")));

        std::optional<int> value = reader.ReadNextNumber();
        while (value) 
        {
            sum += value.value();
            value = reader.ReadNextNumber();
        }
    }
    catch (const FileNotOpenedEx& ex)
    {
        std::cout << ex.what() << "\n";
    }
    catch (...)
    {
        std::cout << "Another exep\n";
    }
    std::cout << "Sum is: " << sum << std::endl;
}