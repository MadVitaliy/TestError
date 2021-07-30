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
        if(Stream.eof( ))
            throw ENFEx();
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
    catch (const FileNotOpenedEx& ex)
    {
        std::cout << ex.what() << "\n";
    }
    catch (const ENFEx& ex)
    {
        std::cout << ex.what() <<"\n";
    }
    catch (...)
    {
        std::cout << "Another exep\n";
    }
    std::cout << "Sum is: " << sum << std::endl;
}