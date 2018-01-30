include Make.defines

PROGS =	 simhttp simget

OPTIONS = -DUNIX  -DUSE_SIGACTION -DANSI


COBJECTS =	DieWithError.o HandleTCPClient.o 
CSOURCES =	DieWithError.c HandleTCPClient.c

CPLUSOBJECTS = 

COMMONSOURCES =

CPLUSSOURCES =

all:	${PROGS}


simhttp:	simhttp.o $(CPLUSOBJECTS) $(COBJECTS)
		${CC} $(INCLUDES) ${LINKOPTIONS} $@ simhttp.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(LINKFLAGS)

simget:		simget.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(COMMONSOURCES) $(SOURCES)
		${CC} $(INCLUDES) ${LINKOPTIONS}  $@ simget.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(LINKFLAGS)


.cc.o:	$(HEADERS)
	$(CPLUS) $(CPLUSFLAGS) $(OPTIONS) $<

.c.o:	$(HEADERS)
	$(CC) $(CFLAGS) $(OPTIONS) $<



backup:
	rm -f tcpecho.tar.gz
	rm -f tcpecho.tar
	tar -cf tcpecho.tar *
	gzip -f tcpecho.tar

clean:
		rm -f ${PROGS} ${CLEANFILES}

depend:
		makedepend -g TCPEchoClient.c TCPEchoServer.c -g simget.c simhttp.c $(INCLUDES) $(CFLAGS) $(HEADERS) $(SOURCES) $(COMMONSOURCES) $(CSOURCES)
#		mkdep $(CFLAGS) $(HEADERS) $(SOURCES) $(COMMONSOURCES) $(CSOURCES)

# DO NOT DELETE

simget.o: /usr/include/stdio.h /usr/include/features.h
simget.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
simget.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
simget.o: /usr/include/linux/stddef.h /usr/include/bits/types.h
simget.o: /usr/include/bits/typesizes.h /usr/include/libio.h
simget.o: /usr/include/_G_config.h /usr/include/wchar.h
simget.o: /usr/include/bits/wchar.h /usr/include/gconv.h
#simget.o: /usr/lib/gcc/i386-redhat-linux/4.1.1/include/stdarg.h
simget.o: /usr/include/bits/stdio_lim.h
simget.o: /usr/include/bits/sys_errlist.h /usr/include/sys/socket.h
simget.o: /usr/include/sys/uio.h /usr/include/sys/types.h
simget.o: /usr/include/linux/time.h /usr/include/linux/types.h
simget.o: /usr/include/linux/posix_types.h /usr/include/linux/stddef.h
simget.o: /usr/include/asm/posix_types.h /usr/include/asm/types.h
simget.o: /usr/include/endian.h /usr/include/bits/endian.h
simget.o: /usr/include/sys/select.h /usr/include/bits/select.h
simget.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
simget.o: /usr/include/sys/sysmacros.h
simget.o: /usr/include/bits/pthreadtypes.h /usr/include/bits/uio.h
simget.o: /usr/include/bits/socket.h /usr/include/linux/limits.h
simget.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
simget.o: /usr/include/asm/sockios.h /usr/include/arpa/inet.h
simget.o: /usr/include/netinet/in.h /usr/include/stdint.h
simget.o: /usr/include/bits/in.h /usr/include/bits/byteswap.h
simget.o: /usr/include/netdb.h /usr/include/rpc/netdb.h
simget.o: /usr/include/bits/netdb.h /usr/include/stdlib.h
simget.o: /usr/include/alloca.h /usr/include/string.h
simget.o: /usr/include/linux/unistd.h /usr/include/asm/unistd.h
simhttp.o: /usr/include/stdio.h /usr/include/features.h
simhttp.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
simhttp.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
simhttp.o: /usr/include/linux/stddef.h /usr/include/bits/types.h
simhttp.o: /usr/include/bits/typesizes.h /usr/include/libio.h
simhttp.o: /usr/include/_G_config.h /usr/include/wchar.h
simhttp.o: /usr/include/bits/wchar.h /usr/include/gconv.h
#simhttp.o: /usr/lib/gcc/i386-redhat-linux/4.1.1/include/stdarg.h
simhttp.o: /usr/include/bits/stdio_lim.h
simhttp.o: /usr/include/bits/sys_errlist.h /usr/include/sys/socket.h
simhttp.o: /usr/include/sys/uio.h /usr/include/sys/types.h
simhttp.o: /usr/include/linux/time.h /usr/include/linux/types.h
simhttp.o: /usr/include/linux/posix_types.h /usr/include/linux/stddef.h
simhttp.o: /usr/include/asm/posix_types.h /usr/include/asm/types.h
simhttp.o: /usr/include/endian.h /usr/include/bits/endian.h
simhttp.o: /usr/include/sys/select.h /usr/include/bits/select.h
simhttp.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
simhttp.o: /usr/include/sys/sysmacros.h
simhttp.o: /usr/include/bits/pthreadtypes.h /usr/include/bits/uio.h
simhttp.o: /usr/include/bits/socket.h /usr/include/linux/limits.h
simhttp.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
simhttp.o: /usr/include/asm/sockios.h /usr/include/arpa/inet.h
simhttp.o: /usr/include/netinet/in.h /usr/include/stdint.h
simhttp.o: /usr/include/bits/in.h /usr/include/bits/byteswap.h
simhttp.o: /usr/include/stdlib.h /usr/include/alloca.h
simhttp.o: /usr/include/string.h /usr/include/linux/unistd.h
simhttp.o: /usr/include/asm/unistd.h
DieWithError.o: /usr/include/stdio.h /usr/include/features.h
DieWithError.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
DieWithError.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
DieWithError.o: /usr/include/linux/stddef.h /usr/include/bits/types.h
DieWithError.o: /usr/include/bits/typesizes.h /usr/include/libio.h
DieWithError.o: /usr/include/_G_config.h /usr/include/wchar.h
DieWithError.o: /usr/include/bits/wchar.h /usr/include/gconv.h
#DieWithError.o: /usr/lib/gcc/i386-redhat-linux/4.1.1/include/stdarg.h
DieWithError.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
DieWithError.o: /usr/include/stdlib.h /usr/include/sys/types.h
DieWithError.o: /usr/include/linux/time.h /usr/include/linux/types.h
DieWithError.o: /usr/include/linux/posix_types.h /usr/include/linux/stddef.h
DieWithError.o: /usr/include/asm/posix_types.h /usr/include/asm/types.h
DieWithError.o: /usr/include/endian.h /usr/include/bits/endian.h
DieWithError.o: /usr/include/sys/select.h /usr/include/bits/select.h
DieWithError.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
DieWithError.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
DieWithError.o: /usr/include/alloca.h
HandleTCPClient.o: /usr/include/stdio.h /usr/include/features.h
HandleTCPClient.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
HandleTCPClient.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-32.h
HandleTCPClient.o: /usr/include/linux/stddef.h /usr/include/bits/types.h
HandleTCPClient.o: /usr/include/bits/typesizes.h /usr/include/libio.h
HandleTCPClient.o: /usr/include/_G_config.h /usr/include/wchar.h
HandleTCPClient.o: /usr/include/bits/wchar.h /usr/include/gconv.h
#HandleTCPClient.o: /usr/lib/gcc/i386-redhat-linux/4.1.1/include/stdarg.h
HandleTCPClient.o: /usr/include/bits/stdio_lim.h
HandleTCPClient.o: /usr/include/bits/sys_errlist.h /usr/include/sys/socket.h
HandleTCPClient.o: /usr/include/sys/uio.h /usr/include/sys/types.h
HandleTCPClient.o: /usr/include/linux/time.h /usr/include/linux/types.h
HandleTCPClient.o: /usr/include/linux/posix_types.h
HandleTCPClient.o: /usr/include/linux/stddef.h /usr/include/asm/posix_types.h
HandleTCPClient.o: /usr/include/asm/types.h /usr/include/endian.h
HandleTCPClient.o: /usr/include/bits/endian.h /usr/include/sys/select.h
HandleTCPClient.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
HandleTCPClient.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
HandleTCPClient.o: /usr/include/bits/pthreadtypes.h /usr/include/bits/uio.h
HandleTCPClient.o: /usr/include/bits/socket.h /usr/include/linux/limits.h
HandleTCPClient.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
HandleTCPClient.o: /usr/include/asm/sockios.h /usr/include/linux/unistd.h
HandleTCPClient.o: /usr/include/asm/unistd.h
