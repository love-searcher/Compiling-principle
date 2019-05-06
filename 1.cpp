/*
Description
 输入若干个字符串，每个字符串为一个集合，按字符串出现的先后顺序输出升序字符串集合；相同的集合只取一个。
此题需要提交实验报告；实验报告用“学号+姓名+12”
Input
 字符串个数    所有字符串，用分隔符分隔
Output
 输出升序字符串集合，用换行符分割，最后一行有换行符。
Sample input
 5
acbd     aabc
aacb    abcd   a1c
Sample output
abcd
abc
1ac
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std ;

string get_char_set( string input_str ) ;//return the char set of input string
bool in_arr(char chr , vector<char> arr ); // if chr in arr
bool in_arr(string chr , vector<string> arr ); // if str already in arr

int main(){
	vector<string> str_arr ;

	string input_str ;
	int count = 0 ;
	cin >> count ;
	for ( int i = 0 ; i < count ; i ++ ){
		cin >> input_str ;
		string out = get_char_set(input_str);
		if ( in_arr(out, str_arr )){ //the char set(out) is already stored in str_arr
			continue ;
		}else {
			str_arr.push_back(out) ;
		}
	}
	//output in the original order
	for ( int i = 0 ; i < str_arr.size()-1 ; i ++ )
		cout << str_arr[i] << endl ;
	cout << str_arr[str_arr.size()-1] ;
	return 0 ;
}


string get_char_set(string input_str){
	vector<char> arr ;
	
	for( int i = 0 ; i < input_str.length() ; i ++){
		if (in_arr(input_str[i], arr)){
			continue ;
		}else {
			arr.push_back(input_str[i]);
		}
	}
	
	sort(arr.begin() , arr.end() ); //sort the char set
	string str(arr.begin(), arr.end()); // change the char set array into a string object
	return str;
}

// judge if chr already in arr.
bool in_arr(char chr , vector<char> arr ){
	for( int i = 0 ; i < arr.size() ; i ++ ){
		if (arr[i] == chr ) 
			return true ;
	}
	return false;
}
bool in_arr(string str , vector<string> arr ){
	for ( int i = 0 ; i < arr.size() ; i ++ ){
		if ( str == arr[i] )
			return true ;
	}
	return false;
}

