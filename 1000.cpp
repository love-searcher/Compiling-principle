#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

using namespace std ;

string get_char_set( string input_str ) ;
bool in_arr(char chr , vector<char> arr );
bool in_arr(string chr , vector<string> arr );

int main(){
	vector<string> str_arr ;

	string input_str ;
	int count = 0 ;
	cin >> count ;
	for ( int i = 0 ; i < count ; i ++ ){
		cin >> input_str ;
		string out = get_char_set(input_str);
		if ( in_arr(out, str_arr )){
			continue ;
		}else {
			str_arr.push_back(out) ;
		}
	}
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
	
	sort(arr.begin() , arr.end() );
	string str(arr.begin(), arr.end());
	return str;
}
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

