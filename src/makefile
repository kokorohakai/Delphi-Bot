#variables
DEFINES 	:=
#files
OBJECTS		:=core.o main.o json.o
MAINCPP		:=main.cpp global.cpp
MAINH		:=global.h
CORECPP		:=core.cpp
COREH		:=core.h
JSONCPP		:=json.cpp
JSONH		:=json.h
#compiler options
OPTIONS		:=-Wno-deprecated -std=gnu++11 -Wno-narrowing -fmax-errors=3
INCLUDES	:=-L/usr/lib/x86_64-linux-gnu/
LIBS		:=-lcurl -lwebsockets
FINAL		:=-o ../bin/delphi $(DEFINES) $(OPTIONS) $(INCLUDES) modules/*.o *.o $(LIBS)
DEBUG 		:=
HEADERS 	:=$(MAINH) $(COREH) $(JSONH)

all: $(OBJECTS)
	cd modules; make all;
	g++ $(DEBUG) $(FINAL)

clean:
	cd modules; make clean;
	rm *.o
	rm ../bin/delphi

debug: enableDebug $(OBJECTS)
	g++ $(DEBUG) $(FINAL)

enableDebug:
	$(eval DEBUG:=-g -ggdb)

main.o: $(MAINCPP) $(HEADERS)
	g++ -c $(SHARED) $(DEBUG) $(OPTIONS) $(MAINCPP)

core.o: $(CORECPP) $(HEADERS)
	g++ -c $(SHARED) $(DEBUG) $(OPTIONS) $(CORECPP)

json.o:	$(JSONCPP) $(HEADERS)
	g++ -c $(SHARED) $(DEBUG) $(OPTIONS) $(JSONCPP)

jsontest: jsontest.cpp json.cpp json.h
	g++ jsontest.cpp json.cpp -g -ggdb -o ../jsontest