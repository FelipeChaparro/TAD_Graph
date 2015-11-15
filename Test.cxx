#include <iostream>
#include <stack>

#include "Graph.h"

typedef PUJ::Graph< char , int > TGraph;

int main( int args, char* argv[] ) {
  TGraph g;
  // Wikipedia Graph: https://es.wikipedia.org/wiki/Anexo:Ejemplo_de_Algoritmo_de_Dijkstra
  
  // IMPORTANT ! Route
  std::stack< long > route;

  g.AddVertex( 'a' ); // 0
  g.AddVertex( 'b' ); // 1
  g.AddVertex( 'c' ); // 2
  g.AddVertex( 'd' ); // 3
  g.AddVertex( 'e' ); // 4
  g.AddVertex( 'f' ); // 5
  g.AddVertex( 'g' ); // 6
  g.AddVertex( 'z' ); // 7

  // Edges
  g.AddArc( 0, 1, 16 );
  g.AddArc( 0, 2, 10 );
  g.AddArc( 0, 3, 5 );

  g.AddArc( 1, 6, 6 );
  g.AddArc( 1, 5, 4 );
  g.AddArc( 1, 2, 2 );
  g.AddArc( 1, 0, 16 );

  g.AddArc( 2, 0, 10 );
  g.AddArc( 2, 1, 2 );
  g.AddArc( 2, 3, 4 );
  g.AddArc( 2, 4, 10 );
  g.AddArc( 2, 5, 12 );

  g.AddArc( 3, 0, 5 );
  g.AddArc( 3, 2, 4 );
  g.AddArc( 3, 4, 15 );
  
  g.AddArc( 4, 3, 15 );
  g.AddArc( 4, 2, 10 );
  g.AddArc( 4, 5, 3 );
  g.AddArc( 4, 7, 5 );

  g.AddArc( 5, 4, 3 );
  g.AddArc( 5, 1, 4 );
  g.AddArc( 5, 2, 12 );
  g.AddArc( 5, 6, 8 );
  g.AddArc( 5, 7, 16 );

  g.AddArc( 6, 1, 6 );
  g.AddArc( 6, 5, 8 );
  g.AddArc( 6, 7, 7 );

  g.AddArc( 7, 6, 7 );
  g.AddArc( 7, 5, 16 );
  g.AddArc( 7, 4, 5 );

  // sudo apt-get install graphviz
  g.PrintAsPNG( "Wikipedia.png" );
  std::cout << "Vertex: " << g.CountVertex( ) << std::endl;
  std::cout << "Distance of shortest path ( A, Z ): " << g.Dijkstra( g.ReturnIndex( 'a' ), g.ReturnIndex( 'z' ), route ) << std::endl;
  //
  std::cout << "Route: ";
  while ( !route.empty() ) {
    std::cout << g.ReturnVertex( route.top( ) ) << " ";
    route.pop();  
  }
  std::cout << std::endl;

  return 0;
}
