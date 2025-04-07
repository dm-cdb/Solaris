his utility prints out the list of user/ID of a system :

Output exemple :

# ./enuser
Parsing uid... <br>
root -> 0 <br>
daemon -> 1 <br>
bin -> 2 <br>
sys -> 3 <br>
adm -> 4 <br>
lp -> 71 <br>
uucp -> 5 <br>
nuucp -> 9 <br>
smmsp -> 25 <br>
listen -> 37 <br>
nobody -> 60001 <br>
noaccess -> 60002 <br>
nobody4 -> 65534 <br>
guestuser -> 1001 <br>
postgres -> 1002 <br>

Last UID in list: 1002. <br>
Is next ID 1003 available ? <br>
UID 1003 available. <br>

Note :

Compiled and tested ok on Linux Redhat 8 as well.

Compilation :

gcc -o enuser enuser.c

 

Argument :

No command line argument.

 
