#ifndef DISCORD_H
#define DISCORD_H
#include <libwebsockets.h>

class DiscordModule : public Module {
	public:
		DiscordModule();
		~DiscordModule();
		void Listen();
	private:
		void setGateway();
		void updateGateway();
		void connectSocket();
		static size_t streamBuffer(char *buffer, size_t size, size_t nitems, void *instream);
		string buffer;
		#include "discord/variables.h"

		/*******************
		Web socket rubbish
		*******************/
		struct pthread_routine_tool {
			struct lws_context *context;
			struct lws *wsi;
		};
		struct WebSocket{
		    struct lws_context *context = NULL;
		    struct lws_context_creation_info info;
		    struct lws *wsi = NULL;
		    struct lws_protocols protocol;
		} ws;
		static int ws_service_callback( lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len);
		static int websocket_write_back(struct lws *wsi_in, char *str, int str_size_in);
};
#endif