#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype>

using namespace std ;

struct { int number; string str[10]; } keywords={3,"int","main","return"} ; //�ؼ���
struct { int number; string str[10]; } operators ={5,"+","*","=","+=","*="}; //�����
struct { int number; string str[10]; } boundaries ={6,"(",")","{","}",",",";"} ; //�ֽ��
struct { int number; string str[100];} identifieres={0}; //��ʶ��
struct { int number; string str[100];} Unsigned_integer={0}; //�޷�������

struct Inter_symbol{
	int type ;
	int value ;
};

void initiate_table( map<string,pair<int,int> >& table );
void update( string str, map<string,pair<int,int> >& table, vector<pair<int,int> >& ans);
pair<int,int> identifier( string str, int& i, map<string,pair<int,int> >& table);
pair<int,int> digit(string str, int& i, map<string,pair<int,int> >& table);
bool isoperator( char temp );
pair<int,int> operator_(string str, int& i, map<string,pair<int,int> >& table);
bool isboundary( char temp );
bool not_finish( string str );

void show( vector<pair<int,int> >& ans );


int main(){
	map<string,pair<int,int> > table ;
	initiate_table( table );

	vector<pair<int,int> > ans ;
	string str ; // read message
	do {
		cin >> str ;
		update( str, table, ans );
	}while ( not_finish(str) );
	show( ans );
}

void initiate_table( map<string,pair<int,int> >& table ){
	for( int i = 0 ; i < keywords.number ; i ++ )
		table[ keywords.str[i]] = make_pair(1,i) ;
	for( int i = 0 ; i < operators.number ; i ++ )
		table[ operators.str[i]] = make_pair(2,i) ;
	for( int i = 0 ; i < boundaries.number ; i ++ )
		table[ boundaries.str[i]] = make_pair(3,i) ;
}

void update( string str, map<string,pair<int,int> >& table, vector<pair<int,int> >& ans){
	int length = str.length() ;
	if ( ! not_finish(str) ) length -- ;
	for ( int i = 0 ; i < length ; ){
		char temp = str[i] ;
		pair<int,int> id;
		if( isalpha(temp) ){
			id = identifier(str, i, table );
		}
		if( isdigit(temp) ){
			id = digit(str, i, table);
		}
		if ( isoperator(temp)){
			id = operator_(str, i, table);
		}
		if ( isboundary(temp) ){
			string boundary = "";
			boundary += temp ;
			id = table[boundary] ;// may be not exits.
			i ++ ;
		}
		ans.push_back( id ); 
	}
}
pair<int,int> identifier( string str, int& i, map<string,pair<int,int> >& table){
	string var = "";
	var += str[i++] ;
	while( i < str.length() && (isalpha(str[i])||isdigit(str[i])||str[i]=='_') ){
		var += str[i++] ;
	}
	if ( !table.count(var) ){ // new identifier
		identifieres.str[identifieres.number] = var ; // suppose 100 is enough
		table[var] = make_pair(4,identifieres.number++);
	}// or keywords
	return table[var] ;
}

pair<int,int> digit(string str, int& i, map<string,pair<int,int> >& table){
	string var = "";
	while( isdigit(str[i])){
		var += str[i++];
	}
	if ( !table.count(var) ){
		Unsigned_integer.str[Unsigned_integer.number] = var ;
		table[var] = make_pair(5, Unsigned_integer.number++);
	}
	return table[var] ;
}

bool isoperator( char temp ){
	if ( temp=='+'|| temp=='*'|| temp=='-'|| temp=='/'|| temp=='=')
		return true ;
	return false ;
}
bool isboundary( char temp){
	if ( temp=='('|| temp==')'|| temp=='{'|| temp=='}'|| temp==','|| temp==';')
		return true;
	return false;
}

pair<int,int> operator_(string str, int& i, map<string,pair<int,int> >& table){
	string op = "";
	if ( str[i]=='='){
		op += str[i++];
		return table[op];
	}
	while( isoperator(str[i])){
		op += str[i++] ;
	}
	return table[op] ;
}

bool not_finish( string str){
	return !(str[str.length()-1] == '#') ;
}
void show( vector<pair<int,int> >& ans ){
	for( int i =0; i < ans.size() ; i ++ ){
		cout << "<"<<ans[i].first << "," << ans[i].second << ">" ;
	}
	cout << endl ;
	cout << "identifieres:";
	for( int i=0; i<identifieres.number; i++)
		cout << identifieres.str[i] << " ";
	cout << endl;
	cout << "Unsigned_integer:" ;
	for( int i=0; i<Unsigned_integer.number; i++)
		cout << Unsigned_integer.str[i] << " ";
	cout << endl;	
}
