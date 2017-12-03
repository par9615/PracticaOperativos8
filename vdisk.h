#define HEADS 8
#define SECTORS 27
#define CYLINDERS 200 
#define SECTOR_SIZE 512

int vdwritesector(int unit, int cylinder, int surface, int sector, int nsecs, char* buffer);
int vdreadsector(int unit, int cylinder, int surface, int sector, int nsecs, char* buffer);