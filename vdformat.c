#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "vdisk.h"

#define FIRST_SECTOR 2

int main(int argc,char *argv[])
{
	int disk = atoi(argv[1]);
	int actual_sector = FIRST_SECTOR;
	char eraser_buffer[SECTOR_SIZE];
	struct SECBOOTPART sbp;

	sprintf(sbp.nombre_particion, "part%d", disk);

	sbp.sec_inicpart = 1;		// 1 sector 
	sbp.sec_res = 1;		// 1 sector reservado para el sector de boot de la partición
	sbp.sec_mapa_bits_area_nodos_i = 1;// 1 sector
	sbp.sec_mapa_bits_bloques = 6;	// 6 sectores
	sbp.sec_tabla_nodos_i = 3;	// 3 sectores
	sbp.sec_log_particion = 43199;		// 43199 sectores
	sbp.sec_x_bloque = 2;			// 2 sectores por bloque
	sbp.heads = 8;				// 8 superficies				
	sbp.cyls = 200;				// 200 cilindros
	sbp.secfis = 27;				// 27 sectores por track

	for(int i = 0; i < 484; i++)
		sbp.restante[i] = 'A';

	// Create eraser_buffer
	for(int i = 0; i < SECTOR_SIZE; i++)
		eraser_buffer[i] = 0x0;

	// Write sectboot in sector
	vdwritesector(disk, 0, 0, actual_sector, sbp.sec_inicpart, (char*)&sbp);

	// Change sector to write
	actual_sector += sbp.sec_res; // secbootpart's size is one

	// Format i nodes table using buffer with zeros
	vdwritesector(disk, 0, 0, actual_sector, sbp.sec_mapa_bits_area_nodos_i, (char*)&eraser_buffer);

	// Change sector to write
	actual_sector += sbp.sec_mapa_bits_area_nodos_i;

	// Format block table using buffer with zeros
	vdwritesector(disk, 0, 0, actual_sector, sbp.sec_mapa_bits_bloques, (char*)&eraser_buffer);

	return 0;
}