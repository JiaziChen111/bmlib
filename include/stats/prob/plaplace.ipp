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
 * cdf of the univariate Laplace distribution
 */

//
// single input

template<typename T>
statslib_constexpr
T
plaplace_int(const T x, const T mu_par, const T sigma_par)
{
    return ( 0.5 + 0.5*gcem::sgn(x - mu_par)*(1.0 - stats_math::exp(-stats_math::abs(x - mu_par) / sigma_par)) );
}

template<typename T>
statslib_constexpr
T
plaplace(const T x, const T mu_par, const T sigma_par, const bool log_form)
{
    return ( log_form == true ? stats_math::log(plaplace_int(x,mu_par,sigma_par)) : plaplace_int(x,mu_par,sigma_par) );
}

statslib_constexpr
double
plaplace(const double x)
{
    return plaplace(x,0.0,1.0,false);
}

statslib_constexpr
double
plaplace(const double x, const bool log_form)
{
    return plaplace(x,0.0,1.0,log_form);
}

statslib_constexpr
double
plaplace(const double x, const double mu_par, const double sigma_par)
{
    return plaplace(x,mu_par,sigma_par,false);
}

//
// matrix/vector input

#ifndef STATS_NO_ARMA

inline
arma::mat
plaplace_int(const arma::mat& x, const double* mu_par_inp, const double* sigma_par_inp, const bool log_form)
{
    const double mu_par = (mu_par_inp) ? *mu_par_inp : 0.0;
    const double sigma_par = (sigma_par_inp) ? *sigma_par_inp : 1.0;
    
    const uint_t n = x.n_rows;
    const uint_t k = x.n_cols;

    //

    arma::mat ret(n,k);

    const double* inp_mem = x.memptr();
    double* ret_mem = ret.memptr();

#ifndef STATS_NO_OMP
    #pragma omp parallel for
#endif
    for (uint_t j=0; j < n*k; j++)
    {
        ret_mem[j] = plaplace(inp_mem[j],mu_par,sigma_par,log_form);
    }

    //
    
    return ret;
}

inline
arma::mat
plaplace(const arma::mat& x)
{
    return plaplace_int(x,nullptr,nullptr,false);
}

inline
arma::mat
plaplace(const arma::mat& x, const bool log_form)
{
    return plaplace_int(x,nullptr,nullptr,log_form);
}

inline
arma::mat
plaplace(const arma::mat& x, const double mu_par, const double sigma_par)
{
    return plaplace_int(x,&mu_par,&sigma_par,false);
}

inline
arma::mat
plaplace(const arma::mat& x, const double mu_par, const double sigma_par, const bool log_form)
{
    return plaplace_int(x,&mu_par,&sigma_par,log_form);
}

#endif
