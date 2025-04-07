This utility basicaly does almost the same thing as useradd, plus it generates a password on command line :

Output exemple :

# ./userplus -m testuser
Group name : testuser.
GID : 1003.
Clear pass : lWbs$276
Crypted pass : srUTPjvZeAQ9E
Login : testuser
Uid : 1003
Gid : 1003
Gecos :
Homedir : /export/home/testuser
Shell : /bin/sh

Note :

I use this program in a "finish script" after installing Solaris to initialize some admin accounts.
There is no "skeleton" user profile created in home directory.
NOT compatible with NIS.
The code is not yet very secure : does not test extensively arguments. Use this program carefully.
A password is always created.

 

Compilation :

gcc -o userplus userplus.c

 

Argument :

-u uid -g gid take repectively the user id and group id.
-d /path_to_home -m indicates path of home directory and create it.
-s shell takes a shell.
-c "comment" takes a comment.
-p password generates random password when p is not set, or set a given password.
user username

Ex :

userplus -u 101 -g 101 -d /export/home/testuser1 -m -s /bin/sh -c "no comment" -p testuser1
userplus -u 102 -g 101 -d /export/home/testuser2 -m -s /bin/sh -c "no comment" -p mypass testuser2

 

 


