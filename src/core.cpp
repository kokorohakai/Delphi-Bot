#include "global.h"

Core::Core(){
	cout << "Delphi bot has started." << endl;
	modules.load();
	think();
}

void Core::think(){
	while (true){
		listen();
		usleep(100);
	}
}
void Core::listen(){
	for ( int i = 0; i < Module::modules.size(); i++ ){
		Module::modules[i]->listen();
	}
}
