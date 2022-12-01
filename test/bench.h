#ifndef bench_h
#define bench_h


#include "vec.h"
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include "../client/RdmaClient.h"
#include "../server/RdmaServer.h"
#include "../utils/utils.h"


#ifdef __cplusplus
// when included in C++ file, let compiler know these are C functions
extern "C" {
#endif

typedef struct {

	double utime;
	double stime;

} tuple;

typedef struct {

	double userTotal;
	double systemTotal;
	double totalTotal;

} triple;


double getGlobalStat();

tuple* getOwnStat();

void benchClient(unsigned long long, unsigned long long (*f)(RdmaClient*, void*, unsigned long long), RdmaClient*, void*, unsigned long long, int);

void benchServer(unsigned long long, unsigned long long (*f)(RdmaServer*, void*, unsigned long long), RdmaServer*, void*, unsigned long long, int);



#ifdef __cplusplus
}
#endif

#endif