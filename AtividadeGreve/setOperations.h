#pragma once 
#ifndef SETOPERATIONS_H 
#define SETOPERATIONS_H

#include "set.h"
#include "node.h"

Set Union(Set& s,Set& t);

Set Intersec(Set& s, Set& t);

Set Difference(Set& s, Set& t);

#endif