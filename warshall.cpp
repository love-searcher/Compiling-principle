/*
计算关系闭包
*/
#include <iostream>
#include <vector>

using namespace std ;

void read_data( vector<vector<int> >& data );
void warshall(vector<vector<int> >& data);
void show( const vector<vector<int> >& data );

int main(){
	vector<vector<int>> data ;
	read_data( data );
	warshall( data );
	show(data );
}

void read_data( vector<vector<int> >& data ){
	int size ;
	cin >> size ;
	for( int i = 0 ; i < size ; i ++ ){
		vector<int> temp ; int val ;
		for( int j = 0 ; j < size ; j ++ ){
			cin >> val;
			temp.push_back( val );
		}
		data.push_back( temp );
	}
	return ;
}
void warshall(vector<vector<int> >& data){
	int size = data.size() ;
	for( int i = 0 ; i < size ; i ++ ){
		for( int j = 0 ; j < size ; j ++){
			if ( data[i][j] ){
				for( int k = 0 ; k < size ;k++){
					data[i][k] = (data[i][k] || data[j][k] );
				}
			}
		} 
	}
}
void show( const vector<vector<int> >& data ){
	for( int i = 0 ; i < data.size() ; i ++){
		for( int j = 0 ; j < data[i].size() ; j ++){
			cout << "  " << data[i][j];
		}
		cout << endl ;
	}
}
 
