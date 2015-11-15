#ifndef __PUJ__GRAPH__HXX__
#define __PUJ__GRAPH__HXX__

#include <cstdlib>
#include <queue>
#include <sstream>

// -------------------------------------------------------------------------
template< class V, class C >
PUJ::Graph< V, C >::
Graph( )
{
}

// -------------------------------------------------------------------------
template< class V, class C >
PUJ::Graph< V, C >::
~Graph( )
{
}

// -------------------------------------------------------------------------
template< class V, class C >
long PUJ::Graph< V, C >::
AddVertex( const V& v )
{
	this->m_Vertices.push_back( v );
	return( this->m_Vertices.size( ) - 1 );
}

// -------------------------------------------------------------------------
template< class V, class C >
void PUJ::Graph< V, C >::
AddArc( const long& a, const long& b, const C& c )
{
	this->m_Costs[ a ][ b ] = c;
}

// -------------------------------------------------------------------------
template< class V, class C >
int PUJ::Graph< V, C >::
CountIslands( ) const
{
  // Init values
	long N = this->m_Vertices.size( );
	std::vector< bool > marks( N, false );
	long count_marked = 0;
	int count_islands = 0;

	// Stop when absolutely all vertex have been visited
	while( count_marked < N )
	{
	// Choose an un-marked vertex
	long start = 0;
	while( marks[ start ] )
		start++;

		// DFS iteration
		std::queue< long > q;
    	q.push( start );
    	while( !q.empty( ) )
    	{
      	// Get a vertex from queue
      	long v = q.front( );
      	q.pop( );

      	// Mark it
      	if( marks[ v ] )
        	continue;
      	marks[ v ] = true;
      	count_marked++;

      	// Add neighbors to queue
      	typename TMatrix::const_iterator mIt = this->m_Costs.find( v );
		if( mIt != this->m_Costs.end( ) )
		{
        	typename TRow::const_iterator rIt = mIt->second.begin( );
        	for( ; rIt != mIt->second.end( ); ++rIt )
         	 q.push( rIt->first );

		} // fi

	} // elihw

	// Ok, one island marked!
	count_islands++;

	} // elihw
	return( count_islands );
}

// -------------------------------------------------------------------------
template< class V, class C >
bool PUJ::Graph< V, C >::
IsBipartite( ) const
{
	// Init values
	long N = this->m_Vertices.size( );
	std::vector< int > marks( N, 0 ); // 0: no mark, 1: color 1, 2: color 2
	long count_marked = 0;
	bool is_bipartite = true;

	// Stop when absolutely all vertex have been visited or the bipartite flag
	// goes "false"
	while( count_marked < N && is_bipartite )
	{
	// Choose an un-marked vertex
		long start = 0;
		while( marks[ start ] != 0 )
		start++;

		// DFS iteration with parent track
		std::queue< std::pair< long, long > > q;
		q.push( std::pair< long, long >( start, start ) );
		while( !q.empty( ) && is_bipartite )
		{
		// Get a vertex (and its parent) from queue
		std::pair< long, long > v = q.front( );
		long vertex = v.first;
		long parent = v.second;
		q.pop( );

		// Mark it with an appropriate color
		if( marks[ vertex ] != 0 )
		continue;
		marks[ vertex ] = ( marks[ parent ] == 1 )? 2: 1;
		count_marked++;

		// Add neighbors to queue
		typename TMatrix::const_iterator mIt = this->m_Costs.find( vertex );
		if( mIt != this->m_Costs.end( ) )
		{
			typename TRow::const_iterator rIt = mIt->second.begin( );
			for( ; rIt != mIt->second.end( ); ++rIt )
			{
			// Update bipartite flag: if both colors are equal, both vertices
			// have been already been visited -> no bipartition
			is_bipartite &= ( marks[ vertex ] != marks[ rIt->first ] );
			q.push( std::pair< long, long >( rIt->first, vertex ) );

			} // rof

		} // fi

	} // elihw

	} // elihw
	return( is_bipartite );
}

// -------------------------------------------------------------------------
template< class V, class C >
void PUJ::Graph< V, C >::
Levels( long source )
{
	std::vector< bool > marks( this->m_Vertices.size(), false );
	std::queue< long > q;

	q.push( source );

	while( !q.empty() ) {
		long node = q.front();

		q.pop();
 
		if ( marks[node] ) 
		    continue;

		std::cout << node << " ";
		marks[node] = true;
    
		typename TMatrix::const_iterator cIt = this->m_Costs.find( node );
		if ( cIt != this->m_Costs.end() ) {

		typename TRow::const_iterator rIt = cIt->second.begin();
		for ( ; rIt != cIt->second.end() ; rIt++ )
			q.push( rIt->first );

    	} // fi
  
  	} // elihw

  std::cout << std::endl;
}

// -------------------------------------------------------------------------
template< class V, class C >
bool PUJ::Graph< V, C >::
HasArc( const long& a, const long& b )
{
	typename TMatrix::const_iterator rIt = this->m_Costs.find( a );
	if ( rIt != this->m_Costs.end() )
		return ( rIt->second.find( b ) != rIt->second.end() );
	return false;
}

// -------------------------------------------------------------------------
template< class V, class C >
V& PUJ::Graph< V, C >::
ReturnVertex( const long& a )
{
	return this->m_Vertices[ a ];
}

// -------------------------------------------------------------------------
template< class V, class C >
C& PUJ::Graph< V, C >::
ReturnCost( const long& a, const long& b )
{
  return this->m_Costs[ a ][ b ];
}

// -------------------------------------------------------------------------
template< class V, class C >
C PUJ::Graph< V, C >::
Dijkstra( const long& source, const long& target, std::stack< long >& route )
{
	std::list< long > q;
	std::vector< C > dist;
	std::vector< long > prev;
	C aux, menor; long u;
	std::list< long >::iterator it;
	
  
	for ( long v = 0 ; v < this->m_Vertices.size() ; v++ ) {
		dist.push_back ( 1000000 ) ;
		q.push_back( v );
		prev.push_back( -1 );
	}
	
	dist[source] = 0;

	while ( !q.empty() ) {
		menor = 1000000;
		// Vertex in 'q' with min dist[u];
		
		it = q.begin();
		for ( ; it != q.end() ; it++ )
			if ( dist[*it] < menor ) {
				menor = dist[*it];
				u = *it;
			}
	
		// Remove u from 'q';
		it = q.begin();
		for ( ; it != q.end() ; ) {
			if ( *it == u )
				it = q.erase( it );
			else it++;
		}
		
		// Si se llega al 'target' se termina la busqueda
		if ( u == target ) break;
			

		for ( long v = 0 ; v < this->m_Vertices.size() ; v++ ) {
			if ( HasArc( u, v ) ) {
				aux = dist[u] + ReturnCost( u, v );
				if ( aux < dist[v] ) {
					dist[v] = aux;
					prev[v] = u;
				}

			} // fi

		} // rof

	} // elihw

	// Route
	while ( prev[u] != -1 ) {
		route.push( u );
		u = prev[u];
	}
	route.push( u );
	
	return dist[target];

}

// -------------------------------------------------------------------------
template< class V, class C >
int PUJ::Graph< V, C >::
CountVertex( ) const
{
	return this->m_Vertices.size();
}

// -------------------------------------------------------------------------
// Es necesario instalar 'graphviz'
// sudo apt-get install graphviz
template< class V, class C >
void PUJ::Graph< V, C >::
PrintAsPNG( const std::string& filename ) const
{
	std::stringstream str;
	str << "echo \"digraph G {" << std::endl;
	typename TMatrix::const_iterator mIt = this->m_Costs.begin( );
	for( ; mIt != this->m_Costs.end( ); ++mIt )
	{
		typename TRow::const_iterator rIt = mIt->second.begin( );
		for( ; rIt != mIt->second.end( ); ++rIt )
			str << mIt->first << " -> " << rIt->first << std::endl;
	}
	str << "}\" | dot -Tpng > " << filename;
	std::system( str.str( ).c_str( ) );
}

// -------------------------------------------------------------------------
template< class V, class C >
long PUJ::Graph< V, C >::
ReturnIndex( const V& v )
{
	for ( unsigned int i = 0 ; i < this->m_Vertices.size() ; i++ ) 
		if ( this->m_Vertices[i] == v ) return i;
  
	return -1;
}

#endif // __PUJ__GRAPH__HXX__

// eof - Graph.hxx
