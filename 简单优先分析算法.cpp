/*
已有简单优先关系表的情况下，对简单优先语法进行分析。
// 主要算法部分需要改进

Description
 输入开始符号，非终结符，终结符，产生式
输出简单优先分析过程


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
产生式的个数，各产生式的序号，产生式的左边和右边符号，空格符分隔；
简单优先分析表方阵的行列数，简单优先分析表，空格符分隔；(0错误；1小于；2等于；3大于)
输入分析字符串，#结束

Output
 输出分析过程；
用“ $ ”分隔，左边表示栈底到栈顶符号；右边表示尚未分析的字符串。

Sample Input Copy
E
6  E A T F B D
9 + -  * / ( ) x y z 
13
1  E E+T
2  E E-T
3  E A
4  A T
5  T F*T
6  T F/T
7  T F
8  F (B)
9  F D
10 B E
11 D x
12 D y
13 D z
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
# & (x+(y-x*z)*(y+x*z))+x/z#
#( & x+(y-x*z)*(y+x*z))+x/z#
#(x & +(y-x*z)*(y+x*z))+x/z#
#(D & +(y-x*z)*(y+x*z))+x/z#
#(F & +(y-x*z)*(y+x*z))+x/z#
#(T & +(y-x*z)*(y+x*z))+x/z#
#(A & +(y-x*z)*(y+x*z))+x/z#
#(E & +(y-x*z)*(y+x*z))+x/z#
#(E+ & (y-x*z)*(y+x*z))+x/z#
#(E+( & y-x*z)*(y+x*z))+x/z#
#(E+(y & -x*z)*(y+x*z))+x/z#
#(E+(D & -x*z)*(y+x*z))+x/z#
#(E+(F & -x*z)*(y+x*z))+x/z#
#(E+(T & -x*z)*(y+x*z))+x/z#
#(E+(A & -x*z)*(y+x*z))+x/z#
#(E+(E & -x*z)*(y+x*z))+x/z#
#(E+(E- & x*z)*(y+x*z))+x/z#
#(E+(E-x & *z)*(y+x*z))+x/z#
#(E+(E-D & *z)*(y+x*z))+x/z#
#(E+(E-F & *z)*(y+x*z))+x/z#
#(E+(E-F* & z)*(y+x*z))+x/z#
#(E+(E-F*z & )*(y+x*z))+x/z#
#(E+(E-F*D & )*(y+x*z))+x/z#
#(E+(E-F*F & )*(y+x*z))+x/z#
#(E+(E-F*T & )*(y+x*z))+x/z#
#(E+(E-T & )*(y+x*z))+x/z#
#(E+(E & )*(y+x*z))+x/z#
#(E+(B & )*(y+x*z))+x/z#
#(E+(B) & *(y+x*z))+x/z#
#(E+F & *(y+x*z))+x/z#
#(E+F* & (y+x*z))+x/z#
#(E+F*( & y+x*z))+x/z#
#(E+F*(y & +x*z))+x/z#
#(E+F*(D & +x*z))+x/z#
#(E+F*(F & +x*z))+x/z#
#(E+F*(T & +x*z))+x/z#
#(E+F*(A & +x*z))+x/z#
#(E+F*(E & +x*z))+x/z#
#(E+F*(E+ & x*z))+x/z#
#(E+F*(E+x & *z))+x/z#
#(E+F*(E+D & *z))+x/z#
#(E+F*(E+F & *z))+x/z#
#(E+F*(E+F* & z))+x/z#
#(E+F*(E+F*z & ))+x/z#
#(E+F*(E+F*D & ))+x/z#
#(E+F*(E+F*F & ))+x/z#
#(E+F*(E+F*T & ))+x/z#
#(E+F*(E+T & ))+x/z#
#(E+F*(E & ))+x/z#
#(E+F*(B & ))+x/z#
#(E+F*(B) & )+x/z#
#(E+F*F & )+x/z#
#(E+F*T & )+x/z#
#(E+T & )+x/z#
#(E & )+x/z#
#(B & )+x/z#
#(B) & +x/z#
#F & +x/z#
#T & +x/z#
#A & +x/z#
#E & +x/z#
#E+ & x/z#
#E+x & /z#
#E+D & /z#
#E+F & /z#
#E+F/ & z#
#E+F/z & #
#E+F/D & #
#E+F/F & #
#E+F/T & #
#E+T & #
#E & #
*/

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <string>
#include <queue>

using namespace std ;


void read_grammar(char& start, vector<char>& N, vector<char>&T, vector<pair<char,string> >& productions);
void read_relation_table( vector<vector<int>>& M ); 
void warshall(vector<vector<int> >& data);
void get_first_last(vector<char>& N, vector<char>&T, vector<pair<char,string> >& productions,vector<vector<int> >&FIRST,vector<vector<int> >&SECOND);
void get_equal_relation(vector<char>& N, vector<char>&T, vector<pair<char,string> >& productions,vector<vector<int> >&equal);
void calculate_lequal( vector<vector<int>>&lequal, vector<vector<int>>&equal, vector<vector<int>>&first);
void calculate_gequal(vector<vector<int>>&gequal, vector<vector<int>>&equal, vector<vector<int>>&first, vector<vector<int>>&last );
void get_M( vector<vector<char>>&M, vector<vector<int>>&equal, vector<vector<int>>&lequal, vector<vector<int>>&gequal );

template< typename Type >
void show( vector<char>&N, vector<char>& T, vector<vector<Type>>& arr);
bool analysis( string str,map<char,int>& m, vector<vector<int>>& M, vector<pair<char,string>>& productions, char start ); 

int main(){
	char start ;
	vector<char> N ; vector<char> T ;
	vector<pair<char,string> > productions ; // using map is ok	
	//map<char,string> productions_map ; //map<int,char> productions_order ;

	read_grammar(start,N,T,productions);
	// eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
	vector<vector<int>> M ; // analysis table; 
	read_relation_table( M );
	
	string str ; // 需要判别的字符串
	cin >> str ;
	show(N,T,M);
	 
	map<char,int> m ;
	for( int i = 0 ; i < N.size() ; i++){
		m[N[i]] = i ;
	}
	for( int i = 0 ; i < T.size() ; i ++){
		m[T[i]] = i+N.size() ;
	}
	analysis( str, m, M, productions, start ); //
/*	 
	vector<vector<int>> first; vector<vector<int>> last ;
	get_first_last(N, T, productions, first, last);
	warshall( first ); warshall( last) ;

	vector<vector<int>> equal ; vector<vector<int>> lequal; vector<vector<int>> gequal ;
	get_equal_relation(N,T,productions, equal );
	calculate_lequal( lequal, equal, first );
	calculate_gequal( gequal, equal, first, last );
	
	vector<vector<char>> M ;
	get_M( M, equal, lequal, gequal );
	
	cout << "EQUAL=" << endl ;
	show( N,T,equal);
	cout << "FIRST+=" << endl ;
	show( N,T,first);
	cout << "LEQUAL=" << endl; 
	show( N,T,lequal);
	cout << "GEQUAL=" << endl ;
	show( N,T,gequal);
	cout << "M[R]=" << endl ;
	show( N,T,M);
*/ 
	return 0 ;
}

void print( vector<char>& s, string str, int j ){
	for( int i = 0 ; i < s.size() ; i++ )
		cout << s[i] ;
	cout << " & " ;
	for( int i = j ; i < str.size() ; i ++ )
		cout << str[i] ;
	cout << endl ; 
	return ;
}

bool analysis( string str,map<char,int>& m, vector<vector<int>>& M, vector<pair<char,string>>& productions, char start ){
	vector<char> s ; // 符号栈 
	s.push_back( '#' ); // 默认 $ < 每一个， 且 每一个 > $ 
	int i=0 , j=0 ; 
	char left ; char right ;
	
	while( true ){
		left = s.back() ;
		right = str[j] ;
		print( s, str ,j );
		//zhongzhi
		if ( s.size() == 2 && s[1] == start && j==str.size()-1)
			return true ;

		if ( i != 0 && j < str.size()-1 && M[m[left]][m[right]] == 0 ) {
			cout << "ERROR" << endl ;
			return false ;
		}
		if ( i != 0 && M[m[left]][m[right]] == 3 || j==str.size()-1 ){ // 寻找前边首个>关系
			int k = i ;
			while( M[ m[s[k-1]] ][ m[s[k]] ] == 2){ // 相等关系 
				k -- ; 
			}
			//k++ ; // k is the end 

			string temp = "" ;
			for( int count = k ; count <= i ; count ++)
				temp += s[count] ;
			//cout << "句柄："<< temp << " 大小 " << temp.size() << endl ;
			// temp 是句柄
			// 判断 temp是否和某个产生式右边匹配
			int count ;
			for( count = 0 ; count < productions.size(); count ++ ){
				if ( productions[count].second == temp ){
					break ;
				}
			}
			if ( count < productions.size() ){ // 匹配成功 
				for( int c = i ; c >= k ; c -- ){
					s.pop_back() ;
				}
				s.push_back( productions[count].first );
				i = k ;
			}else{ // 不匹配 
				cout << " bu pi pei " << endl ;
				print( s, str , j );
				cout << temp << endl ;
				cout << "???" << endl ;
				if( s.back() == '#' && str[j] =='#' )
					return true ;
				else return false ;
			}
		}
		else{
			s.push_back( right );
			i ++ ;
			j ++ ;
		}
	}
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

void read_relation_table( vector<vector<int>> & M ){
	int size ;
	cin >> size ;
	for( int i = 0 ; i < size ; i ++ ){
		vector<int> temp ; int num ;
		for( int j = 0 ; j < size ; j ++ ){
			cin >> num ;
			temp.push_back( num );
		}
		M.push_back( temp );
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
	// 初始化映射，方便字符与index之间映射 
	map<char,int> m ;
	for( int i = 0 ; i < N.size() ; i++){
		m[N[i]] = i ;
	}
	for( int i = 0 ; i < T.size() ; i ++){
		m[T[i]] = i+N.size() ;
	}
	// 初始化 FIRST、LAST 
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
?????? 
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

// map 加 const 的区别是什么？？？？ 
void get_equal( map<char,int>& m , vector<pair<char,string>>& productions, vector<vector<int>>& equal){
	for( int i = 0; i < productions.size() ; i ++ ){
		string str = productions[i].second ;
		char left, right ; int a,b;
		for( int j = 0 ; j < str.size()-1 ; j ++){
			left = str[j]; right = str[j+1];
			a = m[left]; b = m[right] ;
			equal[a][b] = 1 ;
		} 
	}
	return ;
}
/*
寻找简单优先关系 equal
*/
void get_equal_relation(vector<char>& N, vector<char>&T, vector<pair<char,string> >& productions,vector<vector<int> >&equal ){
	// 初始化映射，方便字符与index之间映射 
	map<char,int> m ;
	for( int i = 0 ; i < N.size() ; i++){
		m[N[i]] = i ;
	}
	for( int i = 0 ; i < T.size() ; i ++){
		m[T[i]] = i+N.size() ;
	}
	// 初始化 FIRST、LAST //起始三者都为空(传入时) 
	for( int i = 0 ; i < T.size()+N.size(); i ++){
		vector<int> temp ;
		for( int j = 0 ; j < T.size()+N.size(); j++){
			temp.push_back( 0 );
		}
		equal.push_back( temp );
	}
	get_equal( m , productions , equal );
	return ;
}

/*
bool relation
*/
void matrix_multiply( vector<vector<int>>& dest, vector<vector<int>>& left, vector<vector<int>>& right){
	int size = dest.size() ;
	for( int i = 0 ; i < size ; i ++){
		for( int j = 0 ; j < size ; j ++ ){
			for( int k = 0 ; k < size ; k ++ )
				dest[i][j] |= (left[i][k]*right[k][j]) ; 
		} 
	}
	return ;
}
/*
简单优先关系的形式化构造方法 
三个都是 n*n的方阵 
矩阵乘法顺序 容易搞错 
*/
void calculate_lequal( vector<vector<int>>&lequal, vector<vector<int>>&equal, vector<vector<int>>&first){
	//初始化lequal
	int size = first.size() ;
	for( int i = 0 ; i < size ; i ++ ){
		vector<int> temp ;
		for( int j = 0 ; j < size ; j ++ )
			temp.push_back( 0 );
		lequal.push_back( temp );
	}
	// 矩阵乘法
	matrix_multiply( lequal, equal, first );
	return ; 
}

void calculate_gequal(vector<vector<int>>&gequal, vector<vector<int>>&equal, vector<vector<int>>&first, vector<vector<int>>&last ){
	vector<vector<int>> first_ ;
	vector<vector<int>> last_ ;
	vector<vector<int>> t ;
	//初始化lequal ,和 first_ , last_ 
	int size = first.size() ;
	for( int i = 0 ; i < size ; i ++ ){
		vector<int> temp ;
		for( int j = 0 ; j < size ; j ++ )
			temp.push_back( 0 );
		gequal.push_back( temp );
		first_.push_back( temp );
		last_.push_back( temp );
		t.push_back( temp );
	}
	// 计算 first* 和last的转置
	for( int i = 0 ; i < size ; i ++ ){
		for( int j = 0 ; j < size ; j ++ ){
			if( i == j ) {
				first_[i][j] = 1 ;
			}else{
				first_[i][j] = first[i][j] ;
			}
			last_[i][j] = last[j][i] ;
		}
	}
	matrix_multiply( t, last_ , equal );
	matrix_multiply( gequal, t, first_ ); // ?
}

/*
组建优先关系表 
*/
void get_M( vector<vector<char>>&M, vector<vector<int>>&equal, vector<vector<int>>&lequal, vector<vector<int>>&gequal ){
	// 初始化M
	int size = equal.size() ;
	for( int i = 0 ; i < size ; i++ ){
		vector<char> temp ; 
		for( int j = 0 ; j < size; j ++){
			temp.push_back( ' ' );
		}
		M.push_back( temp ); 
	}
	for( int i = 0 ; i < size ; i++ ){
		for( int j = 0 ; j < size ; j ++ ){
			if ( equal[i][j] ){
				M[i][j] = '=' ;
				continue ;
			}
			if ( lequal[i][j] ){
				M[i][j] = '<' ;
				continue ;
			}
			if ( gequal[i][j] ){
				M[i][j] = '>' ;
				continue ;
			}
		} 
	}
} 

template< typename Type >
void show( vector<char>&N, vector<char>& T, vector<vector<Type>>& arr){
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
