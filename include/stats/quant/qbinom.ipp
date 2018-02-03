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
 * quantile function of the univariate Binomial distribution
 */

//
// single input

template<typename T>
statslib_constexpr
int
qbinom_int(const T p, const int n_trials, const T prob_par, const T value, const int count)
{
    return ( value < p ? qbinom_int(p,n_trials,prob_par, pbinom(count,n_trials,prob_par,false), count + 1) : count - 1 );
}

template<typename T>
statslib_constexpr
int
qbinom(const T p, const int n_trials, const T prob_par, const bool log_form)
{
    return ( log_form == true ? stats_math::log(qbinom_int(p,n_trials,prob_par,(T)0.0,0)) : qbinom_int(p,n_trials,prob_par,(T)0.0,0) );
}

statslib_constexpr
int
qbinom(const double p)
{
    return qbinom(p,1,0.5,false);
}

statslib_constexpr
int
qbinom(const double p, const bool log_form)
{
    return qbinom(p,1,0.5,log_form);
}

statslib_constexpr
int
qbinom(const double p, const int n_trials, const double prob_par)
{
    return qbinom(p,n_trials,prob_par,false);
}

//
// matrix/vector input

#ifndef STATS_NO_ARMA

inline
arma::mat
qbinom_int(const arma::mat& p, const int* n_trials_inp, const double* prob_par_inp, const bool log_form)
{
    const int n_trials = (n_trials_inp) ? *n_trials_inp : 1;
    const double prob_par = (prob_par_inp) ? *prob_par_inp : 0.5;

    const uint_t n = p.n_rows;
    const uint_t k = p.n_cols;

    //

    arma::mat ret(n,k);

    const double* inp_mem = p.memptr();
    double* ret_mem = ret.memptr();

#ifndef STATS_NO_OMP
    #pragma omp parallel for
#endif
    for (uint_t j=0; j < n*k; j++)
    {
        ret_mem[j] = qbinom(inp_mem[j],n_trials,prob_par,log_form);
    }

    //
    
    return ret;
}

inline
arma::mat
qbinom(const arma::mat& p)
{
    return qbinom_int(p,nullptr,nullptr,false);
}

inline
arma::mat
qbinom(const arma::mat& p, const bool log_form)
{
    return qbinom_int(p,nullptr,nullptr,log_form);
}

inline
arma::mat
qbinom(const arma::mat& p, const int n_trials, const double prob_par)
{
    return qbinom_int(p,&n_trials,&prob_par,false);
}

inline
arma::mat
qbinom(const arma::mat& p, const int n_trials, const double prob_par, const bool log_form)
{
    return qbinom_int(p,&n_trials,&prob_par,log_form);
}

#endif
