his utility prints out the list of user/ID of a system :

Output exemple :

# ./enuser
Parsing uid...
root -> 0
daemon -> 1
bin -> 2
sys -> 3
adm -> 4
lp -> 71
uucp -> 5
nuucp -> 9
smmsp -> 25
listen -> 37
nobody -> 60001
noaccess -> 60002
nobody4 -> 65534
guestuser -> 1001
postgres -> 1002

Last UID in list: 1002.
Is next ID 1003 available ?
UID 1003 available.

Note :

Compiled and tested ok on Linux Redhat 8 as well.

Compilation :

gcc -o enuser enuser.c

 

Argument :

No command line argument.

 
