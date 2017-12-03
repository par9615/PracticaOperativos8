#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "vdisk.h"



int main(int argc,char *argv[])
{
	struct MBR mbr;
	struct PARTITION part;

	int disk = atoi(argv[1]);		
	
	for(int i = 0; i < 448; i++)
		mbr.bootstrap_code[i] = 'B';

	part.drive_status = 0x80; 					//Partition is active
	part.chs_begin[0] = 0;   					//Head 0
	part.chs_begin[1] = (0 & 0x300)>>2 | 2;		//Sector 2
	part.chs_begin[2] = 0;						//Cylinder 0
	
	part.partition_type = 0x99;		//Partition type Unix

	part.chs_end[0] = HEADS-1;									//Head 7
	part.chs_end[1] = ((CYLINDERS-1) & 0x300)>>2 | SECTORS;		//Sector 27
	part.chs_end[2] = (CYLINDERS-1) & 0xFF;						//Cylinder 199
	
	part.lba = 0;					//First logic sector
	part.secs_partition = SECTORS;	//Number of sectors assigned to partition

	mbr.partition[0] = part;		//Assign first partition

	for(int i = 1; i < 4; i++)		//Set the other partitions as inactive
		mbr.partition[i].drive_status = 0x00;

	mbr.boot_signature = 0x55AA;  //Signature

	vdwritesector(disk, 0,0,1,1, (char *)&mbr); //Writes MBR on first physical sector

	return 0;
}