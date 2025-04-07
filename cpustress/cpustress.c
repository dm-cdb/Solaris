/* This program will stress your cpu
* You can set the load value
* load value must be over 100 000 to have significant impact 
* Compile with gcc -o cpustress -lm cpustress.c
* Written by C. de Balorre the 22/08/2003
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define MAXMIN 60

void help(int iOpt);
double sample(int iBeat);

int  main(int argc, char **argv){

clock_t start, end;
double i, load=0.0;
long diffclk;
int beat;
uint flag_l=0, flag_t=0; 

int ch;
extern char *optarg;
extern int optind, optopt;

/* Parse command line */
if (argc  > 3)  {                                                            
printf("Error : To many parameters.\n");
help(optopt);
}                                                            
while ((ch = getopt(argc, argv, "l:t:")) != -1)
      switch (ch) {
        case 'l':
                if(atoi(optarg) < 100){
                fprintf(stderr,"Option -%c must be over 100.\n", optopt);
                help(optopt);}
            load=atol(optarg);
	    flag_l++;	
            break;
	case 't':
                if(atoi(optarg) < 1){
                fprintf(stderr,"Option -%c must be over 1.\n", optopt);
                help(optopt);}
		if(atoi(optarg) > MAXMIN){
                fprintf(stderr,"Option -%c must not be over %u.\n", optopt, MAXMIN);
                help(optopt);}

            beat=atoi(optarg);
	    flag_t++;
            break;
	case ':':
                fprintf(stderr,"Option -%c requires an operand\n", optopt);
                help(optopt);
         case '?':
            fprintf(stderr,"Unrecognised option: -%c\n", optopt);
            help(optopt);
        break;
        default:
        help(optopt);
      }


if ((load < 1.0) && (flag_t > 0))
load = sample(beat);
if (!load)
load = 100000.0;

printf("Using load of %0.f...\n", load);
/* Initialize clock */
start = clock();

for (i = 1.5; i <= load; ++i )
(void)log (i);

end = clock();

diffclk = end - start;
printf("Processor time used = %.2f secs\n", ((float)diffclk)/((float)CLOCKS_PER_SEC));
return 0;
}

double sample(int iBeat) {
	clock_t start, end;
	double i, load=10000000.0;
	long diffclk;

	printf("Sampling load for %u minutes...\n", iBeat);
	start = clock();

	for (i = 1.5; i <= load; ++i )
	(void)log (i);

	end = clock();
	diffclk = (end - start) / ((long)CLOCKS_PER_SEC);
	load = (load /(double)diffclk) * ((double)(iBeat * 60));
	return load;
}

void help(iOpt) {
        fprintf(stderr, "Invalid usage or option -%c\n",iOpt);
        fprintf(stderr, "Usage : cpustress [-l nnnnn] | [-t n minutes]\n");
   exit(1);
}

