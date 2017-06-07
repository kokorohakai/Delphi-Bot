#include "global.h"
#include "discordModule.h"

DiscordModule::DiscordModule(){
	Module::modules.push_back(this);
	cout << "Discord module initialized. Module #" << Module::modules.size() << endl;
}

void DiscordModule::Listen(){

}