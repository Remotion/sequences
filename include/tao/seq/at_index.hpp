// Copyright (c) 2015-2017 Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/sequences/

#ifndef TAOCPP_SEQUENCES_INCLUDE_AT_INDEX_HPP
#define TAOCPP_SEQUENCES_INCLUDE_AT_INDEX_HPP

#include <cstddef>

#include "make_integer_sequence.hpp"

namespace tao
{
   namespace seq
   {
      // based on http://talesofcpp.fusionfenix.com/post-22/true-story-efficient-packing

      namespace impl
      {
         template< std::size_t, typename T >
         struct indexed
         {
            using type = T;
         };

         template< typename, typename... Ts >
         struct indexer;

         template< std::size_t... Is, typename... Ts >
         struct indexer< index_sequence< Is... >, Ts... >
            : indexed< Is, Ts >...
         {
         };

         template< std::size_t I, typename T >
         indexed< I, T > select( const indexed< I, T >& );
      }

      template< std::size_t I, typename... Ts >
      using at_index = decltype( impl::select< I >( impl::indexer< index_sequence_for< Ts... >, Ts... >() ) );

#ifndef _MSC_VER
      template< std::size_t I, typename... Ts >
      using at_index_t = typename at_index< I, Ts... >::type;
#else
      namespace impl
      {
         template< typename T >
         struct get_type
         {
            using type = typename T::type;
         };
      }

      template< std::size_t I, typename... Ts >
      using at_index_t = typename impl::get_type< at_index< I, Ts... > >::type;
#endif
   }
}

#endif  // TAOCPP_SEQUENCES_INCLUDE_AT_INDEX_HPP
