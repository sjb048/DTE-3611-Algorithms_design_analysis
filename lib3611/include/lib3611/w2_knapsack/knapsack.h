#ifndef DTE3611_WEEK2_KNAPSACK_H
#define DTE3611_WEEK2_KNAPSACK_H

// stl
//#include <iterator>
#include <ranges>
#include <algorithm>
#include<functional>
#include<vector>
namespace dte3611::np::algorithms
{

  namespace detail
  {

    struct knapsack_01_fn {

      /**************************
       *  Iterator Range Operator
       */

      // Type Generics
      template <std::input_iterator           Iterator_T,
                std::sentinel_for<Iterator_T> Sentinel_T,
                std::weakly_incrementable     Output_T,
                typename ValueProjection_T  = std::identity,
                typename WeightProjection_T = std::identity>
      // Return value
      int
      // Call-operator signature
      operator()(Iterator_T  begin , Sentinel_T end ,
                 Output_T  result , int capacity ,
                 ValueProjection_T  value_projection ,
                 WeightProjection_T  weight_projection) const
      {
        auto const n = std::ranges::distance(begin,end);
        auto const W = capacity;

        //invoke weight projection and determine its type
        using w_type= typename std::decay_t<decltype(std::invoke(weight_projection,begin))>;

        using M_type = std::vector<std::vector<w_type>>;

        //declare memoization table
        M_type M;
         //remember o resize M[][] first

        M.resize(n+1);
        // loop to create the table dynamically
        for(int i = 0;i<=n;i++)
        {
             M[i].resize(W+1);
        }
        //now compute values for M
        for(int i = 1;i<=n;i++)
        {
            for(int c = 0;c<=W;c++)
            {
                auto const vi = std::invoke(value_projection,*(begin+i-1));
                auto const wi = std::invoke(weight_projection,*(begin+i-1));
                 // Store the value of function call
                 if(wi>c)
                 {
                    M[i][c]= M[i-1][c];
                 }
                 else
                    M[i][c]= std::max(M[i-1][c],vi + M[i-1][c-wi]);
                 // Store value in a table before return
            }
        }

        int current = W;
         // Now implement back-tracking to populate the result container
        for(auto j=n;j>0;j--)
        {
            auto const wi = std::invoke(weight_projection,*(begin+j-1));

            if(M[j][current] > M[j-1][current])
            {
                std::fill_n(result, 1, true);
                current = current - wi;
            }
            else
                std::fill_n(result, 1, false);
        }

        return M[n][W];
      }

      /******************
       *  Ranges Operator
       */

      // Type Generics
      template <std::ranges::input_range  Range_T,
                std::weakly_incrementable Output_T,
                typename ValueProjection_T  = std::identity,
                typename WeightProjection_T = std::identity>
      // Return value

      auto
      // Call-operator signature
      operator()(Range_T&& range, Output_T result, int capacity,
                 ValueProjection_T  value_projection,
                 WeightProjection_T weight_projection) const
      {
        return (*this)(std::ranges::begin(range), std::ranges::end(range),
                       std::move(result), capacity, std::ref(value_projection),
                       std::ref(weight_projection));
        //      static_assert( false, "Complete the code - find the appropriate call signature in the cpp reference documentation." );
      }

    };

  }   // namespace detail

  inline constexpr detail::knapsack_01_fn knapsack_01{};


}   // namespace dte3611::np::algorithms


#endif   // DTE3611_WEEK2_KNAPSACK_H
