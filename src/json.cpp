#include <regex>
#include "global.h"

void JSONObject::parse(string str){
	JSONObject temp;
	str = trim(str);
	setType(str);
	switch(type){
		case JSON_OBJECT:
			parseObject(str);
			break;
		case JSON_ARRAY:
			parseArray(str);
			break;
		case JSON_STRING:
			stringVal = str;
			break;
		case JSON_NUMBER:
			numberVal = stoi(str);
			break;
		case JSON_ERROR:
			stringVal = str;
			break;
	}
}

void JSONObject::setType(string str){
	type=JSON_ERROR;
	//regex test = regex("^\\{.*:.*\\}$");
	if ( regex_match( str, regex("^\\{.*:.*\\}$") ) ){
		type=JSON_OBJECT;
		cout << "it is an object" << endl;
		return;
	}
	if ( regex_match(str,regex("^\\[.*\\]$"))){
		type=JSON_ARRAY;
		cout << "it is an array" << endl;
		return;
	}
	if ( regex_match(str,regex("^'.*'$"))){
		type=JSON_STRING;
		cout << "it is a string" << endl;
		return;
	}
	if ( is_number(str)){
		type=JSON_NUMBER;
		cout << "it is a number" << endl;
		return;
	}
	cout << "it is unknown, and therefore treated as a string" << endl;
	return;
}

bool JSONObject::is_number(const string &s){
    return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

void JSONObject::parseObject( string str ){
	vector<string> parts = split(str,',');
	cout << "Object parsed, with " << parts.size() << " properties." << endl;
	for ( int i = 0; i < parts.size(); i++ ){
		vector<string> obj = split(parts[i],':');
		if (obj.size()==2){
			JSONObject temp;
			temp.parse(obj[1]);
			objectVal[ obj[0] ] = temp;
		} 
	}
}

void JSONObject::parseArray( string str ){
	vector<string> parts = split(str,',');
	cout << "Array parsed, containing " << parts.size() << " objects." << endl;
	for ( int i = 0; i < parts.size(); i++){
		JSONObject temp;
		temp.parse(parts[i]);
		arrayVal.push_back(temp);
	}
}

//splits on anything, for JSON specific
vector<string> JSONObject::split( string str, char find ){
	vector<string> output;
	string buf = "";
	bool qLocked=false;//double quotes
	bool sLocked=false;//single quotes
	int cLocked=0;//curly braces
	int pLocked=0;//parenthesis
	int bLocked=0;//brackets

	for ( int i = 1; i < str.length()-1; i++ ){
		if ( 	str[i]==find && 
				!sLocked &&
				!qLocked &&
				cLocked == 0 &&
				pLocked == 0 &&
				bLocked == 0
		){
			output.push_back(trim(buf));
			buf="";
		} else{
			switch(str[i]){
				case '"': qLocked = (qLocked) ? false : true; break;
				case '\'': sLocked = (sLocked) ? false : true; break;
				case '(': pLocked++; break;
				case ')': pLocked--; break;
				case '[': bLocked++; break;
				case ']': bLocked--; break;
				case '{': cLocked++; break;
				case '}': cLocked--; break;
			}
			buf+=str[i];
		}
	}
	if (buf.length() > 0) {
		output.push_back(buf);
	}
	return output;
}

string JSONObject::trim( string str ){
	string spaces = " \f\n\r\t\v";
	int lTrim = str.find_first_not_of(spaces);
	if (lTrim != string::npos ){
		str = str.substr( lTrim );	
	}
	int rTrim = str.find_last_not_of(spaces);
	if (rTrim != string::npos ){
		str = str.substr( 0, rTrim + 1);
	}
	return str;
}

string JSONObject::stringify(){
	string str = "";
	switch(type){
		case JSON_ARRAY:
			str += "[";
			for ( int i = 0; i < arrayVal.size(); i++ ){
				str+=arrayVal[i].stringify();
				str+=",";
			}
			str = str.substr(0,str.length()-1);
			str += "]";
			break;
		case JSON_OBJECT:
			str += "{";
			for ( auto it : objectVal ){
				str+="'"+it.first+"'";
				str+=":";
				str+=it.second.stringify();
				str+=",";
			}
			str = str.substr(0,str.length()-1);
			str += "}";
			break;
		case JSON_ERROR:
			str = stringVal;
			break;
		case JSON_STRING:
			str = "'" + stringVal + "'";
			break;
		case JSON_NUMBER:
			str = to_string(numberVal);
			break;
	}
	return str;
}