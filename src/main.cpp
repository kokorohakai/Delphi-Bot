#include "global.h"
#include <curl/curl.h>

int main(){
	Core core;
	Global::delphi = &core;
}