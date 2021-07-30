#include <iostream>
#include <fstream>
#include <string>
#include <exception>

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

class ENFEx : public std::exception
{
public:
    ENFEx()
    {};
    ~ENFEx()
    {};

    const char* what() const override
    {
        return "End Of File";
    }
};

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
        throw FileNotOpenedEx();
}

int NumberLinesReader::ReadNextNumber()
{
    int temp;
    try
    {
        //if(eof)
        //    throw ENFEx();
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
    catch (const FileNotOpenedEx& str)
    {
        std::cout << "Cannot open file\n";
    }
    catch (const ENFEx& str)
    {
        std::cout << "File read\n";
    }
    catch (...)
    {
        std::cout << "Another exep\n";
    }
    std::cout << "Sum is: " << sum << std::endl;
}