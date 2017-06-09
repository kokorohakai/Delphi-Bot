#include "../../global.h"
DiscordGateway::DiscordGateway(){
    ws.protocol.name  = "wss";
    ws.protocol.callback = &ws_service_callback;
    ws.protocol.per_session_data_size = sizeof(int);
    ws.protocol.rx_buffer_size = 1;
    ws.protocol.id = 0;
    ws.protocol.user = NULL;

    memset(&ws.info, 0, sizeof(ws.info) );
    ws.info.port = CONTEXT_PORT_NO_LISTEN;
    ws.info.iface = NULL;
    ws.info.protocols = &ws.protocol;
    ws.info.ssl_cert_filepath = NULL;
    ws.info.ssl_private_key_filepath = NULL;
    ws.info.extensions = lws_get_internal_extensions();
    ws.info.gid = -1;
    ws.info.uid = -1;
    ws.info.options = 0;

    ws.context = lws_create_context(&ws.info);
	if (ws.context == NULL) {
        cout << "ERROR: [Main] context is NULL." << endl;
        return;
    }
    cout << "[Main] context created" << endl;
}

DiscordGateway::~DiscordGateway(){
	if (ws.context) {
		lws_context_destroy(ws.context);
	}
}

void DiscordGateway::listen(){
	if (ws.context){
		lws_service(ws.context, 50);
	}
}

void DiscordGateway::connectSocket(){
	if (ws.context){
	    ws.wsi = lws_client_connect( 
	    	ws.context, //the context
	    	//vars.gateway.url.c_str(), //the url returned from the both gateway
	    	"gateway.discord.gg", //address
	    	80, //port
	    	0, //ssl
	        "/",
			//"/?v=5&encoding=json", //path
			"wss://gateway.discord.gg?v=5&encoding=json",//temp host
			//vars.gateway.url.c_str(), //host
			//"localhost:80", //host
			NULL, //origin
			ws.protocol.name, //protocal
			-1  //??? / ietf_version_or_minus_one
		);
	    if (ws.wsi == NULL) {
	        cout << "[Main] wsi create error." << endl;
	        return;
	    }

		cout << "[Main] wsi create success" << endl 
	        << "==== Connected to Discord Gateway. ====" << endl;
	}
}

int DiscordGateway::ws_service_callback( lws *wsi, lws_callback_reasons reason, void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            cout << "[Main Service] Connect with server success." << endl;
            //connection_flag = 1;
            break;

        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            cout << "[Main Service] Connect with server error." << endl;
            /*
            destroy_flag = 1;
            connection_flag = 0;
            */
            break;

        case LWS_CALLBACK_CLOSED:
            cout << "[Main Service] LWS_CALLBACK_CLOSED" << endl;
            /*
            destroy_flag = 1;
            connection_flag = 0;
            */
            break;

        case LWS_CALLBACK_CLIENT_RECEIVE:
            cout << "[Main Service] Client received:" << (char *)in << endl;

            /*
            	if (writeable_flag)
                destroy_flag = 1;
                */
            break;
        case LWS_CALLBACK_CLIENT_WRITEABLE :
            cout << "[Main Service] On writeable is called. send byebye message" << endl;
            websocket_write_back(wsi, "Byebye! See you later", -1);
            //writeable_flag = 1;
            break;

        default:
            break;
    }

    return 0;
}

int DiscordGateway::websocket_write_back(struct lws *wsi_in, char *str, int str_size_in) {
    if (str == NULL || wsi_in == NULL)
        return -1;

    int n;
    int len;
    unsigned char *out = NULL;

    if (str_size_in < 1) 
        len = strlen(str);
    else
        len = str_size_in;

    out = (unsigned char *)malloc(sizeof(unsigned char)*(LWS_SEND_BUFFER_PRE_PADDING + len + LWS_SEND_BUFFER_POST_PADDING));
    //* setup the buffer* /
    memcpy (out + LWS_SEND_BUFFER_PRE_PADDING, str, len );
    //* write out* /
    n = lws_write(wsi_in, out + LWS_SEND_BUFFER_PRE_PADDING, len, LWS_WRITE_TEXT);

    cout << "[websocket_write_back] " << str << endl;
    //* free the buffer*/
    free(out);

    return n;
}