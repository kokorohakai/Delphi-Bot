#include "../global.h"

Module::Module(){
	cout << "Modules initializing." << endl;
}

void Module::listen(){
	discordModule.listen();
}