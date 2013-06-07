#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "windows.h"
#include <sstream>
#include <iterator>
using namespace std;

typedef vector<int> VInt;
typedef vector<VInt> VVInt;
typedef VInt::iterator VIter;

VVInt graph;
VInt colors, parents, enter, low;
int NumVer = 0;
int Edge = 0;

ofstream out( "output.txt");
//------------------------------------------------------------------------
/* Поиск в глубину, выполняющий вычисление enter и low
 u - номер вершины в графе
 */
void visitLow( int u ) {
	colors[u] = 1;
	low[u] = enter[u] = ++NumVer;
   
	for ( VIter it = graph[u].begin(); it != graph[u].end(); it++ )
		if ( colors[*it] == 0 ) {
			parents[*it] = u;
			Edge++;
			visitLow( *it );
			low[u] = min( low[u], low[*it] );
		}
		else{
			if ( colors[*it] == 1 && *it != parents[u] ){
				Edge++;
				low[u] = min( low[u], enter[*it] );
			}
		}

	colors[u] = 2; 
// вывод мостов
	if ( low[u] >= enter[u] )
		if ( parents[u] != -1 )
			out << "--->" << parents[u] + 1 << "-" << u + 1 <<endl;
}
//------------------------------------------------------------------------
int main() {
	int n = 0; //число вершин
	int v;
	int j;
   
// Прочитаем граф
	ifstream inFile ( "adjList_undir_70_30_off.txt" );
	string str;

	while ( !inFile.eof() ){
		j = 1;
		n++;
		inFile >> str;
		graph.resize( n );
		getline( inFile, str );
		
		std::istringstream in(str);

		std::copy( std::istream_iterator<int>( in ), std::istream_iterator<int>(), std::back_inserter( graph[n-1] ) );	

		int j = 0;
		while ( j < graph[n-1].size() ){
			graph[n-1][j] = graph[n-1][j] - 1;
			j++;
		}		
	}
// вычислим enter и low
	colors.assign( n, 0 );
	parents.assign( n, -1 );
	enter.resize( n );
	low.resize( n );
	int t1, t2;
	
	n--;
	LARGE_INTEGER start, finish, freq;
	QueryPerformanceFrequency( &freq );
	QueryPerformanceCounter( &start );


	t1 = GetTickCount();
	visitLow( 0 );
	t2 = GetTickCount();

	QueryPerformanceCounter( &finish );
	double time = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;

	out << "Vertexes:" << n << "\nEdges:" << Edge << "\nTime:" << time << "\nK:" << time/n/Edge << endl;
	//system( "pause" );
}
