#define DTE3611_DAY4_DEPTH_FIRST_SEARCH_H
#define DTE3611_DAY4_DEPTH_FIRST_SEARCH_H

// concepts
#include "../utils/concepts/graphs.h"

#include <boost/graph/adjacency_list.hpp>
#include<stack>
#include<list>
#include<vector>
#include<utility>
#include<algorithm>

namespace dte3611::graph::algorithms
{

  template <predef::concepts::graph::BidirectionalGraph Graph_T>
  std::vector<typename Graph_T::vertex_descriptor>
  depthFirstSearch([[maybe_unused]] Graph_T const& graph,
                   [[maybe_unused]]
                   typename Graph_T::vertex_descriptor const& start)
  {

//      using VertexDescriptor = typename Graph_T::vertex_descriptor;
//      auto u = VertexDescriptor();

//      std::vector<VertexDescriptor> visited, nodes;
//      std::list<VertexDescriptor> node_queue;

//      // Initialize
//      visited.push_back(start);
//      node_queue.push_back(start);


//      while (!node_queue.empty()) {
//          u = node_queue.front();
//          if (u != start) {
//              nodes.push_back(u);
//          }
//          node_queue.pop_front();

//          auto adj_vertices = boost::adjacent_vertices(u, graph);


//          for (auto i = adj_vertices.second; i != adj_vertices.first; --i) {
//              auto const vi = *i;
//              if (std::find(visited.begin(), visited.end(), vi) == visited.end()) {
//                  visited.push_back(vi);
//                  node_queue.push_front(vi);
//              }
//          }
//      }

//      return nodes;



      using VertexDescriptor = typename Graph_T::vertex_descriptor;
//         auto  u = VertexDescriptor();

         std::vector<VertexDescriptor>   visited;
         std::list<VertexDescriptor>     stack;
     //    std::list<int>::iterator     i;



          stack.push_back(start);
          visited.push_back(start);
          while(!stack.empty())
          {
              auto ver = stack.top();
              stack.pop_back();
              if (std::find(visited.begin(),visited.end(),ver)!= visited.end())
              {
                  continue;
              }
              visited.push_back(ver);
              auto vertices = boost::adjacent_vertices(ver,graph);
             // std::list<int>::iterator i;

              for(auto i =  vertices.first; i!= vertices.second ; i++)
              {
                  auto const vi = (*i);
                  stack.push_front(vi);
                  visited.push_back(vi);
              }
          }

         return visited;

  }

}   // namespace dte3611::graph::algorithms


   // DTE3611_DAY4_DEPTH_FIRST_SEARCH_H
