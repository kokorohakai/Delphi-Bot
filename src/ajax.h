#ifndef AJAX_H
#define AJAX_H

class AJAX{
	public:
		AJAX();
		~AJAX();
		void addHeader(string);
		void clearHeader();
		void setURL(string);
		void setUserAgent(string);
		string go();
	private:
		void setupCurl(CURL *);
		curl_slist *list = NULL;
		string header = "";
		string URL = "";
		string buffer = "";
		string userAgent = "";
		static size_t streamBuffer(char *buffer, size_t size, size_t nitems, void *instream);
};
#endif