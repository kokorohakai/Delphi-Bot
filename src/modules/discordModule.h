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
		
		#include "discord/variables.h"

		DiscordGateway gateway;
};
#endif