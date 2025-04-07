Condump

This utility prints out a summary of a system harware.

Output exemple :

# ./condump
Memory info :
PhysMem : 243.18 MB
FreeMem : 128.91 MB

Cpu info :
Nbre proc : 1
On-line : 1

Cpu_clock : 360 MHz
Cpu type : sparcv9
Cpu state : on-line

Plate-forme info:
OS : SunOS 5.9
Archi : sparc
Manuf : Sun_Microsystems
Serial : 2159045864

# ./confdump
Memory info :
PhysMem : 504.48 MB
FreeMem : 421.19 MB

Cpu info :
Nbre proc : 1
On-line : 1

Cpu_clock : 500 MHz
Cpu type : i386
Cpu state : on-line

Plate-forme info:
OS : SunOS 5.9
Archi : i386
Manuf : COMPAQ
Serial : 696801395

Note :

This utility will pool only the first processor. Since I don't have any smp Solaris machine at hand yet, I am not be able to test pooling of several proc.

This program makes an intensive use of kstat library, which is proprietary to SUN.

Compilation :

gcc -o confdump -lkstat confdump.c
 
Argument :
No command line argument.
