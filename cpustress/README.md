This utility stresses the CPU :

Output exemple :

./cpustress -t 1
Sampling load for 1 minutes...
Using load of 150000000...
Processor time used = 60.47 secs

Note :

Compiled and tested ok on Linux Redhat 8 as well.

Compilation :

gcc -o cpustress -lm cpustress.c

Argument :

[-l nnnnn] | [-t n minutes]

-l takes a brute load as argument
-t takes n minutes as argument
If no argument is given, calculation will be based on a brute load of 100 000.

This program performs a log calculation within a loop ; The load is basically the number of loops.
The load given by sampling yields only a rough estimation of the time that will be spent by the process.
I have noticed that the sampling is more accurate on Sparc processor than Intel : this is probably because a Sparc is much more efficient under heavy load.
Maximum is 60 minutes of test. You can change the MAXMIN value in the source to raise this figure.
