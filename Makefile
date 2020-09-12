COMMSRC= ./restapi/RestAPI.cpp ./pugixml/pugixml.cpp

STDSRC=main.cpp
STDOBJS=$(STDSRC:.cpp=.o)

COMMOBJS=$(COMMSRC:.cpp=.o)

DLPATH=-I./restapi/. -I./pugixml/. 
CFLAGOPTS=-std=c++11 -Wall -g -lcurl 

ifeq ($(MODE), 1)
CFLAGS= -DENABLE_COREDUMP $(DLPATH) $(CFLAGOPTS)
else
CFLAGS=$(DLPATH) $(CFLAGOPTS)
endif

TARGET=news

CC=g++
all: $(TARGET) 

news: $(STDOBJS) $(COMMOBJS)
	$(CC) -o $@ $(COMMOBJS) $(STDOBJS) $(CFLAGS)

%.o:%.cpp Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf ./news $(STDOBJS) $(COMMOBJS)

