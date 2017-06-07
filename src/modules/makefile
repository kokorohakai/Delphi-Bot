#variables
DEFINES 	:=
#files
OBJECTS		:=module.o discord.o
MODULECPP	:=module.cpp
MODULEH		:=module.h
DISCORDCPP	:=discordModule.cpp
DISCORDH	:=discordModule.h
#compiler options
OPTIONS		:=-Wno-deprecated -std=gnu++11 -Wno-narrowing -fmax-errors=3
INCLUDES	:=
LIBS		:=
FINAL		:=
DEBUG 		:=
HEADERS 	:=$(MODULEH) $(DISCORDH)

all: $(OBJECTS)
	

clean:
	rm *.o

debug: enableDebug $(OBJECTS)
	g++ $(DEBUG) $(FINAL)

enableDebug:
	$(eval DEBUG:=-g -ggdb)

module.o: $(MODULECPP) $(HEADERS)
	g++ -c $(SHARED) $(DEBUG) $(MODULECPP)

discord.o: $(DISCORDCPP) $(HEADERS)
	g++ -c $(SHARED) $(DEBUG) $(DISCORDCPP)