/* Written by Christian de Balorre the 03/09/2003
*  Compile with "gcc -o fkcpy fkcpy_sol.c"
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <string.h>


#define BUFFER  256

void help(void);

int main (int argc, char *argv[])
{

struct stat myStat;
char src[BUFFER];
char dst[BUFFER];
char * buf;
char buf1[3]="- ";
char buf2[3]="* ";
char buf3[4]="* -";

long ioblk, blks, fsize, fperc, finc;
float time0, transf;
int fd1, fd2, n;
int ret, buf_size, test;

hrtime_t start, end;

memset(src, 0, sizeof(src));
memset(dst, 0, sizeof(dst));
memset(myStat, 0, sizeof(myStat));

if (argc != 3){
help();
}

if ((sizeof(argv[1]) > BUFFER) || (sizeof(argv[2]) > BUFFER)){
printf("Buffer overrun\n");
exit(1);
}

strcpy(src, argv[1]);
strcpy(dst, argv[2]);
if (!(strcmp(dst, src))){
printf("Error: same source and destination files\n");
help();
}

if (!(stat(src, & myStat))){
ioblk=myStat.st_blksize;
blks=myStat.st_blocks;
fsize=512 * blks;
fperc=(fsize / 10);
}
else{
perror(src);
exit(1);
}

if(!(buf = (char *) malloc(ioblk))) {
printf("Oooops, bye!\n");
perror("Malloc");
exit(1);
}
else {
buf_size = ioblk;
}

if ((fd1=open(src,O_RDONLY)) == -1){
perror(src);
exit(1);
}
if ((fd2=open(dst, O_RDWR | O_TRUNC | O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1){
perror(dst);
exit(1);
}

close(fd2);

fd2=open(dst, O_RDWR | O_APPEND);

printf("Copying file %s using buffer of %u bytes...\n\n", src, buf_size);
write(STDOUT_FILENO, buf1, sizeof(buf1));

start = gethrtime();

do {
n = read(fd1, buf, buf_size);
	if (write(fd2, buf, n) != n) {
	perror("Write error");
	}
finc+=n;
if (finc > fperc) {
	finc = 0;
	write(STDOUT_FILENO, buf2, sizeof(buf2));
}}
while (n > 0);

write(STDOUT_FILENO, buf3, sizeof(buf3));
end = gethrtime();
time0=((float)(end - start))/1000000000;
printf("\n%u bytes from %s copied in %.2f sec\n", fsize, src, time0);
if ( time0 > 0.0 ){
transf = (float)fsize / time0 ;
printf("Xfer speed : %.0f bytes/sec\n", transf);
}
else
printf("Xfer speed : %u bytes/sec\n", fsize);

free(buf);
close(fd1);
close(fd2);

return 0;
}

void help(void){
printf("fkcpy usage:\n");
printf("fkcpy src dest\n");
exit(1);
}

