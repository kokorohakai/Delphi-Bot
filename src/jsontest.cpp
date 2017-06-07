#include "global.h"

int main(){
	JSONObject test;
	test.parse("{fruits:['apple','orange','banana','grapes'],prices:{apple:.99,orange:1.99,banana:.50,grapes:5.99}}");

	cout << test.stringify() << endl;
}