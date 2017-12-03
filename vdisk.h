#define HEADS 8
#define SECTORS 27
#define CYLINDERS 200 

int vdcreat();
int vdopen();
int vdread();
int vdwrite();
int vdclose();
int vdseek();
int vdulink();

int setinode();

int searchinode();
int removeinode();

int isinodefree();
int nextinodefree();

int assigninode();
int unassigninode();

int isblockfree();
int nextfreeblock();

int assignblock();
int unassignblock();

int writeblock();
int readblock();

int vdwriteseclog(int unit, int sector, char* buffer);
int vdreadseclog(int unit, int sector, char* buffer);

int vdwritesector(int unit, int cylinder, int surface, int sector, int nsecs, char* buffer);
int vdreadsector(int unit, int cylinder, int surface, int sector, int nsecs, char* buffer);