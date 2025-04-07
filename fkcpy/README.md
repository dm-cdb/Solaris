Funky copy is rather useless an utility, but I think it gives cool output :

Output exemple :

# ./fcpy DSS.zip DSS.new.zip
Copying file DSS.zip using buffer of 8192 bytes...

-- * * * * * * * * * * - <br>
34201600 bytes of DSS.zip copied in 4.39 sec
Xfer speed : 7793310 bytes/sec

Note :

I use this utility to tune nfs servers and the tcp/ip stack.
This utility uses dynamic buffering, but it should always be 8192 bytes...
It also uses the gethrtime() function, which is Solaris proprietary.

Compilation :

gcc -o fkcpy fkcpy.c

Argument :

fkcpy source target
