/*
Description
 输入字母表，非确定ＦＡ状态集，映射集；用造表法算法。
输出确定ＦＡ状态集，映射集；

Input
 输入字母个数，字母表
状态个数，状态表（状态名称，开始状态，终止状态：0否1是），空格符分隔；
映射个数，映射表（起，终，字母），空格符分隔；
【参考作业3.4】

Output
 Determine State:
状态表: 状态名称，开始状态，终止状态，[子集]
Determine Mapping:
映射表: 起，终，字母,(顺序号
Sample Input Copy
2
x y
5
0 1 0
1 0 0
2 0 0
3 0 0
4 0 1
9
0 1 x
0 2 y
1 2 x
1 3 x
2 1 y
2 3 y
3 3 x
3 3 y
3 4 x
Sample Output Copy
Determine State:
0 1 0 [0]
1 0 0 [1]
2 0 0 [2]
3 0 0 [23]
4 0 0 [13]
5 0 1 [34]
6 0 1 [234]
7 0 0 [3]
Determine Mapping:
0 1 x (0
0 2 y (1
1 3 x (2
2 4 y (3
3 5 x (4
3 4 y (5
4 6 x (6
4 7 y (7
5 5 x (8
5 7 y (9
6 5 x (10
6 4 y (11
7 5 x (12
7 7 y (13
*/

#include <iostream>
#include <vector>
#include <map>
#include <queue> 
#include <algorithm>

using namespace std;
void display_mapping( map<pair<int,char>,vector<int> >& trans );
vector<vector<int> > build_table( map<pair<int,char>,vector<int> >&trans , vector<int>&now , vector<char>&alpha_table , map<pair<vector<int>,char>,vector<int> >&new_trans,vector<vector<int> >&new_states );
void display_determine_state( vector<vector<int> >&new_states ,vector<int> & end_state) ;
void display_determine_mapping( vector<vector<int> >&new_states , vector<char>&alpha_table , map<pair<vector<int>,char>,vector<int> >&new_trans );

int main(){
	vector<int> start_state, end_state ;
	map<pair<int,char>,vector<int> > trans ; // the mapping
	int count ; char temp ;
	vector<char> alpha_table;
	
	cin >> count ; // alpha table
	while( count--){
		cin >> temp ;
		alpha_table.push_back(temp);
	}
	cin >> count ; // initial state
	while( count--) {
		int state,start,end;
		cin >> state >> start >> end ;
		if( start ) start_state.push_back(state);
		if( end ) end_state.push_back(state);
	}
	
	cin >> count ; // mapping
	int begin, end; char action ;
	while( count -- ){
		cin >> begin >> end >> action ;
		trans[make_pair(begin,action)].push_back(end) ;
	}
	
	vector<vector<int> > new_states;
	vector<int> new_start_state = start_state ; 
	new_states.push_back( new_start_state ); //一层复制 
	vector<vector<int> > new_end_state ;
	map<pair<vector<int>,char>,vector<int> > new_trans ;
	
	queue<vector<int> > state_queue ;
	state_queue.push( new_start_state ); // the queue for iteration
	while( !state_queue.empty() ){ // until there is no more new states
		// only concern x as action
		vector<int> now = state_queue.front() ;
		state_queue.pop() ;
		vector<vector<int> > next = build_table( trans , now , alpha_table , new_trans,new_states);
		for( int i = 0 ; i < next.size() ; i++ )
			state_queue.push( next[i] );
	}
//	cout << "Debug begin" << endl ;
	display_determine_state( new_states , end_state );
	display_determine_mapping( new_states , alpha_table , new_trans );
//	display_mapping( trans ) ;
	return 0 ;
}
/*

		if( trans.count(make_pair(begin,action)) ){
			trans[make_pair(begin,action)].push_back(end) ;
		}
*/

void merge_vector( vector<int>&next ,vector<int>& temp){
	for( int i = 0 ; i < temp.size() ; i ++ ){
		int j ;
		for( j = 0 ; j < next.size() ; j ++ ){
			if ( temp[i] == next[j] ) break ;
		}
		if ( j == next.size() ) next.push_back( temp[i] );
	}
	return ;
}

// get next states 
vector<vector<int> > build_table( map<pair<int,char>,vector<int> >&trans , vector<int>&now , vector<char>&alpha_table , map<pair<vector<int>,char>,vector<int> >&new_trans,vector<vector<int> >&new_states ){
	vector<vector<int> > ans ;
	for( int i = 0 ; i < alpha_table.size() ; i ++ ){
		vector<int> next ;
		char action = alpha_table[i] ;
		for( int j = 0 ; j < now.size() ; j ++ ){
			if ( trans.count( make_pair(now[j],action)) ){
				vector<int> temp = trans[make_pair(now[j],action)]; //
				// if temp in next, no need to put it.
				merge_vector( next, temp );
			}
		}
		if ( next.empty() ) continue ;

		sort( next.begin() , next.end() ); //the states are in order
		new_trans[make_pair(now,action)] = next; //pair<vector<int>,char>,vector<int>

		int count ; // judge if it is a new state 
		for ( count = 0 ; count < new_states.size() ; count ++ ){
			if ( next == new_states[count] ) break ;
		}
		if ( count == new_states.size() ){ // for a new state
			new_states.push_back( next );
			ans.push_back( next );
		}
	}	
	return ans ;
}

bool is_terminal( vector<int>& state, vector<int>& end_state){
	for( int i = 0 ; i < state.size() ; i ++ ){
		for( int j = 0 ; j < end_state.size() ; j++ ){
			if ( state[i] == end_state[j] ){
				return true ;
			}
		}
	}
	return false ;
}
// show determine state
void display_determine_state( vector<vector<int> >&new_states,vector<int>& end_state ){
	cout << "Determine State:" << endl ;
	for( int i = 0 ; i < new_states.size() ; i ++ ){
		cout << i << " " ;
		if ( i == 0 ) cout << 1 << " ";
		else cout << 0 << " " ;
		if ( is_terminal( new_states[i] , end_state ))
			cout << 1 << " " << "[";
		else cout << 0 << " " << "[" ;
		for ( int j = 0 ; j < new_states[i].size() ; j ++ ){
			cout << new_states[i][j] ;
		}
		cout << "]" << endl ;
	}
}
void display_determine_mapping( vector<vector<int> >&new_states , vector<char>&alpha_table , map<pair<vector<int>,char>,vector<int> >&new_trans ){
	cout <<"Determine Mapping:" << endl ;
	int count = 0 ;
	for( int i = 0 ; i < new_states.size() ; i ++ ){
		for( int j = 0 ; j < alpha_table.size(); j ++ ){
			int end_index ;
			if ( new_trans.count( make_pair(new_states[i],alpha_table[j]))){
				// find the end state index
				vector<int> end_state = new_trans[make_pair(new_states[i],alpha_table[j])] ;
				for( int c = 0 ; c < new_states.size(); c++){
					if ( new_states[c] == end_state )
						end_index = c ;
				}
				cout << i << " " << end_index << " " << alpha_table[j] << " ("<< count ++ << endl;				
			}
		}
	}
	return ;
}

// show information
void display_mapping( map<pair<int,char>,vector<int> >& trans ){
	cout << "This is the mapping." << endl ;
	for( map<pair<int,char>,vector<int> >::iterator it=trans.begin();it!=trans.end();it++){
		pair<int,char> a = it->first ; vector<int> b=it->second ;
		cout << a.first << " " << a.second << " " ;
		for( int i = 0 ; i < b.size(); i++ ){
			cout << b[i] << " " ;
		}
		cout << endl ;
	}
}
