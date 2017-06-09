#include <regex>
#include "global.h"

void JSONObject::parse(string str){
	clear();
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
			str = removeEnclosure(str);
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
		return;
	}
	if ( regex_match(str,regex("^\\[.*\\]$"))){
		type=JSON_ARRAY;
		return;
	}
	if ( regex_match(str,regex("^'.*'$"))){
		type=JSON_STRING;
		return;
	}
	if ( regex_match(str,regex("^\".*\"$"))){
		type=JSON_STRING;
		return;
	}
	if ( is_number(str)){
		type=JSON_NUMBER;
		return;
	}
	return;
}

bool JSONObject::is_number(const string &s){
    return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

void JSONObject::parseObject( string str ){
	str = removeEnclosure(str);
	vector<string> parts = split(str,',');
	for ( int i = 0; i < parts.size(); i++ ){
		vector<string> obj = split(parts[i],':');
		if (obj.size()==2){
			string property = propertyName(obj[0]);
			JSONObject value;
			value.parse(obj[1]);
			objectVal[ property ] = value;
		} 
	}
}

void JSONObject::parseArray( string str ){
	str = removeEnclosure(str);
	vector<string> parts = split(str,',');
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

	for ( int i = 0; i < str.length(); i++ ){
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

string JSONObject::removeEnclosure(string str){
	string output;
	output = trim(str);
	output = output.substr(1,output.length()-2);
	output = trim(output);
	return output;
}

string JSONObject::propertyName(string str){
	string output = trim(str);
	if ( regex_match(str,regex("^'.*'$"))){
		output = removeEnclosure(str);
	}
	if ( regex_match(str,regex("^\".*\"$"))){
		output = removeEnclosure(str);
	}
	return output;
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
			str = "'" + stringVal + "'";
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

void JSONObject::clear(){
	vector <JSONObject *> eStack;
	eStack.push_back(this);
	int n = 0;
	while(n < eStack.size() ){
		JSONObject *temp = eStack[n];
		switch(temp->type){
			case JSON_OBJECT:
				for ( auto i = temp->objectVal.begin(); i!=temp->objectVal.end(); ++i ){
					eStack.push_back( &i->second );
				}
				break;
			case JSON_ARRAY:
				for ( int i = 0; i < temp->arrayVal.size(); i++ ){
					JSONObject *t = &temp->arrayVal[i];
					eStack.push_back(t);
				}
				break;
		}
		n++;
	}
	while (eStack.size() > 0){
		JSONObject *temp = eStack.back();
		switch(temp->type){
			case JSON_OBJECT:
				temp->objectVal.clear();
				break;
			case JSON_ARRAY:
				temp->arrayVal.clear();
				break;
		}
		eStack.pop_back();
	}
}