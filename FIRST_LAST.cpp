/*
根据FIRST、LAST进行语法分析
使用warshall算法进行
*/

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <queue>

using namespace std ;


void read_grammar(char& start, vector<char>& N, vector<char>&T, vector<pair<char,string> >& productions);
void warshall(vector<vector<int> >& data);
void get_first_last(vector<char>& N, vector<char>&T, vector<pair<char,string> >& productions,vector<vector<int> >&FIRST,vector<vector<int> >&SECOND);
void show( vector<char>&N, vector<char>&T ,vector<vector<int>>& arr );

int main(){
	char start ;
	vector<char> N ; vector<char> T ;
	vector<pair<char,string> > productions ; // using map is ok
	//map<char,string> productions_map ; //map<int,char> productions_order ;

	read_grammar(start,N,T,productions);
	vector<vector<int>> first ; vector<vector<int>> last ;
	get_first_last(N, T, productions, first, last);
	cout << "FIRST=" << endl ;
	show(N,T,first); 
	cout << "LAST=" << endl ;
	show(N,T,last);
	warshall( first ); warshall( last) ;
	cout << "FIRST+=" << endl ;
	show(N,T,first); 
	cout << "LAST+=" << endl ;
	show(N,T,last);
	return 0 ;
}

/*
read the grammar info from the cmd
store it in the data stracture
*/
void read_grammar(char& start, vector<char>& N, vector<char>&T, vector<pair<char,string> >& productions){
	int N_num , T_num , P_num ;

	cin >> start >> N_num ;
	char temp ;
	for( int i = 0 ; i < N_num ; i ++ ){
		cin >> temp ;
		N.push_back(temp) ;
	}
	cin >> T_num ;
	for( int i = 0 ; i < T_num ; i ++ ){
		cin >> temp ;
		T.push_back(temp) ;
	}
	cin >> P_num ;
	int num ; char left ; string right_str ;
	for( int i = 0 ; i < P_num ; i ++ ){
		cin >> num >> left >> right_str ;
		productions.push_back( make_pair(left, right_str));
	}
	return ;
}


void get_first(map<char,int>& m, vector<pair<char,string>>& productions, vector<vector<int>>& first){
	for( int i = 0 ; i < productions.size() ; i ++){
		char ch = productions[i].first ;
		char fir = productions[i].second[0] ;
		first[m[ch]][m[fir]] = 1;
	}
	return ;
}

void get_last(map<char,int>& m, vector<pair<char,string>>& productions, vector<vector<int>>& last){
	for( int i = 0 ; i < productions.size() ; i ++){
		char ch = productions[i].first ;
		string str = productions[i].second ;
		char la = str.back();
		last[m[ch]][m[la]] = 1;
	}
	return ;
}

void get_first_last(vector<char>& N, vector<char>&T, vector<pair<char,string> >& productions,vector<vector<int> >&FIRST,vector<vector<int> >&LAST){
	map<char,int> m ;
	for( int i = 0 ; i < N.size() ; i++){
		m[N[i]] = i ;
	}
	for( int i = 0 ; i < T.size() ; i ++){
		m[T[i]] = i+N.size() ;
	}
	for( int i = 0 ; i < T.size()+N.size(); i ++){
		vector<int> temp ;
		for( int j = 0 ; j < T.size()+N.size(); j++){
			temp.push_back( 0 );
		}
		FIRST.push_back( temp );
		LAST.push_back( temp );
	}
	get_first( m, productions,FIRST);
	get_last( m, productions, LAST);
}
/*
计算闭包 
*/
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


void show( vector<char>&N, vector<char>& T, vector<vector<int>>& arr){
	cout << "   " ;
	for( int i = 0 ; i < N.size() ; i ++ )
		cout << "  " << N[i] ;
	for( int i = 0 ; i < T.size() ; i++)
		cout << "  " << T[i] ; 
	cout << endl ;
	int size = N.size() ;
	for( int i = 0 ; i < arr.size() ; i ++ ){
		if ( i < size )
			cout <<"  " <<  N[i] ;
		else cout << "  " << T[i-size] ;
		for( int j = 0 ; j < arr[i].size() ; j ++ ){
			cout << "  " << arr[i][j] ;
		}
		cout << endl ;
	}
}
