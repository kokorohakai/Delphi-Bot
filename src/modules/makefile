#variables
DEFINES 	:=
#files
OBJECTS		:=module.o discord.o
MODULECPP	:=module.cpp
MODULEH		:=module.h
DISCORDCPP	:=discordModule.cpp discord/gateway.cpp
DISCORDH	:=discordModule.h discord/variables.h ../global.h discord/gateway.h
#compiler options
OPTIONS		:=-Wno-deprecated -std=gnu++11 -Wno-narrowing -fmax-errors=3
DEBUG 		:=
HEADERS 	:=$(MODULEH) $(DISCORDH)

all: $(OBJECTS)

clean:
	rm *.o

debug: enableDebug $(OBJECTS)

enableDebug:
	$(eval DEBUG:=-g -ggdb)

module.o: $(MODULECPP) $(HEADERS)
	g++ -c $(SHARED) $(OPTIONS) $(DEBUG) $(MODULECPP)

discord.o: $(DISCORDCPP) $(HEADERS)
	g++ -c $(SHARED) $(OPTIONS) $(DEBUG) $(DISCORDCPP)