#define MYVARIABLES
struct Vars{
	//URLS - this is a list of URLS used for functionality
	string apiURL = "";
	string gatewayURL = "";
	string cdnUrl = "";
	string inviteUrl = "";
	//Client Info (Passwords).
	string clientID = "";
	string clientSecret = "";
	string botToken = "";
	//the rest.
	string userAgent = "";
	string fullName = "";
	string name = "";
	//stateful data
	struct Gateway{
		string url = "";//websocket url returned from API.
		int shards = 0;//how many processes we're allowed to execute.
	} gateway;
} vars;