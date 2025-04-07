/* Written by Christian de Balorre the 14/08/2003 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

#define BUFFER 32
#define DLIMIT 3650

void help(int iOpt);
time_t decoffset(long lOffset, long epoch);
time_t incoffset(long lOffset, long epoch);

int main (int argc, char *argv[])
{

int ch;
extern char *optarg;
extern int optind, optopt;
int mflag, pflag, lflag;

long lNow, lDay;
time_t now, lDate;
struct tm * myTm;
char newFDate[BUFFER];

/* Initialize variable */
memset (&mflag,0,sizeof(mflag));
memset (&pflag,0,sizeof(pflag));
memset (&lflag,0,sizeof(lflag));
memset (newFDate,0,sizeof(newFDate));

/* Time serial in sec since 1970 */
now=time((time_t *)NULL);
lNow=(long) now;

/* test de la ligne de commande */

while (( ch = getopt(argc, argv, "m:p:l")) != -1)
switch (ch) {
        case 'm':
                mflag++;
                if (pflag){
                fprintf(stderr,"You can't use option -m and -p at the same time\n");
                help(optopt);
                exit(2);
                }
                lDay=atol(optarg);
                if ( lDay > DLIMIT ){
                printf("Please do not exceed limit\n");
                exit(2);
                }
                lDate=decoffset(lDay, lNow);
                continue;
        case 'p':
                pflag++;
                if (mflag){
                fprintf(stderr,"You can't use option -m and -p at the same time\n");
                help(optopt);
                exit(2);
                }
                lDay=atol(optarg);
                if ( lDay > DLIMIT) {
                printf("Please do not exceed limit\n");
                exit(2);
                }
                lDate=incoffset(lDay, lNow);
                continue;
        case 'l':
                lflag++;
                break;
        default:
                help(optopt);
        }

myTm=localtime(&lDate);
if (lflag){
strftime(newFDate, BUFFER, "%m/%d/%Y", myTm);
}
else {
strftime(newFDate, BUFFER, "%d/%m/%Y", myTm);
}
printf("%s\n", newFDate);
return 0;
}

/* Functions */

time_t decoffset(long lOffset, long epoch) {
long date;
date = epoch - (lOffset * 86400);
return (time_t)date;
}

time_t incoffset(long lOffset, long epoch) {
long date;
date = epoch + (lOffset * 86400);
return (time_t)date;
}


/* Affiche l'aide en ligne */

void help(iOpt) {
        fprintf(stderr, "Invalid option -%c\n",iOpt);
        fprintf(stderr, "Usage : dayof -m offset | -p offset -l\n");
        fprintf(stderr, "offset are expressed in days\n");
        exit(1);
}

