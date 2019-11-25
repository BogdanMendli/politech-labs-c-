#ifndef OUTPUTTASK_HPP
#define OUTPUTTASK_HPP
#include <list>
#include <iostream>
#include "element.hpp"

void formatText(std::ostream &out, unsigned int width, const std::list<element_t> &vector);
bool trueOrder (const std::list<element_t> &vector);

#endif
