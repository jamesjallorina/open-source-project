// ------------------------------------------------------------------- 
// Class Name   : ResoureMonitoring.h
// Description  : Used for monitoring HDD storage space
// Author       : James Marjun Jallorina
// Date         : 05/08/2016
// ------------------------------------------------------------------- 

#ifndef HARD_DISK_MONITORING
#define HARD_DISK_MONITORING

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <pthread.h>
#include <vector>


class HardDiskMonitoring
{
private:
	vector<string> vPartionList;

public:
	HardDiskMonitoring();
	~HardDiskMonitoring();
	
	void setvPartionList(string sPartionName);
	void getvPartionList(void);
	string command(const char *cCommand);
	int getPartionMounted(void);
	void getPartionMemoryList(void);
	void executeDiskMonitoring(void);
	void *systemThread(void *ptr);
	void startSystemMonitoring(void);
}; //End class Definition

#endif
