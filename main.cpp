#include <iostream>
#include <iterator>
#include <algorithm>
#include <set>
#include <range/v3/all.hpp>
#include "myclass.h"

#define RANGE

void ipParser(std::set<MyClass, std::greater<MyClass>> &ipSet, std::string &ipStr)
{
    std::array<int, 4> tmpArr;

    int octetCounter = 0;
    std::string tmpStr;
    auto itb = ipStr.begin();
    while (itb != ipStr.end()) {
        if(isdigit(*itb))
        {
            tmpStr.push_back(*itb);
        } else if(*itb == '.') {
            if(!tmpStr.empty())
            {
                int ipNumber = std::stoi(tmpStr);
                if(ipNumber >= 0 && ipNumber < 256)
                {
                    if(octetCounter < 3)
                    {
                        tmpArr[octetCounter] = ipNumber;
                        tmpStr.clear();
                        ++octetCounter;
                    } else {
                        std::cout << "Invalid IP String";
                        break;
                    }
                } else {
                    std::cout << "Invalid IP String";
                    break;
                }
            } else {
                std::cout << "Invalid IP String";
                break;
            }

        } else {
            std::cout << "Invalid IP String";
            break;
        }
        ++itb;
    }

    if(octetCounter == 3)
    {
        int ipNumber = std::stoi(tmpStr);
        if(ipNumber >= 0 && ipNumber < 256)
        {
            tmpArr[octetCounter] = ipNumber;
        }
    }

    ipSet.insert(MyClass(ipStr, tmpArr));
}

int main()
{
    std::set<MyClass, std::greater<MyClass>> s;
    std::string str;
    std::cout << "Enter ip-v4 string: ";
    while(std::cin >> str)
    {
        ipParser(s, str);
        std::cout << "Enter ip-v4 string: ";
    }

    std::cout << "\nAll Ips In Descending Order: \n";
    #ifdef RANGE
        ranges::for_each(s, [](auto &obj){std::cout << obj << '\n';});
    #else
        std::copy(s.begin(), s.end(), std::ostream_iterator<MyClass>(std::cout, "\n"));
    #endif

    std::cout << "Filter 1: \n";
    int firstFilter = 1;

    #ifdef RANGE
        ranges::for_each(s | ranges::view::filter([firstFilter](auto &obj){return obj.getArr().at(0) == firstFilter;}), 
                                        [](auto &obj){std::cout << obj << '\n';});
    #else
        std::copy_if(s.begin(), s.end(), std::ostream_iterator<MyClass>(std::cout, "\n"), [firstFilter](MyClass lhs){
            return lhs.getArr().at(0) == firstFilter;
        });
    #endif

    std::cout << "Filter 2: \n";
    int secondFilter1 = 46;
    int secondFilter2 = 70;

    #ifdef RANGE
        ranges::for_each(s | ranges::view::filter([secondFilter1, secondFilter2](auto& obj)
            {return obj.getArr().at(0) == secondFilter1 && obj.getArr().at(1) == secondFilter2;}), 
            [](auto &obj){std::cout << obj << '\n';});
    #else
        std::copy_if(s.begin(), s.end(), std::ostream_iterator<MyClass>(std::cout, "\n"), [secondFilter1, secondFilter2](MyClass lhs){
            return lhs.getArr().at(0) == secondFilter1 && lhs.getArr().at(1) == secondFilter2;
        });
    #endif



    std::cout << "Filter 3: \n";
    int thirdFilter = 46;

    #ifdef RANGE
        ranges::for_each(s | ranges::view::filter([thirdFilter](auto& obj)
            { 
                return std::any_of(obj.getArr().begin(), obj.getArr().end(), [thirdFilter](auto num){
                    return num == thirdFilter;
                });
            }),
            [](auto &obj){std::cout << obj << '\n';});
    #else
        std::copy_if(s.begin(), s.end(), std::ostream_iterator<MyClass>(std::cout, "\n"), [thirdFilter](MyClass lhs){
            return std::any_of(lhs.getArr().begin(), lhs.getArr().end(), [thirdFilter](int num){return num == thirdFilter;});
        });
    #endif

    return 0;
}
