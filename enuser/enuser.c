/* Written by Christian de Balorre the 14/08/2003 */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>


int main (int argc, char *argv[])
{
uid_t uid=0;
struct passwd *my_passwd;

printf("Parsing uid...\n");
setpwent();
while ((my_passwd=getpwent()))
{
uid=my_passwd->pw_uid;
printf("%s -> %d\n", my_passwd->pw_name, (int) uid);
}
endpwent();
printf ("\nLast UID in list: %d.\n",(int) uid);
(int) uid++;
printf ("Is next ID %d available ? ...\n",(int) uid);


my_passwd = getpwuid(uid);
        if (my_passwd)
    {
        printf ("Login name : %s.\n", my_passwd->pw_name);
        printf ("UID : %d.\n", (int) (my_passwd->pw_uid));
        printf ("Error : uid %d already exists.\n", (int) uid);
        printf ("Please choose another uid.\n");
        exit (EXIT_FAILURE);
    }
        else
    {
        printf ("UID %d available.\n", (int) uid);
    }
return 0;
}
