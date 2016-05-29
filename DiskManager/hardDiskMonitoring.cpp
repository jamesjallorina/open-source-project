// ------------------------------------------------------------------- 
// Class Name   : ResoureMonitoring.h
// Description  : Used for monitoring HDD storage space
// Author       : James Marjun Jallorina
// Date         : 05/08/2016
// ------------------------------------------------------------------- 
#include <iostream>
#include "HardDiskMonitoring.h"

using namespace std;

// -------------------------------------------------------------
// Constructor and Destructor
// -------------------------------------------------------------
HardDiskMonitoring::HardDiskMonitoring() { }
HardDiskMonitoring::~HardDiskMonitoring() { }

void HardDiskMonitoring::setvPartionList(string sPartionName)
{
	vPartitionList.pushback(sPartionName);
}

void HardDiskMonitoring::getvPartionList(int iNum)
{
	return vPartionList[i];
}

// -------------------------------------------------------------
// Piping Linux commands alternative to system call
// -------------------------------------------------------------
string HardDiskMonitoring::command(const char *cCommand)
{
	FILE *f = popen( cCommand, "r");
	const int BUFFSIZE = 1024;
	char acFetchedChar[BUFFSIZE];
	memset(acFetchedChar, '\0', BUFFSIZE);
		
		while( fgets(acFetchedChar, BUFFSIZE, f)){
		}
		pclose(f);
	
	string sFetchedString(acFetchedChar);
	sFetchedString.resize(sFetchedString.size()-1);
	return sFetchedString;
} //End of function

// -------------------------------------------------------------
// Get the total partition mounted
// -------------------------------------------------------------
int HardDiskMonitoring::getPartionMounted(void){
	int iTotalMountedPartition = 0;
	string sGetAllCurrentPartion = string("df | grep '/dev' | wc | awk '{print $1}'");
	string sGetValue = command(sGetAllCurrentPartion.c_str());
	iTotalMountedPartition = atoi(sGetValue.c_str());
//	cout << "Total Mounted Partition: " << iTotalPartion << endl;
	return iTotalMountedPartition;
} //End of function

// -------------------------------------------------------------
// 
// -------------------------------------------------------------
void HardDiskMonitoring::getPartitionMemoryList(void){
	FILE* fl;
	char* line = NULL;
	char* result = (char*) calloc(1, 1);
	size_t len = 0;

	fflush(NULL);
	string cmd = string("df | grep '/dev' | awk '{print $1}'");
	const char *command = cmd.c_str();
	fl = popen(command, "r");
	while(getline(&line, &len, fl) != -1){
		result = (char*) realloc(result, strlen(result) + strlen(line) + 1);
		strncpy(result + strlen(result), line, strlen(line) + 1);
		free(line);
		line = NULL;
		setvPartionList(string(result));
		
		result = (char*) calloc(1,1);
	}
	fflush(fl);
	pclose(fl);
} //End of function

void HardDiskMonitoring::executeDiskMonitoring(void){
	getPartitionMemoryList();
	string sGetStorageValue = "";
	string sMemoryLeft = "";
	cout << "\nChecking Disk Partion. . ." << endl;
	cout << "Found only: " << getPartionMounted() << " Partion. . ." << endl;
	for(int i=0; i<=getPartionMounted(); i++){
		
		sGetStorageValue = string("df | grep ") + vPartionList[i] + string(" | awk '{print $3}'");
		sMemoryLeft = command(sGetStorageValue.c_str());
		if ( sMemoryLeft == "0" || sMemoryLeft == "0.0" || sMemoryLeft == "0.00")
		{
		cout << "Partition " << getvPartionList(i) << "is FULL, please allocate extra storage. . ." << endl;
		}
	}
} //End of function

void *HardDiskMonitoring::systemThread(void *ptr){
	for(;;)
	{
		for(int s = 5; s > 0; s--)
		{
			sleep(1);	
		}
		executeDiskMonitoring();
	}
} //End of function

void HardDiskMonitoring::startSystemMonitoring(void)
{
	pthread_t thread;
	int iret1;
	iret1 = pthread_create( &thread, NULL, systemThread,(void*) NULL);
	if(iret1){
		fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		exit(EXIT_FAILURE);
	}
		pthread_join( thread, NULL);
} //End of function