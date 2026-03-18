#ifndef DTE3611_WEEK2_SUBSET_SUM_H
#define DTE3611_WEEK2_SUBSET_SUM_H


// concepts
// ...

// stl
#include <vector>
#include <algorithm>
#include <ranges>

#include <numeric>

namespace dte3611::np::algorithms
{

  namespace detail
  {

    struct subset_sum_fn {

      /************************
       *  Return type -- helper
       */
      template <typename Value_T>
      using SubsetSum_Output = std::vector<std::vector<Value_T>>;



      template <typename Value_T>
      using SubsetSum = std::vector<Value_T>;


     template <std::forward_iterator         Iterator_T,
                  std::sentinel_for<Iterator_T> Sentinel_T,
                  typename Projection_T = std::identity, typename Value_T>

      void addToSum(SubsetSum_Output<Value_T> &candidate_sums,
                    SubsetSum<Value_T> &cur_sums,Iterator_T val, Sentinel_T end) const
      {
          //stop criterion
          if (val == end) return;


          // here is our decision problem


          //two options:
          //left: val is not included in the sum
          //recursive call to add to sum
          candidate_sums.push_back(cur_sums);
          addToSum(candidate_sums, cur_sums,val+1, end);

          //right: val is included in the sum
          //recursive call to add to sum
          auto sum_inclusive {cur_sums};
          sum_inclusive.push_back(*val);
          candidate_sums.push_back(sum_inclusive);
          addToSum(candidate_sums, sum_inclusive,val+1, end);
      }

      /**************************
       *  Iterator Range Operator
       */
      // Type Generics
      template <std::forward_iterator         Iterator_T,
                std::sentinel_for<Iterator_T> Sentinel_T,
                typename Projection_T = std::identity, typename Value_T>

      // Return value
      SubsetSum_Output<Value_T>



      // Call-operator signature
      operator()(Iterator_T begin, Sentinel_T end, Value_T target,
                 Projection_T /* projection */ = {} ) const
      {

           SubsetSum_Output<Value_T> candidates, output;
           auto val{begin};
           SubsetSum<Value_T> c_sum;
           addToSum(candidates,c_sum,val,end);

          //call recursive method to compute our candidate subsums
          // add to sum(candidates
          //iterate through candidates subset and add those with sums
          //equal to the target sum to output
           for_each(candidates.begin(),candidates.end(), [&](SubsetSum<Value_T>& sum){
               auto subsum= std::accumulate(sum.begin(),sum.end(),0);
               if (subsum== target)
                   output.push_back(sum);
           });
//
        /* function content */
        return output;
      }


      /******************
       *  Ranges Operator
       */

      // Type Generics
      template <std::ranges::forward_range Range_T,
                typename Projection_T = std::identity, typename Value_T>

      // Return value
      SubsetSum_Output<Value_T>

      // Call-operator signature
      operator()(Range_T&& range, Value_T target,
                 Projection_T projection = {}) const
      {
        return (*this)(std::ranges::begin(range), std::ranges::end(range),
                       target, std::ref(projection));
        //      static_assert( false, "Complete the code - find the appropriate call signature in the cpp reference documentation." );
      }
    };

  }   // namespace detail

  inline constexpr detail::subset_sum_fn subset_sum{};

}   // namespace dte3611::np::algorithms


#endif   // DTE3611_WEEK2_SUBSET_SUM_H
