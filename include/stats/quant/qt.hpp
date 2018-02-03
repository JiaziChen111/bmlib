/*################################################################################
  ##
  ##   Copyright (C) 2011-2018 Keith O'Hara
  ##
  ##   This file is part of the StatsLib C++ library.
  ##
  ##   StatsLib is free software: you can redistribute it and/or modify
  ##   it under the terms of the GNU General Public License as published by
  ##   the Free Software Foundation, either version 2 of the License, or
  ##   (at your option) any later version.
  ##
  ##   StatsLib is distributed in the hope that it will be useful,
  ##   but WITHOUT ANY WARRANTY; without even the implied warranty of
  ##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  ##   GNU General Public License for more details.
  ##
  ################################################################################*/

/*
 * quantile function of the t distribution
 */

#ifndef _statslib_qt_HPP
#define _statslib_qt_HPP

// single input
template<typename T>
statslib_constexpr T qt(const T p, const int dof_par, const bool log_form);

statslib_constexpr double qt(const double p);
statslib_constexpr double qt(const double p, const bool log_form);
statslib_constexpr double qt(const double p, const int dof_par);

// matrix/vector input
#ifndef STATS_NO_ARMA
arma::mat qt_int(const arma::mat& p, const int* dof_par_inp, const bool log_form);

arma::mat qt(const arma::mat& p);
arma::mat qt(const arma::mat& p, const bool log_form);
arma::mat qt(const arma::mat& p, const int dof_par);
arma::mat qt(const arma::mat& p, const int dof_par, const bool log_form);
#endif

#include "qt.ipp"

#endif
