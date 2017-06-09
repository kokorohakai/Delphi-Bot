#include "global.h"
void report(JSONObject obj){
	switch (obj.type){
		case JSON_OBJECT:
			for (auto i : obj.objectVal){
				cout << i.first << " : " << endl;
				report(i.second);
			}
		break;
		case JSON_ARRAY:
			for (int i = 0; i < obj.arrayVal.size();i++){
				cout << "[" << i << "] : " << endl;
				report(obj.arrayVal[i]);
			}
		break;
		case JSON_NUMBER:
			cout << obj.numberVal << endl;
		break;
		default:
			cout << obj.stringVal << endl;
		break;
	}
}

int main(){
	JSONObject test;
	
	cout << "TEST 1:" << endl;
	test.parse("{fruits:['apple','orange','banana','grapes'],prices:{apple:.99,orange:1.99,banana:.50,grapes:5.99}}");
	cout << "Object Report:" << endl;
	report(test);
	cout << test.stringify() << endl << endl;

	cout << "TEST 2: (From Discord API)" << endl;
	test.parse("{\"code\": 0, \"message\": \"404: Not Found\"}");
	cout << "Object Report:" << endl;
	report(test);
	cout << test.stringify() << endl << endl;

	cout << "TEST 3: (From Mabinogi DB)" << endl;
	test.parse("{\"records\":34,\"total\":1,\"page\":\"1\",\"rows\":[{\"id\":28,\"cell\":[\"Alchemy Mastery\",28,28]},{\"id\":22,\"cell\":[\"Bow Mastery\",22,22]},{\"id\":2,\"cell\":[\"Campfire\",2,2]},{\"id\":44,\"cell\":[\"Carpentry\",44,44]},{\"id\":29,\"cell\":[\"Chain Cylinder\",29,29]},{\"id\":20,\"cell\":[\"Crash Shot\",20,20]},{\"id\":21,\"cell\":[\"Critical Hit\",21,21]},{\"id\":23,\"cell\":[\"Crossbow Mastery\",23,23]},{\"id\":6,\"cell\":[\"Doppleganger\",6,6]},{\"id\":24,\"cell\":[\"Final Shot\",24,24]},{\"id\":39,\"cell\":[\"Fire Alchemy\",39,39]},{\"id\":3,\"cell\":[\"Fishing\",3,3]},{\"id\":31,\"cell\":[\"Flame Burst\",31,31]},{\"id\":35,\"cell\":[\"Frozen Blast\",35,35]},{\"id\":33,\"cell\":[\"Guard Cylinder Mastery\",33,33]},{\"id\":43,\"cell\":[\"Handicraft\",43,43]},{\"id\":36,\"cell\":[\"Heat Buster\",36,36]},{\"id\":37,\"cell\":[\"Life Drain\",37,37]},{\"id\":18,\"cell\":[\"Magnum Shot\",18,18]},{\"id\":25,\"cell\":[\"Mirage Missile\",25,25]},{\"id\":42,\"cell\":[\"Production Mastery\",42,42]},{\"id\":17,\"cell\":[\"Ranged Attack\",17,17]},{\"id\":1,\"cell\":[\"Rest\",1,1]},{\"id\":34,\"cell\":[\"Sand Burst\",34,34]},{\"id\":38,\"cell\":[\"Shock\",38,38]},{\"id\":26,\"cell\":[\"Spider Shot\",26,26]},{\"id\":19,\"cell\":[\"Support Shot\",19,19]},{\"id\":4,\"cell\":[\"Taming Wild Animals\",4,4]},{\"id\":5,\"cell\":[\"Transformation Mastery\",5,5]},{\"id\":27,\"cell\":[\"Urgent Shot\",27,27]},{\"id\":40,\"cell\":[\"Water Alchemy\",40,40]},{\"id\":30,\"cell\":[\"Water Cannon\",30,30]},{\"id\":41,\"cell\":[\"Wind Alchemy\",41,41]},{\"id\":32,\"cell\":[\"Wind Blast\",32,32]}]}");
	cout << "Object Report:" << endl;
	report(test);
	cout << test.stringify() << endl << endl;


}