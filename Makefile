CC=gcc
CCFLAGS=-I$(HDRDIR) -O2 -lm

HDRDIR=include/

SRCDIR=src/
SRCFILE=*.c

LISTDIR=list/
NEWFDIR=newf/
REMFDIR=remf/
NEWDDIR=newd/
HEXDUMPDIR=hexdump/
CALCDIR=calc/
RPNSDIR=rpns/

OUTDIR=bin/
LISTOUT=list
NEWFOUT=newf
REMFOUT=remf
NEWDOUT=newd
HEXDUMPOUT=hexdump
CALCOUT=calc
RPNSOUT=rpns

all:
	clear

	rm bin/*
	$(CC) -o $(OUTDIR)$(LISTOUT) $(SRCDIR)$(LISTDIR)$(SRCFILE) $(CCFLAGS)
	$(CC) -o $(OUTDIR)$(NEWFOUT) $(SRCDIR)$(NEWFDIR)$(SRCFILE) $(CCFLAGS)
	$(CC) -o $(OUTDIR)$(REMFOUT) $(SRCDIR)$(REMFDIR)$(SRCFILE) $(CCFLAGS)
	$(CC) -o $(OUTDIR)$(NEWDOUT) $(SRCDIR)$(NEWDDIR)$(SRCFILE) $(CCFLAGS)
	$(CC) -o $(OUTDIR)$(HEXDUMPOUT) $(SRCDIR)$(HEXDUMPDIR)$(SRCFILE) $(CCFLAGS)
	$(CC) -o $(OUTDIR)$(CALCOUT) $(SRCDIR)$(CALCDIR)$(SRCFILE) $(CCFLAGS)
	$(CC) -o $(OUTDIR)$(RPNSOUT) $(SRCDIR)$(RPNSDIR)$(SRCFILE) $(CCFLAGS)
	zip -r bunnysuite.zip bin
