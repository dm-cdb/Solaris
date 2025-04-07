/* Written by Christian de Balorre the 14/08/2003 */

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <shadow.h>
#include <libgen.h>
#include <grp.h>
#include <sys/stat.h>

#define BUF_USER                129
#define BUF_HOME                257
#define BUF_PASS                65
#define BUF_SH          65
#define BUF_COMM                65


void help(int iOpt);
void check_user(char *);
uid_t set_uid(void);
gid_t set_gid(uid_t, char*);
void check_uid(uid_t);
void check_gid(gid_t);
char *makepass(char *);
void makepwd(char *, char *, char *,char *,uid_t, gid_t, int);
void makesp(char *, char *, long);

int main (int argc, char *argv[])
{

char user[BUF_USER];
char home[BUF_HOME];
char pass[BUF_PASS];
char sh[BUF_SH];
char comm[BUF_COMM];
uid_t uid=0;
gid_t gid=0;
char *cry_pass;
time_t now;
long today;
size_t size;
int flag=0;

int ch;
extern char *optarg;
extern int optind, optopt;

memset (user,0,sizeof(user));
memset (home,0,sizeof(home));
memset (pass,0,sizeof(pass));
memset (sh,0,sizeof(sh));
memset (comm,0,sizeof(comm));

if (argc  <= 1)  {                                                            
printf("Error : no parameter entered on the command line.\n");
help(optopt);
}                                                            


      while ((ch = getopt(argc, argv, "c:p:u:d:g:s:m")) != -1)
      switch (ch) {
        case 'u':
                if(atoi(optarg) < 0){
                fprintf(stderr,"Option -%c must be over 0.\n", optopt);
                help(optopt);}
            uid=(uid_t)(atoi(optarg));
            continue;
        case 'g':
                if(atoi(optarg) < 0){
                fprintf(stderr,"Option -%c must be over 0.\n", optopt);
                help(optopt);}
            gid=(gid_t)(atoi(optarg));
            continue;
        case 'd':
            strcpy(home,optarg);
                if((size=strlen(home))> BUF_HOME){
                fprintf(stderr,"Option -%c too long ( > %u chars)\n", optopt, BUF_HOME);
                help(optopt);}
            continue;
        case 'p': 
		 strcpy(pass,optarg);
                if((size=strlen(pass))> BUF_PASS){
                fprintf(stderr,"Option -%c too long ( > %u chars)\n", optopt, BUF_PASS);
                help(optopt);}
            continue;
         case 's':
            strcpy(sh,optarg);
                if((size=strlen(sh))> BUF_SH){
                fprintf(stderr,"Option -%c too long ( > %u chars)\n", optopt, BUF_SH);
                help(optopt);}
            continue;
        case 'c':
            strcpy(comm,optarg);
                if((size=strlen(comm))> BUF_COMM){
                fprintf(stderr,"Option -%c too long ( > %u chars)\n", optopt, BUF_COMM);
                help(optopt);}
            continue;
	case 'm':
	     flag=1;
	     continue;
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
strcpy(user,argv[argc - 1]);
if((size=strlen(comm))> BUF_USER){
fprintf(stderr,"Option -%c too long ( > %u chars)\n", optopt, BUF_USER);
exit(1);}


if(user[0]){
check_user(user);
        }

if(!uid){
uid = set_uid();
        }

check_uid(uid);


if(!gid){
gid = set_gid(uid, user);
        }


check_gid(gid);


if(pass[0]){
cry_pass=makepass(pass);
        }
else {
strcpy(pass,"alea");
cry_pass=makepass(pass);
}

if(! sh[0]){
strcpy(sh,"/bin/sh");
        }

if(!home[0]){
strcpy(home,"/export/home/");
strcat(home,user);
        }

makepwd(user,sh,comm,home,(uid_t) uid,(gid_t) gid, flag);

now=time((time_t *)NULL);
today=((long) now)/86400;

makesp(user,cry_pass,today);

return 0;
}

/* here we begin functions  */

uid_t set_uid(){

uid_t uid=0;
struct passwd *my_passwd;

setpwent();

while ((my_passwd = getpwent()))
{
uid=my_passwd->pw_uid;
}

(int) uid++;

my_passwd = getpwuid(uid);
        if (my_passwd)
    {
        printf ("Login name : %s.\n", my_passwd->pw_name);
        printf ("UID : %d.\n", (int) (my_passwd->pw_uid));
        printf ("Error : uid %d already exists.\n", (int) uid);
        printf ("Please choose uid manually.\n");
        exit (EXIT_FAILURE);
    }
	
return uid;
}

gid_t set_gid(uid_t uid, char *user){

gid_t gid = (gid_t)uid;
struct group *my_group;
FILE *fp;
int i = 0;
char buf[64];

my_group = getgrgid(gid);
if (my_group){
	printf ("Group name : %s.\n", my_group->gr_name);
        printf ("GID : %d.\n", (int) (my_group->gr_gid));
        while(my_group->gr_mem[i]){
        printf ("Group member : %s.\n", my_group->gr_mem[i]);
        i++;
        }
	printf ("Error : gid %d already exist.\n", (int)gid);
	printf("Please choose gid manually.\n");
	exit (EXIT_FAILURE);
	}

sprintf(buf, "%s::%u:\n", user, (int)gid);
fp=fopen("/etc/group", "a");
fputs(buf, fp);
fclose(fp);
}



void makepwd(char *p_user,char *p_sh,char *p_comm,char *p_home,uid_t u_uid,gid_t g_gid,int flag){
FILE *fp;
FILE *fp1;

struct passwd n_passfile, *p_passfile;
p_passfile = &n_passfile;
n_passfile.pw_name=p_user;
n_passfile.pw_passwd="x";
n_passfile.pw_uid=u_uid;
n_passfile.pw_gid=g_gid;
n_passfile.pw_age=NULL;
n_passfile.pw_comment=NULL;
n_passfile.pw_gecos=p_comm;
n_passfile.pw_dir=p_home;
n_passfile.pw_shell=p_sh;

printf("Login : %s\n",p_passfile->pw_name);
printf("Uid : %u\n",(int) p_passfile->pw_uid);
printf("Gid : %u\n",(int) p_passfile->pw_gid);
printf("Gecos : %s\n",p_passfile->pw_gecos);
printf("Homedir : %s\n", p_passfile->pw_dir);
printf("Shell : %s\n", p_passfile->pw_shell);

fp = fopen( "/etc/passwd", "a");
putpwent(p_passfile,fp);
fclose(fp);

if (flag){
if (! mkdir(p_home,S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)){
chown(p_home,u_uid,g_gid);
}}
}

void makesp(char * p_user,char * p_cry_pass,long l_today){
FILE *fp;
time_t now=NULL;

struct spwd n_spfile, *p_spfile;
p_spfile=&n_spfile;
n_spfile.sp_namp=p_user;
n_spfile.sp_pwdp=p_cry_pass;
n_spfile.sp_lstchg=l_today;
n_spfile.sp_min=-1;
n_spfile.sp_max=-1;
n_spfile.sp_warn=-1;
n_spfile.sp_inact=-1;
n_spfile.sp_expire=-1;
n_spfile.sp_flag=0;

fp=fopen("/etc/shadow", "a");
putspent(p_spfile,fp);
fclose(fp);

}

char *makepass(char * p_pass){
        char alpha[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h',
'i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
        char num[]={'1','2','3','4','5','6','7','8','9'};
        char spechar[]={'#','%','$','@','&','*'};
        time_t now = NULL;
        float r = 0;
        unsigned int j = 0;
        unsigned int i = 0;
        char temp1[5];
        char temp2[4];
        char temp3[2];
        char p_sel[3];
        char * cry_pass;

srand((unsigned int) time(&now));
        for (i = 0; i < 2; i++){
        r = rand();
	  j = (r/32767)*51;
        *(p_sel + i)=alpha[j];
        }
memset(p_sel + 2,0,1);

memset(temp1,0,sizeof(temp1));
memset(temp2,0,sizeof(temp2));
memset(temp3,0,sizeof(temp3));

if(!strcmp(p_pass,"alea")){
        srand(((unsigned int) time(&now))+1000);
        for (i = 0; i < 4; i++){
        r = rand();
        j = (r/32767)*51;
        *(temp1 + i) = alpha[j];
        }
        for (i = 0; i < 3; i++){
        r = rand();
        j = (r/32767)*8;
        *(temp2 + i) = num[j];
        }
        for (i = 0; i < 1; i++){
        r = rand();
        j = (r/32767)*5;
        *(temp3 + i) = spechar[j];
        }
        strcpy(p_pass,temp1);
        strcat(p_pass,temp3);
        strcat(p_pass,temp2);
        p_pass[8] = 0;
        }
printf("Clear pass : %s\n",p_pass);
cry_pass=(char *)crypt(p_pass,p_sel);
printf("Crypted pass : %s\n",cry_pass);
return cry_pass;
}

/* check user function */

void check_user(char * p_user){
        struct passwd *my_passwd;
        my_passwd = getpwnam(p_user);
        if (my_passwd)
    {
        printf ("Login name : %s.\n", my_passwd->pw_name);
        printf ("UID : %d.\n", (int) (my_passwd->pw_uid));
        printf ("Error : user %s already exists.\n", p_user);
        printf ("Please choose another login.\n");
        exit (EXIT_FAILURE);
    }
}

void check_uid(uid_t i_uid){
        struct passwd *my_passwd;
        my_passwd = getpwuid(i_uid);
        if (my_passwd)
    {
        printf ("Login name : %s.\n", my_passwd->pw_name);
        printf ("UID : %d.\n", (int) (my_passwd->pw_uid));
        printf ("Error : uid %d already exists.\n", (int) i_uid);
        printf ("Please choose another uid.\n");
        exit (EXIT_FAILURE);
    }
}

void check_gid(gid_t i_gid){
        unsigned int i=0;
        struct group *my_group;
        my_group = getgrgid(i_gid);
        if (my_group){
        printf ("Group name : %s.\n", my_group->gr_name);
        printf ("GID : %d.\n", (int) (my_group->gr_gid));

        while(my_group->gr_mem[i]){
        printf ("Group member : %s.\n", my_group->gr_mem[i]);
        i++;
        }
        }
        else {
        printf ("Error : gid %d does not exists.\n", (int) i_gid);
        exit (EXIT_FAILURE);
    }
}

void help(iOpt) {
        fprintf(stderr, "Invalid option -%c\n",iOpt);
        fprintf(stderr, "Usage : userplus -u uid -g gid [-d homedir][-m] [-s shell] [-c gecos] [-p password] user\n");
   exit(1);
}

