/* Written by Christian de Balorre the 14/08/2003 */

#include <sys/param.h>
#include <limits.h>
#include <kstat.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/systeminfo.h>

/* Compile with "gcc -o confdump -lkstat confdump.c" */

main(void){

    kstat_ctl_t *kc;
    kstat_t *ksp;
    kstat_named_t *kn0, *kn1, *kn2, *kn3, *kn4;
    int pagesize;
	
    double bytesFree, MbytesFree, PhysMem;
    char sinfo1[257], sinfo2[257], sinfo3[257], sinfo4[257], sinfo5[257];
    long count, count0;
    long nproc, nproc_line;
     
    memset(sinfo1,0,sizeof(sinfo1));
    memset(sinfo2,0,sizeof(sinfo2));
    memset(sinfo3,0,sizeof(sinfo3));
    memset(sinfo4,0,sizeof(sinfo4));
    memset(sinfo5,0,sizeof(sinfo5));

    if (!(kc = kstat_open())){
      perror("kstat_open");
      exit(1);
    }
    
    if (!(ksp = kstat_lookup(kc, "unix", 0, "system_pages"))){
      perror("kstat_lookup");
      exit(1);
    }

    if (kstat_read(kc, ksp,0) == -1) {
      perror("kstat_read");
      exit(1);
    }
    kn0 = kstat_data_lookup(ksp, "physmem");
    kn1 = kstat_data_lookup(ksp, "freemem");
   
    pagesize = getpagesize();
    PhysMem = ((double)kn0 ->value.ul * (double)pagesize) / 1048576;
    MbytesFree = ((double)kn1->value.ul * (double)pagesize) / 1048576;

    printf("Memory info :\n");
    printf("PhysMem   : %.2f MB\n", PhysMem);
    printf("FreeMem   : %.2f MB\n", MbytesFree);

    memset(ksp, 0, sizeof(ksp));
    
    if (!(ksp = kstat_lookup(kc, "cpu_info", -1, NULL))){
      perror("kstat_lookup");
      exit(1);
    }

    if (kstat_read(kc, ksp,0) == -1) {
      perror("kstat_read");
      exit(1);
    }
    
    kn2 = kstat_data_lookup(ksp, "clock_MHz");
    kn3 = kstat_data_lookup(ksp, "cpu_type");
    kn4 = kstat_data_lookup(ksp, "state");
    
    nproc = sysconf(_SC_NPROCESSORS_CONF);
    nproc_line = sysconf(_SC_NPROCESSORS_ONLN);

    printf("\nCpu info  :\n");
    printf("Nbre proc : %d\n", nproc);
    printf("On-line   : %d\n", nproc_line);
    printf("\nCpu_clock : %d MHz\n",kn2->value.i32);
    printf("Cpu type  : %s\n", kn3->value.c);
    printf("Cpu state : %s\n", kn4->value.c);

   count=sysinfo(SI_SYSNAME, sinfo1,257); 
   count=sysinfo(SI_RELEASE, sinfo2,257);
   count=sysinfo(SI_ARCHITECTURE, sinfo3,257);
   count=sysinfo(SI_HW_PROVIDER, sinfo4,257);
   count=sysinfo(SI_HW_SERIAL, sinfo5,257);

    printf("\nPlate-forme info:\n");
    printf("OS        : %s %s\n", sinfo1, sinfo2);
    printf("Archi     : %s\n", sinfo3);
    printf("Manuf     : %s\n", sinfo4);
    printf("Serial    : %s\n", sinfo5);

exit(0);
}

