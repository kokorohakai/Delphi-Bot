#ifndef DISCORD_H
#define DISCORD_H
//#include <libwebsockets.h>

class DiscordModule {
	public:
		DiscordModule();
		~DiscordModule();
		void listen();
	private:
		void initAJAX();
		void setGateway();
		
		AJAX ajax;
		int counter = 0;
		
		#include <discord/myvariables.h>
		#ifndef MYVARIABLES
		#include "discord/variables.h"
		#endif

		DiscordGateway gateway;
};
#endif