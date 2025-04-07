This utility enables you to manipulate dates :

Output exemple :

# ./dayof -m 10
03/08/2003

# ./dayof -p 20 -l
09/02/2003

Note :

Compiled and tested ok on Linux Redhat 8 as well.
I use this program for exemple in Netbackup script to retrieve the backup summary of the last 30 days.

Compilation :

gcc -o dayof dayof.c

Argument :

-m substracts n days to current date, -p adds n days, -l prints out US date format.
-m & -p are mutually exclusive arguments.
