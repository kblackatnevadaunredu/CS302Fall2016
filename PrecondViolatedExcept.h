//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** Listing 7-5.
    @file PrecondViolatedExcept.h */
#include <exception>
#include <cstring>
#include <iostream>

using namespace std;

#ifndef PRECOND_VIOLATED_EXCEPT_
#define PRECOND_VIOLATED_EXCEPT_



class PrecondViolatedExcept
{
public:
   PrecondViolatedExcept(const std::string& message = "");
}; // end PrecondViolatedExcept
#endif
