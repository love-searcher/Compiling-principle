/*
Description
 输入开始符号，非终结符，终结符，语意动作表，产生式，LL(1)分析表
输出LL(1)语意处理动作

Input
 输入开始符号；
非终结符个数，非终结符，空格符分隔；
终结符个数，终结符，空格符分隔；
语意动作个数，语意动作符，空格符分隔；
产生式的个数，各产生式的序号，产生式的左边和右边符号，空格符分隔；
LL(1)分析表中的产生式个数，序号，行符号，列符号，产生式编号，空格符分隔；

Output
 语意动作符序列；用空格隔开，第一个动作前有一空格。

Sample Input Copy
E
6  E A T B F D
9  + - * / ( ) x y z 
7  1 2 3 4 5 6 7
13
1  E TA
2  A +TA1
3  A -TA2
4  A k
5  T FB
6  B *FB3
7  B /FB4
8  B k
9  F (E)
10 F D
11 D x5
12 D y6
13 D z7
7
1 ADD
2 SUB
3 MUL
4 DIV
5 a
6 b
7 c
25
1  E ( 1
2  E x 1
3  E y 1
4  E z 1
5  A + 2
6  A - 3
7  A ) 4
8  A # 4
9  T ( 5
10 T x 5
11 T y 5
12 T z 5
13 B + 8
14 B - 8
15 B * 6
16 B / 7
17 B ) 8
18 B # 8
19 F ( 9
20 F x 10
21 F y 10
22 F z 10
23 D x 11
24 D y 12
25 D z 13
(x+(y-x*z)*(y+x*z))+x/z#
Sample Output Copy
 a b a c MUL SUB b a c MUL ADD MUL ADD a c DIV ADD
*/
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <queue>

using namespace std ;


void read_grammar(char& start, vector<char>& N, vector<char>&T, vector<pair<char,string> >& productions, vector<int>& goal_item);
void read_actions( vector<string>& actions );

void read_LL_table( map<pair<char,char>,int> & table );
void LL_translation(string str,char start, map<pair<char,char>,int>& table, vector<pair<char,string>>& productions, vector<char>& N, int item_size, vector<int>& ans);


int main(){
	char start ;
	vector<char> N ; vector<char> T ;
	vector<pair<char,string> > productions ; // using map is ok
	//map<char,string> productions_map ; //map<int,char> productions_order ;

	vector<int> goal_item ;
	read_grammar(start,N,T,productions, goal_item);

	vector<string> actions ;
	read_actions( actions );
	map<pair<char,char>,int> table ;
	read_LL_table( table );
	string str; 
	cin >> str ;

	vector<int> ans ;
	LL_translation(str, start, table, productions, N, goal_item.size(), ans);
	//

	for ( int i = 0 ; i < ans.size() ; i ++ ){
		int index = ans[i]-1 ;
		cout << actions[index] << " " ;
	}
	cout << endl ;
	return 0 ;
}

/*
read the grammar info from the cmd
store it in the data stracture
*/
void read_grammar(char& start, vector<char>& N, vector<char>&T, vector<pair<char,string> >& productions, vector<int>& goal_item){
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
	int goal_num , temp1;
	cin >> goal_num ;
	for( int i = 0 ; i < goal_num ; i ++ ){
		cin >> temp1 ; //???? useless
		goal_item.push_back( temp1 );
	}

	cin >> P_num ;
	int num ; char left ; string right_str ;
	for( int i = 0 ; i < P_num ; i ++ ){
		cin >> num >> left >> right_str ;
		productions.push_back( make_pair(left, right_str));
	}
	return ;
}

/*
read these actions ?
*/
void read_actions( vector<string>& actions ){
	int num , temp;
	string str ;
	cin >> num ;
	for( int i = 0 ; i < num ; i ++ ){
		cin >> temp >> str ;
		actions.push_back( str ) ;
	}
}

/*
read the LR table
*/
void read_LL_table( map<pair<char,char>,int> & table ){
	int num, p_num , temp;
	char N, t ;
	cin >> num ;
	for( int i = 0 ; i < num ; i++ ){
		cin >> temp >> N >> t >> p_num ;
		table[make_pair(N,t)] = p_num ;
	}
	return ;
}


void display( vector<char>& char_vector ){
	for( int i = 0 ; i < char_vector.size() ; i ++ ){
		cout << char_vector[i] << "   " ;
	}
	cout << endl ;
}

bool in_char(char ch, vector<char>& temp ){
	for( int i = 0 ; i < temp.size() ; i ++ ){
		if ( temp[i] == ch )
			return true ;
	}
	return false ;
}
/*
translate using LL
*/
void LL_translation(string str,char start, map<pair<char,char>,int>& table, vector<pair<char,string>>& productions, vector<char>& N, int item_size, vector<int>& ans){
	vector<char> trans_q ;
	trans_q.push_back( start );
	int index = 0 ;
	while( index < str.length() && !trans_q.empty()){
		//display( trans_q );
		char first_item = trans_q.back() ;
		//cout << first_item << endl ;
		trans_q.pop_back() ;
		if ( in_char(first_item, N) ){
			//using the first non terminal ==
			int production_num = table[make_pair(first_item, str[index] )] ; // may be error here
			string add_str = productions[production_num-1].second ; // the order
			//cout << "add_str " << add_str << endl ;
			for( int i = add_str.length()-1; i>=0 ; i-- )
				trans_q.push_back( add_str[i] );
		}
		if ( first_item == str[index] ){
			index ++ ;
			continue ;
		}
		if ( first_item == 'k' ){ // special symble
			continue ;
		}
		if ( first_item == '#'){ // terminal
			return ;
		}
		if ( first_item-'0' >= 1 && first_item-'0' <= item_size ){
			//cout << "? $" << endl ;
			ans.push_back( int(first_item-'0') );
			continue ;
		}

	}
}
