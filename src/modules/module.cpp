#include "global.h"
#include "discordModule.h"

vector<Module *> Module::modules;

Module::Module(){
	cout << "Modules initializing." << endl;
}

void Module::load(){
	//I need to figure out a way to pull this out of this method
	//and allow it to stand alone, but I guess it's not recessary.
	//Maybe another day I can make it plugins, but this is not
	//something I want to make public.
	DiscordModule discordModule;	
}

void Module::listen(){

}