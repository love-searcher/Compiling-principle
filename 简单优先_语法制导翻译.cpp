/*
输入开始符号，非终结符，终结符，语意动作表，产生式
输出简单优先法的语意处理动作
以简单优先算术表达式G[E]: 为例
E→E+T | E-T | A
A→T
T→F*T | F/T | F
F→(B) | D
B→E
D→x | y | z

Input
 输入开始符号；
非终结符个数，非终结符，空格符分隔；
终结符个数，终结符，空格符分隔；
语意动作个数，语意动作符，空格符分隔；
产生式的个数，各产生式的序号，产生式的左边和右边符号源产生式，目标产生式，空格符分隔；
简单优先分析表方阵的行列数，简单优先分析表，空格符分隔；
输入分析字符串，#结束

Output
 输出分析过程:
语意动作符序列；用空格隔开，第一个动作前有一空格。

Sample Input Copy
E
6  E A T F B D
9 + -  * / ( ) x y z 
7  1 2 3 4 5 6 7
13
1  E E+T 1
2  E E-T 2
3  E A   0
4  A T   0
5  T F*T 3
6  T F/T 4
7  T F   0
8  F (B) 0
9  F D   0
10 B E   0
11 D x   5
12 D y   6
13 D z   7
7
1 ADD
2 SUB
3 MUL
4 DIV
5 a
6 b
7 c
15
  0  0  0  0  0  0  2  2  0  0  0  3  0  0  0
  0  0  0  0  0  0  3  3  0  0  0  3  0  0  0
  0  0  0  0  0  0  3  3  0  0  0  3  0  0  0
  0  0  0  0  0  0  3  3  2  2  0  3  0  0  0
  0  0  0  0  0  0  0  0  0  0  0  2  0  0  0
  0  0  0  0  0  0  3  3  3  3  0  3  0  0  0
  0  0  2  1  0  1  0  0  0  0  1  0  1  1  1
  0  0  2  1  0  1  0  0  0  0  1  0  1  1  1
  0  0  2  1  0  1  0  0  0  0  1  0  1  1  1
  0  0  2  1  0  1  0  0  0  0  1  0  1  1  1
  1  1  1  1  2  1  0  0  0  0  1  0  1  1  1
  0  0  0  0  0  0  3  3  3  3  0  3  0  0  0
  0  0  0  0  0  0  3  3  3  3  0  3  0  0  0
  0  0  0  0  0  0  3  3  3  3  0  3  0  0  0
  0  0  0  0  0  0  3  3  3  3  0  3  0  0  0
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


void read_grammar(char& start, vector<char>& N, vector<char>&T, vector<pair<char,pair<string, int> > >& productions,vector<int>& goal_items);
void read_actions( vector<string>& actions );
void read_SMG_table( vector<vector<int>>& table );

// here 
void read_LL_table( map<pair<char,char>,int> & table );
void LL_translation(string str,char start, map<pair<char,char>,int>& table, vector<pair<char,string>>& productions, vector<char>& N, int item_size, vector<int>& ans);

template< typename Type >
void show( vector<char>&N, vector<char>& T, vector<vector<Type>>& arr);

void SMG_translate(string str,char start, vector<vector<int>>& table, map<char,int>& m, vector<pair<char,pair<string, int> >>& translation_rules, vector<int>& ans);

int main(){
	char start ;
	vector<char> N ; vector<char> T ;
	vector<pair<char,pair<string, int> > > translation_rules ; // using map is ok
	//map<char,string> productions_map ; //map<int,char> productions_order ;
	vector<int> goal_items ;
	read_grammar(start,N,T,translation_rules, goal_items);

	vector<string> goal_actions ;
	read_actions( goal_actions );

	vector<vector<int>> table ;
	read_SMG_table( table );

	string str; 
	cin >> str ;
//	cout << str << endl ;

	map<char,int> m;
	for( int i = 0 ; i < N.size()+T.size() ; i ++ ){
		if ( i < N.size() )
			m[N[i]] = i ;
		else{
			m[ T[i-N.size()] ] = i ;
		}
	}
	for( int i = 0 ; i < N.size() ;i++ ){
		cout << m[ N[i] ] << " ";
	}
	cout << endl ;
	for( int i = 0 ; i < T.size() ;i++ ){
		cout << m[ T[i] ] << " ";
	}
	cout << endl ;

	show( N, T, table) ;
	cout << m['x'] << endl ;
	cout << m['+'] << endl ;
	cout << table[ m['x']] [m['+']] << endl ;
	vector<int> ans ;
	SMG_translate(str, start, table,m, translation_rules, ans );
	//LR_analysis(str, table, m, productions, start);
	for( int i = 0 ; i < ans.size() ; i++ ){
		if( ans[i] != 0 ){
			cout << goal_actions[ ans[i]-1 ] << " " ;
		}
	}
	cout << endl ;

	return 0 ;
}

/*
read the grammar info from the cmd
store it in the data stracture
*/
void read_grammar(char& start, vector<char>& N, vector<char>&T, vector<pair<char,pair<string, int>>>& productions,vector<int>& goal_items ){
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
	int a_num , temp1 ;
	cin >> a_num ;
	for( int i = 0 ; i < a_num ; i ++ ){
		cin >> temp1 ;
		goal_items.push_back( temp1 );
	}
	cin >> P_num ;
	int num ; char left ; string right_str ; int goal_item ;
	for( int i = 0 ; i < P_num ; i ++ ){
		cin >> num >> left >> right_str >> goal_item ;
		productions.push_back( make_pair(left, make_pair(right_str, goal_item)));
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
simple prior grammer
*/
void read_SMG_table( vector<vector<int>>& table ){
	int size ;
	cin >> size ;
	for( int i = 0 ; i < size ; i ++ ){
		vector<int> temp ;
		for( int j = 0 ; j < size; j++ )
			temp.push_back( 0 );
		table.push_back( temp );
	}

	int temp ;
	for( int i = 0 ; i < size ; i ++ ){
		for( int j = 0 ; j < size ; j++ ){
			cin >> temp ;
			table[i][j] = temp ;
		}
	}
	return ;
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
function for SMG
*/
void match(vector<char>& symble_q, int& index,vector<pair<char,pair<string, int> >>& translation_rules, vector<int>& ans ){
	string str = "" ;
	for( int i = index; i < symble_q.size() ; i++ )
		str += symble_q[i] ;
	for( int i = 0 ; i < translation_rules.size() ; i++ ){
		if( translation_rules[i].second.first == str ){
			for( int count = symble_q.size()-1 ; count >= index ; count -- ){
				symble_q.pop_back() ;
			}
			symble_q.push_back( translation_rules[i].first );
			if ( translation_rules[i].second.second != 0)
				ans.push_back( translation_rules[i].second.second );
			return ;
		}
	}
	cout << "No matching!" << endl; 
}
/*
translate using SMG
(0错误；1小于；2等于；3大于)
*/
void SMG_translate(string str,char start, vector<vector<int>>& table, map<char,int>& m, vector<pair<char,pair<string, int> >>& translation_rules, vector<int>& ans){
	vector<char> symble_q ;
	symble_q.push_back('#') ;
	int index = 0 ;
	while( true ){
		if ( symble_q.size() == 2 && symble_q[1] == start && index==str.size()-1)
			return ; // successful end

		char top_symble = symble_q.back() ;
		char first_ch = str[index] ;
		if( top_symble =='#' ){ // <
			symble_q.push_back( first_ch ) ;
			index ++ ;
			continue ;
		}
		if( index == str.length()-1 ){ // > 
			int begin_index = symble_q.size()-1 ;
			while( begin_index > 0){
				if ( begin_index == 1 ){
					match(symble_q, begin_index, translation_rules, ans);
					break ;
				}
				int left = m[ symble_q[begin_index-1] ];
				int right = m[ symble_q[begin_index] ];
				if ( table[left][right] == 1 ){
					match(symble_q, begin_index, translation_rules, ans);
					break ;
				}
				begin_index -- ;
			}
			continue ;
		}
		int i = m[top_symble] , j = m[first_ch] ;
		if( table[i][j] != 3 ){ // the relation is == 
			symble_q.push_back( first_ch );
			index ++ ;
			continue ;
		}
		if( table[i][j]==3 ){
			int begin_index = symble_q.size()-1 ;
			while( begin_index > 0){
				if ( begin_index == 1 ){
					match(symble_q, begin_index, translation_rules, ans);
					break ;
				}
				int left = m[symble_q[begin_index-1] ];
				int right = m[symble_q[begin_index] ];
				if ( table[left][right] == 1 ){
					match(symble_q, begin_index, translation_rules, ans);
					break ;
				}
				begin_index -- ;
			}
		}
	}
}
