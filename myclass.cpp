#include "myclass.h"

std::ostream& operator<<(std::ostream& os, const MyClass& obj)
{
    os << obj.m_pair.first;
    return os;
}

MyClass::MyClass(std::string str, InternalArray arr)
{
    m_pair = std::make_pair(str, arr);
}

const MyClass::InternalArray &MyClass::getArr() const
{
    return m_pair.second;
}

bool operator<(const MyClass& lhs, const MyClass& rhs)
{
    return lhs.m_pair.first < rhs.m_pair.first;
}

bool operator>(const MyClass& lhs, const MyClass& rhs)
{
    return lhs.m_pair.first > rhs.m_pair.first;
}
