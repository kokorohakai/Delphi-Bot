#include "global.h"

Core::Core(){
	cout << "Delphi bot has started." << endl;
	think();
}

void Core::think(){
	while (true){
		usleep(100000);// 1/10th of a second.
		listen();
	}
}
void Core::listen(){
	modules.listen();
}
