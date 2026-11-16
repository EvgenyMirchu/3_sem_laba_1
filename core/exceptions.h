#pragma once
#include <stdexcept>
#include <string>


class IndexOutOfRange: public std::out_of_range 
{
public:
    IndexOutOfRange(int index, int size): 
        std::out_of_range("index " + std::to_string(index) + " out of range [0, " + std::to_string(size) + ")") {}
};


class InvalidArgument: public std::invalid_argument 
{
public:
    explicit InvalidArgument(const std::string& message): std::invalid_argument(message) {}
};