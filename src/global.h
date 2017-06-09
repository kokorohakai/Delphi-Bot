#ifndef GLOBAL_H
#define GLOBAL_H
//global includes, needed everywhere.
#include <iostream>
#include <unistd.h>
#include <map>
#include <vector>
#include <string>
using namespace std;
#include <curl/curl.h>
#include <libwebsockets.h>
#include "json.h"
#include "ajax.h"
#include "modules/discord/gateway.h"
#include "modules/discordModule.h"
#include "modules/module.h"
#include "core.h"

struct Global{
	static Core *delphi;
};

#endif