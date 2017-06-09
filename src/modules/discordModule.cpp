#include "global.h"
#include <curl/curl.h>
//#include <signal.h>
#include <libwebsockets.h>

#include "discordModule.h"

DiscordModule::DiscordModule(){
	Module::modules.push_back(this);
	cout << "Discord module initialized. Module #" << Module::modules.size() << endl;
	
	curl_global_init(CURL_GLOBAL_DEFAULT);
	
	setGateway();
	connectSocket();
}

void DiscordModule::Listen(){
	lws_service(ws.context, 50);
}

DiscordModule::~DiscordModule(){
	lws_context_destroy(ws.context);
}

//used by curl to place data into: "string buffer". This data can then be used 
//after curl is complete.
size_t DiscordModule::streamBuffer(char *buffer, size_t size, size_t nitems, void *inTarget){
	size_t realsize = size*nitems;
	DiscordModule *DM = (DiscordModule *)inTarget;
	for ( int i = 0; i < realsize; i++ ){
		DM->buffer.append(1, buffer[i]);
	}
	return realsize;
}

/*
	Authenticate with Discords bot gateway. This authenticates and then 
	receives what url it is allowed to open a websocket on, and how many.
*/
void DiscordModule::setGateway(){
	cout << "Connecting to Discord Gateway" << endl;
	//configure the authentication header.
	vars.header = "Authorization: Bot ";
	vars.header.append(vars.botToken);


	CURL *curl = curl_easy_init();
	CURLcode res;
	curl_slist *list = NULL;

	
	if (curl){
		list = curl_slist_append(list ,vars.header.c_str());
  		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
    	curl_easy_setopt(curl, CURLOPT_URL, vars.gatewayURL.c_str());
		curl_easy_setopt(curl, CURLOPT_USERAGENT, vars.userAgent.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, streamBuffer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK){
			cerr << "curl_easy_perform() failed:" 
				<< curl_easy_strerror(res) << endl;
		}

		JSONObject gw;
		gw.parse(buffer);
		vars.gateway.url = gw.objectVal["url"].stringVal;
		vars.gateway.shards = gw.objectVal["shards"].numberVal;
		cout << "Allocated " << vars.gateway.shards << " connection to: " << vars.gateway.url << endl;
		curl_slist_free_all(list);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

void DiscordModule::updateGateway(){
	cout << "Updating our state to Discord Gateway" << endl;
	//configure the authentication header.
	vars.header = "Authorization: Bot ";
	vars.header.append(vars.botToken);


	CURL *curl = curl_easy_init();
	CURLcode res;
	curl_slist *list = NULL;

	
	if (curl){
		list = curl_slist_append(list ,vars.header.c_str());
  		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
    	curl_easy_setopt(curl, CURLOPT_URL, vars.gatewayURL.c_str());
		curl_easy_setopt(curl, CURLOPT_USERAGENT, vars.userAgent.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, streamBuffer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
		//this is the only line that's really different... isn't?
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "idle_since=&game={name:\");

		res = curl_easy_perform(curl);

		if (res != CURLE_OK){
			cerr << "curl_easy_perform() failed:" 
				<< curl_easy_strerror(res) << endl;
		}

		JSONObject gw;
		gw.parse(buffer);
		vars.gateway.url = gw.objectVal["url"].stringVal;
		vars.gateway.shards = gw.objectVal["shards"].numberVal;
		cout << "Allocated " << vars.gateway.shards << " connection to: " << vars.gateway.url << endl;
		curl_slist_free_all(list);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}




void DiscordModule::connectSocket(){
	//* register the signal SIGINT handler */
    struct sigaction act;
    //act.sa_handler = INT_HANDLER;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    sigaction( SIGINT, &act, 0);


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

    ws.protocol.name  = "wss";
    ws.protocol.callback = &ws_service_callback;
    ws.protocol.per_session_data_size = sizeof(int);
    ws.protocol.rx_buffer_size = 0;
    ws.protocol.id = 0;
    ws.protocol.user = NULL;

    ws.context = lws_create_context(&ws.info);
    cout << "[Main] context created" << endl;

	if (ws.context == NULL) {
        cout << "[Main] context is NULL." << endl;
        return;
    }

	/*
	lws_client_connect(
		struct lws_context *clients, 
		const char *address,
        int port, 
        int ssl_connection, 
        const char *path,
        const char *host, 
        const char *origin, 
        const char *protocol,
        int ietf_version_or_minus_one
    ) LWS_WARN_DEPRECATED;
    */
    ws.wsi = lws_client_connect( 
    	ws.context, //the context
    	//vars.gateway.url.c_str(), //the url returned from the both gateway
    	"gateway.discord.gg", //address
    	80, //port
    	0, //ssl
		"/?v=5&encoding=json", //path
		"wss://gateway.discord.gg?v=5&encoding=json",//temp host
		//vars.gateway.url.c_str(), //host
		//"localhost:80", //host
		NULL, //origin
		ws.protocol.name, //protocal
		-1  //???
	);
    if (ws.wsi == NULL) {
        cout << "[Main] wsi create error." << endl;
        return;
    }

	cout << "[Main] wsi create success." << endl;
}

int DiscordModule::ws_service_callback( lws *wsi, lws_callback_reasons reason, void *user, void *in, size_t len) {
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


int DiscordModule::websocket_write_back(struct lws *wsi_in, char *str, int str_size_in) {
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
    //* setup the buffer*/
    memcpy (out + LWS_SEND_BUFFER_PRE_PADDING, str, len );
    //* write out*/
    n = lws_write(wsi_in, out + LWS_SEND_BUFFER_PRE_PADDING, len, LWS_WRITE_TEXT);

    cout << "[websocket_write_back] " << str << endl;
    //* free the buffer*/
    free(out);

    return n;
}