CC=g++
CFLAGS=-g -Wall -O2

rankSynergy: geneSetConf.o main.o
	$(CC) $(CFLAGS) -o rankSynergy geneSetConf.o main.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

geneSetConf.o: geneSetConf.cpp
	$(CC) $(CFLAGS) -c geneSetConf.cpp
