#include "../global.h"

DiscordModule::DiscordModule(){
	cout << "Discord module initialized." << endl;
    initAJAX();
	setGateway();
    gateway.connectSocket();
}

void DiscordModule::listen(){
    ++counter;
    cout << "DiscordModule::listen" << endl;
    if (counter%100==0) {
        setGateway();
        /*
            TODO: if something changes, it should reconnect to the gateway.
            gateway.connectSocket();
        */
    }
    gateway.listen();
}

DiscordModule::~DiscordModule(){
	
}

void DiscordModule::initAJAX(){
    string header = "Authorization: Bot ";
    header = header.append(vars.botToken);
    ajax.addHeader(header);
    ajax.setUserAgent(vars.userAgent);
}
/*
	Authenticate with Discords bot gateway. This authenticates and then 
	receives what url it is allowed to open a websocket on, and how many.
*/
void DiscordModule::setGateway(){
	cout << "updating Discord Gateway" << endl;
    ajax.setURL(vars.gatewayURL);
    JSONObject gw;
    string output = ajax.go();
    cout << output << endl;
    gw.parse( output );
	
    vars.gateway.url = gw.objectVal["url"].stringVal;
    vars.gateway.shards = gw.objectVal["shards"].numberVal;

    cout << "Allocated " << vars.gateway.shards << " connection to: " << vars.gateway.url << endl;
}