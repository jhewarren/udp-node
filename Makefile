all:	udpc udps

udpc: udp_clnt.c
	gcc -Wall  $< -o $@

udps: udp_svr.c
	gcc -Wall  $< -o $@

clean:
	rm -f udpc udps *.o *~ core

