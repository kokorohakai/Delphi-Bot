#include "global.h"

AJAX::AJAX(){
	list = NULL;
	curl_global_init(CURL_GLOBAL_DEFAULT);
}

AJAX::~AJAX(){
	curl_slist_free_all(list);
	curl_global_cleanup();
}

string AJAX::go(){
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl){
		setupCurl(curl);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK) cerr << "Curl failed:" << curl_easy_strerror(res) << endl;
		curl_easy_cleanup(curl);
	} else {
		cout << "FATAL ERROR: curl failed to initialize" << endl;
		return "ERROR";
	}
	return buffer;
}

void AJAX::setupCurl(CURL *curl){
	curl_easy_setopt(curl, CURLOPT_URL, URL.c_str() );
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, userAgent.c_str() );
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, streamBuffer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, this);
}

void AJAX::setURL(string inURL){
	//URL = inURL;
	URL = "https://discordapp.com/api/gateway/bot";
}

void AJAX::addHeader(string inHeader){
	header = inHeader;
	list = curl_slist_append(list, header.c_str());
}

void AJAX::clearHeader(){
	curl_slist_free_all(list);
	list = NULL;
}

void AJAX::setUserAgent(string inAgent){
	userAgent = inAgent;
}

size_t AJAX::streamBuffer(char *buffer, size_t size, size_t nitems, void *inTarget){
	size_t realsize = size*nitems;
	AJAX *DM = (AJAX *)inTarget;
	for ( int i = 0; i < realsize; i++ ){
		DM->buffer.append(1, buffer[i]);
	}
	return realsize;
}