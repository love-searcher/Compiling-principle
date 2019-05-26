/*
Description
 输入开始符号，非终结符，终结符，语意动作表，产生式
输出简单优先法的语意处理动作
以拓广算术表达式G[A]: 为例
A→E
E→E+T | T
T→T*F | F
F→(E) | a

Input
 输入开始符号；
非终结符个数，非终结符，空格符分隔；
终结符个数，终结符，空格符分隔；
语意动作个数，语意动作符，空格符分隔；
产生式的个数，各产生式的序号，产生式的左边和右边符号源产生式，目标产生式，空格符分隔；
状态数，ACTION列数，GOTO列数，空格符分隔；
状态，ACTION矩阵(k 0 表示空 A 0 表示接收)，GOTO矩阵(0表示 空)，空格符分隔；
输入分析字符串，#结束

Output
输出分析过程；
语意动作符序列；用空格隔开，第一个动作前有一空格。

Sample Input Copy
A
4  E T F A
6  a +  * ( ) #
3  1 2 3
7
0  A E     0
1  E E+T   1
2  E T     0
3  T T*F   2
4  T F     0
5  F (E)   0
6  F a     3

3
1 ADD
2 MUL
3 x

12 6 3
0  s 5  k 0  k 0  s 4  k 0  k 0  1 2 3
1  k 0  s 6  k 0  k 0  k 0  A 0  0 0 0
2  k 0  r 2  s 7  k 0  r 2  r 2  0 0 0
3  k 0  r 4  r 4  k 0  r 4  r 4  0 0 0
4  s 5  k 0  k 0  s 4  k 0  k 0  8 2 3
5  k 0  r 6  r 6  k 0  r 6  r 6  0 0 0
6  s 5  k 0  k 0  s 4  k 0  k 0  0 9 3
7  s 5  k 0  k 0  s 4  k 0  k 0  0 0 10
8  k 0  s 6  k 0  k 0  s 11 k 0  0 0 0
9  k 0  r 1  s 7  k 0  r 1  r 1  0 0 0
10 k 0  r 3  r 3  k 0  r 3  r 3  0 0 0
11 k 0  r 5  r 5  k 0  r 5  r 5  0 0 0

(a+a)*a#
Sample Output Copy
 x x ADD x MUL 
*/
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <queue>

using namespace std ;


void read_grammar(char& start, vector<char>& N, vector<char>&T, vector<pair<char,pair<string,int> > >& productions,vector<int>& goal_item);
void read_actions( vector<string>& actions ) ;

// here 
void read_LR_table( vector<vector<pair<char,int> >>& table );
void LR_analysis(string str,vector<vector<pair<char,int> >>& table,map<char,int>& m,vector<pair<char,pair<string,int>>>& productions,char start,vector<int>& ans );

int main(){
	char start ;
	vector<char> N ; vector<char> T ;
	vector<pair<char,pair<string,int> > > translations ; // using map is ok
	//map<char,string> productions_map ; //map<int,char> productions_order ;
	vector<int> goal_item ;

	read_grammar(start,N,T,translations,goal_item);

	vector<string> actions ;
	read_actions( actions );


	vector<vector<pair<char,int> >> table ;
	read_LR_table( table );
/*
	for( int i = 0 ; i < table.size() ; i ++ ){
		for ( int j = 0 ; j < table[i].size() ; j ++ ){
			cout << table[i][j].first << table[i][j].second << " " ;
		}
		cout << endl ;
	}
*/
	string str; 
	cin >> str ;
//	cout << str << endl ;

	map<char,int> m;
	for( int i = 0 ; i < N.size()+T.size() ; i ++ ){
		if ( i < T.size() )
			m[T[i]] = i ;
		else{
			m[ N[i-T.size()] ] = i ;
		}
	}
	vector<int> ans ;
	LR_analysis(str, table, m, translations, start, ans);

	for( int i = 0 ; i < ans.size() ; i ++ ){
		if ( ans[i] )
			cout << actions[ans[i]-1] << " ";
	}
	cout << endl ;
	return 0 ;
}

/*
read the grammar info from the cmd
store it in the data stracture
*/
void read_grammar(char& start, vector<char>& N, vector<char>&T, vector<pair<char,pair<string,int> > >& productions, vector<int>& goal_item){
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
	int A_num ;	int action_num ;
	cin >> A_num ;
	for( int i = 0 ; i < A_num ; i ++ ){
		cin >> action_num ;
		goal_item.push_back( action_num );
	}

	cin >> P_num ;
	int num ; char left ; string right_str ;
	for( int i = 0 ; i < P_num ; i ++ ){
		cin >> num >> left >> right_str >> action_num ;
		productions.push_back( make_pair(left, make_pair(right_str,action_num) ) );
	}
	return ;
}

void read_actions( vector<string>& actions ){
	int num ; int temp ; string str ;
	cin >> num ;
	for( int i = 0 ; i < num ; i ++ ){
		cin >> temp >> str ;
		actions.push_back( str );
	}
}

/*
read the LR table
*/
void read_LR_table( vector<vector<pair<char,int> >>& table ){
	int height, w1 , w2;
	cin >> height >> w1 >> w2 ;
	int width = w1+w2 ;
	for( int i = 0 ; i < height ; i ++ ){
		vector<pair<char,int>> temp ;
		int index; char temp_ch; int temp_int; 
		cin >> index ;
		for( int j = 0 ; j < w1 ; j ++ ){
			cin >> temp_ch >> temp_int ;
			temp.push_back( make_pair(temp_ch,temp_int));
		}
		for( int j = 0 ; j < w2 ; j ++ ){
			cin >> temp_int ;
			temp.push_back( make_pair(' ', temp_int));
		}
		table.push_back( temp );
	}
	return ;
}

void display( vector<int>& state_q, vector<char>& char_q, string str, int index){
	cout << "#" ;
	for( int i = 0 ; i < state_q.size()-1 ; i ++ ){
		cout << state_q[i] << char_q[i] ;
	}
	cout << state_q.back() << " & " ;
	for( int i = index ; i < str.length() ; i ++ ){
		cout << str[i] ;
	}
	cout << endl ;
	return ;
}
void LR_analysis(string str,vector<vector<pair<char,int> >>& table,map<char,int>& m,vector<pair<char,pair<string,int>>>& productions,char start,vector<int>& ans ){
	vector<char> char_q ;
	vector<int> state_q;

	state_q.push_back( 0 ) ;
	for( int i = 0 ; i < str.length() ; i++ ){
		// display
		//display(state_q , char_q, str, i );
		int state = state_q.back();

		char ch = str[i] ; // the input char
		int action = m[ch] ;  // the index of the table for the char
		if( table[state][action].first == 's'){
			char_q.push_back( ch );
			state_q.push_back( table[state][action].second );
			continue ;
		}
		if ( table[state][action].first == 'r'){			
			char left = productions[ table[state][action].second ].first ;
			int index = m[left] ;			
			string right = productions[ table[state][action].second ].second.first ;
			ans.push_back( productions[ table[state][action].second ].second.second );

			for ( int j = 0 ; j < right.length() ; j++ ){
				state_q.pop_back() ;
				char_q.pop_back() ;
			}
			state = state_q.back() ;// guiyue
			char_q.push_back( left );
			int c = table[state][index].second ;
			state_q.push_back( table[state][index].second );
			i -- ;

			continue ;
		}
		if ( table[state][action].first == 'k' ){
			cout << "ERROR INPUT" << endl ;
			return ;
		}
	}
}
