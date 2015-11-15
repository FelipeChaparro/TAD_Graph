// References:
// [1]. Florez, Leonardo. (2015). TAD Grafo.
// [2]. Wikipedia, (2015). Dijkstra's algorithm. [online] Available at: https://en.wikipedia.org/wiki/Dijkstra's_algorithm [Accessed 13 Nov. 2015].

#ifndef __PUJ__GRAPH__H__
#define __PUJ__GRAPH__H__

#include <map>
#include <vector>
#include <list>
#include <stack>

namespace PUJ
{
  template< class V, class C >
  class Graph
  {
  public:
    Graph( );
    virtual ~Graph( );

	long AddVertex( const V& v );
    void AddArc( const long& a, const long& b, const C& c );

    int CountIslands( ) const;
    int CountVertex( ) const;
    bool IsBipartite( ) const;
    void Levels( long source );
    bool HasArc( const long& a, const long& b );
    V& ReturnVertex( const long& a );
    C& ReturnCost( const long& a, const long& b );
    long ReturnIndex( const V& v );
    C Dijkstra( const long& source, const long& target, std::stack< long >& route );

    void PrintAsPNG( const std::string& filename ) const;

  protected:
    std::vector< V > m_Vertices;

    typedef std::map< long, C >    TRow;
    typedef std::map< long, TRow > TMatrix;
    TMatrix m_Costs;
  };

} // ecaseman

#include "Graph.hxx"

#endif // __PUJ__GRAPH__H__

// eof - Graph.h
