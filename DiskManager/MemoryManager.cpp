// ------------------------------------------------------------------- 
// Class Name   : DiskManager.cpp
// Description  : Calls for system main function
// Author       : James Marjun Jallorina
// Date         : 05/08/2016
// ------------------------------------------------------------------- 
#include <iostream>
#include "HardDiskMonitoring.h"

//#define BUFFSIZE 1024

using namespace std;

void usage(void){
	fprintf(stderr,
		"usage:\n"
		"	DiskManager v1.00 05082016\n"
		"	DiskManager -d&              run DiskManager\n"
		"	DiskManager --help           show this help\n"
		"\n"
	);
}

int main(int argc, char *argv[])
{
	if ( argc <= 1 )
	{
		usage();
		return 0;
	}
	string argcomp = argv[1];
	if (argcomp == "--help"){
		usage();
		return 0;
	}

	if (argcomp == "-d"){		//Debug mode
		startSystemMonitoring();
		return 0;
	}

	ofstream   fout("/dev/null");
	cout.rdbuf(fout.rdbuf()); // redirect 'cout' to a 'fout'
	startSystemMonitoring();
	exit(EXIT_SUCCESS); */
	return 0;
}