#ifndef DISCORD_GATEWAY_H
#define DISCORD_GATEWAY_H
enum byte{//state
	LOGGEDOUT = 0,
	LOGGINGIN = 1,
	LOGGEDIN = 2,
	LOGGINGOUT = 3
};

class DiscordGateway{
	public:
		DiscordGateway();
		~DiscordGateway();
		void listen();
		void connectSocket();
	private:
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
		byte state = LOGGEDOUT;

		static int ws_service_callback( lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len);
		static int websocket_write_back(struct lws *wsi_in, char *str, int str_size_in);
};
#endif