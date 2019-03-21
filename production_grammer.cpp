/*
Description
 输入开始符号，非终结符，终结符，产生式
按非终结符顺序输出产生式；
此题需要提交实验报告；实验报告用“学号+姓名+22”
Input
 输入开始符号；
非终结符个数，非终结符，空格符分隔；
终结符个数，终结符，空格符分隔；
产生式的个数，各产生式的左边和右边符号，空格符分隔；
Output
 G[开始符号]：
按非终结符顺序输出各产生式；
*/

/*
	char non[]= {'3','E','T','F'} ;
	vector<char> non_terminal(non, non+sizeof(non)/sizeof(char)) ;
	char t[] = {'7','+','-','*','/','(',')','i'} ;
	vector<char> terminal(t, t+sizeof(t)/sizeof(char)) ;	

	char start = 'E' ;
	map<char,string> production ;
*/

/*
nonterminal : vector<char>
terminal : vector<char>
production : map
start : char
*/
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std ;

void display( vector<char> non_terminal , map<char,string> production , char start );
int main(){
	char start ;
	vector<char> non_terminal , terminal ;	
	map<char,string> production ;
	int count = 0 ;

	cin >> start ;
	// input start\ terminal \ Non terminal and products.
	char zifu ;
	cin >> count ;
	while( count -- ){
		cin >> zifu ;
		non_terminal.push_back(zifu) ;
	}
	cin >> count ;
	while( count -- ){
		cin >> zifu ;
		terminal.push_back(zifu) ;
	}

	char left ; string right ;
	cin >> count ;
	for ( count-- ){ // the products are organized here.
		cin >> left >> right ;
		if ( production.count(left) == 0 ) // not exist
			production[left] = right ;
		else {
			right = " | "+right ;
			production[left] += right ;  
		}		
	}
	display( non_terminal , production , start ) ;
	return 0 ;
}


void display( vector<char> non_terminal , map<char,string> production, char start ){
	cout << "G["<< start <<"]:" << endl ;
	char key ;
	for ( int i = 0 ; i < non_terminal.size() ; i ++ ){
		key = non_terminal[i] ;
		if ( production[key] != "" )
			cout << key << "::=" << production[key] << endl ;
	}
	return ;
}
