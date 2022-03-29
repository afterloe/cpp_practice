#define _CRT_SECURE_NO_WARNING

#include <iostream>
#include "line.h"

Line::Line(int l)
{
    this->line = l;
    std::cout << "setLine success" << std::endl;
}

Line::~Line(void)
{
    this->line = 0;
    std::cout << "object del" << std::endl;
}

void Line::setLength(int l)
{
    this->line = l;
    std::cout << "new Line has been set." << std::endl;
}

int Line::getLength(void)
{
    return this->line;
}