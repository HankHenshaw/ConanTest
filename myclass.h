#ifndef MYCLASS_H
#define MYCLASS_H

#include <array>
#include <string>

class MyClass {
    static constexpr int ARR_SIZE = 4;
    using InternalArray = std::array<int, ARR_SIZE>;
    using Pair = std::pair<std::string, InternalArray>;
    Pair m_pair;
public:
    MyClass(std::string str, InternalArray arr);
    friend bool operator<(const MyClass& lhs, const MyClass& rhs);
    friend bool operator>(const MyClass& lhs, const MyClass& rhs);
    friend std::ostream& operator<<(std::ostream& os, const MyClass& obj);
    const InternalArray& getArr() const;
};


#endif // MYCLASS_H
