/*
在计算FIRST、LAST的基础上
使用简单优先分析方法对简单优先文法进行处理。
本文件通过产生式生成优先关系表

Description
 简单优先算术表达式G[E]: 
E→E+T | E-T | A
A→T
T→F*T | F/T | F
F→(B) | D
B→E
D→x | y | z
输入开始符号，非终结符，终结符，产生式
输出G[E]: 简单优先算术表达式优先分析表

Input
 输入开始符号；
非终结符个数，非终结符，空格符分隔；
终结符个数，终结符，空格符分隔；
产生式的个数，各产生式的序号，产生式的左边和右边符号，空格符分隔；

Output
 第一行：关系提示
空格，按非终结符和终结符顺序输出，每个符号占3格；
非终结符或终结符号，关系0或1，每个符号占3格；
 
分别输出EQUAL=,LEQUAL=,GEQUAL=,M[R]=;
前3个表1表示有关系，后一个关系有输出关系，没有输出空格；

样例：
input:
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

output :
EQUAL=
     E  A  T  F  B  D  +  -  *  /  (  )  x  y  z
  E  0  0  0  0  0  0  1  1  0  0  0  0  0  0  0
  A  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  T  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  F  0  0  0  0  0  0  0  0  1  1  0  0  0  0  0
  B  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0
  D  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  +  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0
  -  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0
  *  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0
  /  0  0  1  0  0  0  0  0  0  0  0  0  0  0  0
  (  0  0  0  0  1  0  0  0  0  0  0  0  0  0  0
  )  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  x  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  y  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  z  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
LEQUAL=
     E  A  T  F  B  D  +  -  *  /  (  )  x  y  z
  E  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  A  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  T  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  F  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  B  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  D  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  +  0  0  0  1  0  1  0  0  0  0  1  0  1  1  1
  -  0  0  0  1  0  1  0  0  0  0  1  0  1  1  1
  *  0  0  0  1  0  1  0  0  0  0  1  0  1  1  1
  /  0  0  0  1  0  1  0  0  0  0  1  0  1  1  1
  (  1  1  1  1  0  1  0  0  0  0  1  0  1  1  1
  )  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  x  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  y  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  z  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
GEQUAL=
     E  A  T  F  B  D  +  -  *  /  (  )  x  y  z
  E  0  0  0  0  0  0  0  0  0  0  0  1  0  0  0
  A  0  0  0  0  0  0  1  1  0  0  0  1  0  0  0
  T  0  0  0  0  0  0  1  1  0  0  0  1  0  0  0
  F  0  0  0  0  0  0  1  1  0  0  0  1  0  0  0
  B  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  D  0  0  0  0  0  0  1  1  1  1  0  1  0  0  0
  +  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  -  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  *  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  /  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  (  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0
  )  0  0  0  0  0  0  1  1  1  1  0  1  0  0  0
  x  0  0  0  0  0  0  1  1  1  1  0  1  0  0  0
  y  0  0  0  0  0  0  1  1  1  1  0  1  0  0  0
  z  0  0  0  0  0  0  1  1  1  1  0  1  0  0  0
M[R]=
     E  A  T  F  B  D  +  -  *  /  (  )  x  y  z
  E                    =  =           >         
  A                    >  >           >         
  T                    >  >           >         
  F                    >  >  =  =     >         
  B                                   =         
  D                    >  >  >  >     >         
  +        =  <     <              <     <  <  <
  -        =  <     <              <     <  <  <
  *        =  <     <              <     <  <  <
  /        =  <     <              <     <  <  <
  (  <  <  <  <  =  <              <     <  <  <
  )                    >  >  >  >     >         
  x                    >  >  >  >     >         
  y                    >  >  >  >     >         
  z                    >  >  >  >     >         
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
void get_equal_relation(vector<char>& N, vector<char>&T, vector<pair<char,string> >& productions,vector<vector<int> >&equal);
void calculate_lequal( vector<vector<int>>&lequal, vector<vector<int>>&equal, vector<vector<int>>&first);
void calculate_gequal(vector<vector<int>>&gequal, vector<vector<int>>&equal, vector<vector<int>>&first, vector<vector<int>>&last );
void get_M( vector<vector<char>>&M, vector<vector<int>>&equal, vector<vector<int>>&lequal, vector<vector<int>>&gequal );

template< typename Type >
void show( vector<char>&N, vector<char>& T, vector<vector<Type>>& arr);

int main(){
	char start ;
	vector<char> N ; vector<char> T ;
	vector<pair<char,string> > productions ; // using map is ok
	//map<char,string> productions_map ; //map<int,char> productions_order ;

	read_grammar(start,N,T,productions);
	
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
