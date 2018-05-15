#include <iostream>
#include <vector>
#include <cstdlib>
const int BASE = 10;
class LongInt
{
    public:
    LongInt(const std::string& number);
    ~LongInt(){}
    LongInt operator +( const LongInt& other);
    LongInt operator -(const LongInt& other);
    LongInt operator <(const LongInt& other);
    private:
    std::vector<uint32_t> m_data;
    size_t size;
};
//std::stoi(std::string)
std::ostream& operator<<(std::ostream &stream, LongInt& number)
{
    if(number->m_data.empty())
    {
        return stream;
    }
    stream<<number.m_data.back();
    auto n = ...;
    for(size_t i = 2; i < number.m_data.size());
    {
        stream<<std::set
    }
}
LongInt::LongInt(const std::string& number)
{
    for(auto it = number.rbegin(); it != number.rend(); ++it)
    {
        char c = *it;
        m_data.push_back(static_cast<uint32_t> c);
    }
}
LongInt::operator+(const LongInt& other)
{
    int maxSize = std::max(this->m_data.size(), other.m_data.size());
    bool inNextRow(false);
    for(std::size_t i = 0; i < maxSize; ++i)
    {
        int row = 
    }

}
LongInt operator <(const LongInt& other)
{
    if(other.m_data.size() > m_data.size())
        return true;
    else if(other.m_data.size() < m_data.size())
        return false;
    
}
LongInt::operator-(const LongInt& other)
{
    int maxSize = std::max(this->m_data.size(), other.m_data.size());
    LongInt res;
    for(size_t i = 0; i < maxSize; ++i)
    {
        int row = 0;
        if(m_data.size >= i)
        {
            row += other.m_data[i] - 
        }
    }
    
}
int main()
{
    std::string number1, number2;
    char operation;
    while(std::cin>>number1>>number2>>operatiob)
    {
        LongInt long_number(number1);
        LongInt long_number(number2);
        switch(operation)
        {
            case '+':
            {
                LongInt result = long_number1 + long_number2;
                std::cout<<result<<std::endl;
                break;
            }
            case '-':
            {

            }
            case '<':
            {
                bool result = long_number1 < long_number2;
            }

        }
    }
}