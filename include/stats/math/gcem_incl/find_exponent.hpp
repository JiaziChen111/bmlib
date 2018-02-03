/*################################################################################
  ##
  ##   Copyright (C) 2016-2018 Keith O'Hara
  ##
  ##   This file is part of the GCE-Math C++ library.
  ##
  ##   GCE-Math is free software: you can redistribute it and/or modify
  ##   it under the terms of the GNU General Public License as published by
  ##   the Free Software Foundation, either version 2 of the License, or
  ##   (at your option) any later version.
  ##
  ##   GCE-Math is distributed in the hope that it will be useful,
  ##   but WITHOUT ANY WARRANTY; without even the implied warranty of
  ##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  ##   GNU General Public License for more details.
  ##
  ################################################################################*/

/*
 * compile-time find_exponent function
 */

#ifndef _gcem_find_exponent_HPP
#define _gcem_find_exponent_HPP

template<typename T>
constexpr
int
find_exponent(const T x, const int exponent)
{
    return ( x < T(1.0) ? find_exponent(x*10,exponent-1) : ( x > T(10.0) ? find_exponent(x*0.1,exponent+1) : exponent ) );
}

#endif
