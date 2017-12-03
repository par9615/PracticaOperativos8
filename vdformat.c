#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "vdisk.h"

int main(int argc,char *argv[])
{
	int disk = atoi(argv[1]);
	struct SECBOOTPART sbp;


	sprintf(sbp.nombre_particion, "part%d", disk);
	
	//vdwritesector(int unit, int cylinder, int surface, int sector, int nsecs, char* buffer);

	vdwritesector(0, 0,0,2,1, (char*)&sbp);




	return 0;
}