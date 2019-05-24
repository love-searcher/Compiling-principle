/*
Description
 输入文法，输出其项目集

Input
 输入文法的开始符号

输入非终结符个数 ，非终结符系列

输入终结符个数 ， 终结符系列

输入产生式个数 ， 产生式序号  产生式左右系列

Output
 项目序号   产生式序号   小数点位置  产生式左右部分

注：前4宽带3格，最后一个后换行

Sample Input Copy
A
4  E T F A
6  a +  * ( ) #
7
0  A E
1  E E+T
2  E T
3  T T*F
4  T F
5  F (E)
6  F a
Sample Output Copy
  1  1  0  A   E
  2  1  1  A   E
  3  2  0  E   E+T
  4  2  1  E   E+T
  5  2  2  E   E+T
  6  2  3  E   E+T
  7  3  0  E   T
  8  3  1  E   T
  9  4  0  T   T*F
 10  4  1  T   T*F
 11  4  2  T   T*F
 12  4  3  T   T*F
 13  5  0  T   F
 14  5  1  T   F
 15  6  0  F   (E)
 16  6  1  F   (E)
 17  6  2  F   (E)
 18  6  3  F   (E)
 19  7  0  F   a
 20  7  1  F   a
*/
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <queue>

using namespace std ;


void read_grammar(char& start, vector<char>& N, vector<char>&T, vector<pair<char,string> >& productions);

int main(){
	char start ;
	vector<char> N ; vector<char> T ;
	vector<pair<char,string> > productions ; // using map is ok
	//map<char,string> productions_map ; //map<int,char> productions_order ;

	read_grammar(start,N,T,productions );

	//item_set generate_item_set(start, N, T, productions);
	int count = 1 ;
	for ( int i = 0 ; i < productions.size() ; i ++ ){
		for( int j = 0 ; j <= productions[i].second.size() ; j++ ){
			cout << setw(3) << count << setw(3) << (i+1) 
				 << setw(3) << j << setw(3) << productions[i].first 
				 << "   " << productions[i].second << endl ;
			count ++ ;
		}
	}
	return 0 ;
}

/*
read the grammar info from the cmd
store it in the data stracture
*/
void read_grammar(char& start, vector<char>& N, vector<char>&T, vector<pair<char,string> >& productions ){
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
