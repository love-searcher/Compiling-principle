/*

workflow
	read_relation
	bell_matrix
	priority_function
input :
5
+ * i ( )
> < < < >
> > < < >
> > 0 0 >
< < < < =
> > 0 0 >

*/
#include <iostream>
#include <vector>

using namespace std ;

//void init_arr( vector<vector<int>>& arr , int size);
void read_info( vector<vector<char> >& arr, vector<char>& symble);
void build_connection(vector<vector<char> >& arr, vector<vector<int> >& matrix, vector<int>& node_values );
void show( vector<vector<int> >& arr, vector<int>& values);
void show_function( vector<int>& node_values , vector<char>& symble );	

int main(){
	vector<vector<char> > arr ;
	vector<char> symble ;
	read_info( arr, symble );
	
	vector<vector<int> > matrix ;
	vector<int> node_values ;
	build_connection(arr, matrix, node_values ) ;

	show( matrix , node_values );
	show_function( node_values , symble );	

    return 0 ;    
}

void init_arr( vector<vector<int> >& arr , int size){
	for ( int i = 0 ; i < size ; i ++ ){
		vector<int> temp ;
		for ( int j = 0 ; j < size ; j ++ )
			temp.push_back( 0 );
		arr.push_back( temp );
	}
	return ;
}

/*
read the input information.
args :
	arr and symble are initial empty
return :
	the changes are stored in arr and symble 
*/
void read_info( vector<vector<char> >& arr, vector<char>& symble){
	int size = 0 ;
	cin >> size ;
	char temp ;
	for ( int i = 0 ; i < size ; i ++ ){
		cin >> temp ;
		symble.push_back( temp );
	}
	
	// table 
	for ( int i = 0 ; i < size ; i ++ ){
		vector<char> row ; char temp ; 
		for ( int j = 0 ; j < size ; j ++ ){
			cin >> temp ;
			row.push_back( temp );
		}
		arr.push_back( row );
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
/*

*/
void build_connection(vector<vector<char> >& arr, vector<vector<int> >& matrix, vector<int>& node_values ){
	int size = arr.size() ;
	init_arr( matrix, 2*size ); // init as 0
	// Bell method
	for ( int i = 0 ; i < size ; i ++ ){
		for ( int j = 0 ; j < size ; j ++ ){
			//switch arr[i][j]
			if ( arr[i][j] == '>' ){
				matrix[i][size+j] = 1 ;
			}
			if ( arr[i][j] == '<' ){
				matrix[size+j][i] = 1 ;
			}
			if ( arr[i][j] == '=' ){
				matrix[i][size+j] = 1 ;
				matrix[size+j][i] = 1 ;
			}
		}
	}
	for ( int i = 0 ; i < 2*size ; i ++ )
		matrix[i][i] = 1 ;
	warshall( matrix );
	for( int i = 0 ; i < 2*size ; i ++ ){
		node_values.push_back( 0 );
		for ( int j = 0 ; j < 2*size ; j ++ ){
			node_values[i] += matrix[i][j] ;
		}
	}
	return ;
}

void show( vector<vector<int> >& arr , vector<int>& values ){
	for ( int i = 0 ; i < arr.size() ; i ++ ){
		cout << "  " << values[i] ;
		for ( int j = 0 ; j < arr[i].size() ; j ++ ){
			cout << "  " << arr[i][j] ;
		}
		cout << endl ;
	}
	return ;
}

void show_function( vector<int>& node_values , vector<char>& symble ){
	int size = symble.size() ;
	cout << "   " ;
	for ( int i = 0 ; i < size ; i ++ ){
		cout << "  " << symble[i] ;
	}
	cout << endl ;
	cout << "  f" ;
	for( int i = 0 ; i < size; i ++ )
		cout << "  " << node_values[i] ;
	cout << endl ;
	cout << "  g" ;
	for( int i = 0 ; i < size ; i ++ )
		cout << "  " << node_values[i+size] ;
	cout << endl ;
}
