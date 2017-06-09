#ifndef JSON_H
#define JSON_H
enum{
	JSON_ERROR=0,
	JSON_OBJECT=1,
	JSON_ARRAY=2,
	JSON_STRING=3,
	JSON_NUMBER=4
};

class JSONObject{
	public:
		int type=0;//uses the enum above to determenine the type used, below.
		//the data.
		map <string, JSONObject> objectVal;//JSON_OBJECT
		vector <JSONObject> arrayVal;//JSON_ARRAY
		string stringVal;//JSON_STRING
		double numberVal;//JSON_NUMBER
		//the methods
		void parse(string);//parses a string into a JSON Object.
		string stringify();//converts an object, into a string.
		void clear();//empties the object.
	private:
		void setType(string str);//gets the type of the object from string.
		bool is_number(const string &s);
		void parseObject(string str);
		void parseArray(string str);
		string trim(string str);//removes surrounding whitespace.
		string removeEnclosure(string str);//removes surrounding enclosures of strings.
		string propertyName(string str);//prepares a property name, removings containing quotations marks if present.
		vector<string> split(string str,char find);
};
#endif