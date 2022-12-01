#include "bench.h"

double getGlobalStat() {
	char c[1000];
	FILE *fptr;
    if ((fptr = fopen("/proc/stat", "r")) == NULL) {
        printf("Error! File /proc/stat cannot be opened.");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    int r =  fscanf(fptr, "%[^\n]", c);
    fclose(fptr);

    int v = 0;
    char **arr = NULL;

    v = split(c, ' ', &arr);

    double user 	= strtod(arr[1], NULL);
    double nice 	= strtod(arr[2], NULL);
    double system 	= strtod(arr[3], NULL);
    double idle 	= strtod(arr[4], NULL);

    return user + nice + system + idle;
}

tuple* getOwnStat() {
	char c[1000];
	FILE *fptr;
    if ((fptr = fopen("/proc/self/stat", "r")) == NULL) {
        printf("Error! File /proc/self/stat cannot be opened.");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    int r = fscanf(fptr, "%[^\n]", c);
    fclose(fptr);

    int v = 0;
    char **arr = NULL;

    v = split(c, ' ', &arr);

    double utime 	= strtod(arr[13], NULL);
    double stime 	= strtod(arr[14], NULL);

    tuple* t = (tuple*) malloc(sizeof(tuple));

    t->utime = utime;
    t->stime = stime;

    return t;
}

void benchClient(unsigned long long workSize, unsigned long long (*f)(RdmaClient*, void*, unsigned long long), RdmaClient* rdmaClient, void* data, unsigned long long size, int repetitions) {

	triple** cpuLoads = vector_create();
	double* times = vector_create();

	for (unsigned long long i = 0; i < repetitions; i++) {

		double before = getGlobalStat();
		tuple* b = getOwnStat();

		double ownUserBefore 	= b->utime;
		double ownSystemBefore 	= b->stime;

		struct timeval begin, end;
	    gettimeofday(&begin, 0);

	    (*f)(rdmaClient, data, size);

	    gettimeofday(&end, 0);

	    long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;

    	double after = getGlobalStat();
    	tuple* a = getOwnStat();

		double ownUserAfter 	= a->utime;
		double ownSystemAfter 	= a->stime;

		double diff = (after - before);
      	double userPercent 		= (ownUserAfter - ownUserBefore) / diff * 100.0;
      	double systemPercent 	= (ownSystemAfter - ownSystemBefore) / diff * 100.0;
      	double totalPercent 	= userPercent + systemPercent;

      	triple* cpu = (triple*) malloc(sizeof(triple));
      	cpu->userTotal 		= userPercent;
      	cpu->systemTotal 	= systemPercent;
      	cpu->totalTotal 	= totalPercent;

      	vector_add(&cpuLoads, cpu);
      	vector_add(&times, elapsed);
	}

	double userTotal 	= 0;
	double systemTotal 	= 0;
	double totalTotal 	= 0;

	for (int j = 0; j < vector_size(cpuLoads); j++) {
		userTotal 	+= cpuLoads[j]->userTotal;
		systemTotal += cpuLoads[j]->systemTotal;
		totalTotal 	+= cpuLoads[j]->systemTotal;
	}

	double userPercent 	= userTotal/repetitions;
	double systemPercent 	= systemTotal/repetitions;
	double totalPercent 	= totalTotal/repetitions;

	double total = 0;

	for (int k = 0; k < vector_size(times); k++) {
		total += times[k];
	}

	total /= repetitions;

	printf("%llu, %f, %f, %f, %f, %f \n", workSize, total, workSize/total, userPercent, systemPercent, totalPercent);

}


void benchServer(unsigned long long workSize, unsigned long long (*f)(RdmaServer*, void*, unsigned long long), RdmaServer* rdmaServer, void* data, unsigned long long size, int repetitions) {

	triple** cpuLoads = vector_create();
	double* times = vector_create();

	for (unsigned long long i = 0; i < repetitions; i++) {

		double before = getGlobalStat();
		tuple* b = getOwnStat();

		double ownUserBefore 	= b->utime;
		double ownSystemBefore 	= b->stime;

		struct timeval begin, end;
	    gettimeofday(&begin, 0);

	    (*f)(rdmaServer, data, size);

	    gettimeofday(&end, 0);
	    long seconds = end.tv_sec - begin.tv_sec;
    	long microseconds = end.tv_usec - begin.tv_usec;
    	double elapsed = seconds + microseconds*1e-6;

    	double after = getGlobalStat();
    	tuple* a = getOwnStat();

		double ownUserAfter 	= a->utime;
		double ownSystemAfter 	= a->stime;

		double diff = (after - before);
      	double userPercent = (ownUserAfter - ownUserBefore) / diff * 100.0;
      	double systemPercent = (ownSystemAfter - ownSystemBefore) / diff * 100.0;
      	double totalPercent = userPercent + systemPercent;

      	triple* cpu = (triple*) malloc(sizeof(triple));
      	cpu->userTotal 		= userPercent;
      	cpu->systemTotal 	= systemPercent;
      	cpu->totalTotal 	= totalPercent;

      	vector_add(&cpuLoads, cpu);
      	vector_add(&times, elapsed);
	}

	double userTotal 	= 0;
	double systemTotal 	= 0;
	double totalTotal 	= 0;

	for (int j = 0; j < vector_size(cpuLoads); j++) {

		userTotal 	+= cpuLoads[j]->userTotal;
		systemTotal += cpuLoads[j]->systemTotal;
		totalTotal 	+= cpuLoads[j]->systemTotal;
	}

	double userPercent 	= userTotal/repetitions;
	double systemPercent 	= systemTotal/repetitions;
	double totalPercent 	= totalTotal/repetitions;

	double total = 0;

	for (int k = 0; k < vector_size(times); k++) {
		total += times[k];
	}

	total /= repetitions;

	printf("%llu, %f, %f, %f, %f, %f \n", workSize, total, workSize/total, userPercent, systemPercent, totalPercent);
	
}




