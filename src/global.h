//global includes, needed everywhere.
#include <iostream>
#include <unistd.h>
#include <map>
#include <vector>
#include <string>
using namespace std;
#include "modules/module.h"
#include "core.h"
#include "json.h"

//the actual global.h
#ifndef GLOBAL_H
#define GLOBAL_H
struct Global{
	static Core *delphi;
};

#endif