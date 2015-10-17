// The Art of C++ / Sequences
// Copyright (c) 2015 Daniel Frey

#include <tao/seq/tuple_cat.hpp>

#include <type_traits>
#include <tuple>

#define USE std
//#define USE tao::seq

int main()
{
  auto t = USE::tuple_cat( std::make_tuple( 1, true ),
			   std::make_tuple( 1.0 ),
			   std::make_tuple(),
			   std::make_tuple( 1UL, nullptr ) );

  static_assert( std::is_same< decltype( t ), std::tuple< int, bool, double, unsigned long, std::nullptr_t > >::value, "oops" );

  auto t2 = USE::tuple_cat( t, std::make_tuple( 1, true ),
			    t, std::make_tuple( 1.0 ),
			    t, std::make_tuple(),
			    t, std::make_tuple( 1UL, nullptr ) );

  auto t3 = USE::tuple_cat( t2, std::make_tuple( 1, true ),
			    t2, std::make_tuple( 1.0 ),
			    t2, std::make_tuple(),
			    t2, std::make_tuple( 1UL, nullptr ) );

  auto t4 = USE::tuple_cat( t3, std::make_tuple( 1, true ),
			    t2, std::make_tuple( 1.0 ),
			    t3, std::make_tuple(),
			    t2, std::make_tuple( 1UL, nullptr ) );

  static_assert( std::tuple_size< decltype( t4 ) >::value == 265, "oops" );
}