#
# Created by gmakemake (Ubuntu Jul 25 2014) on Sat Oct  6 05:44:27 2018
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s .S
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.S.s:
		$(CPP) -o $*.s $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c
CPP = $(CPP) $(CPPFLAGS)
########## Flags from header.mak

CFLAGS = -ggdb -Wall -std=c99 -pedantic -Wextra
CLIBFLAGS =

########## End of flags from header.mak


CPP_FILES =	
C_FILES =	scanner.c classification.c matrixCreation.c tokenize.c
PS_FILES =	
S_FILES =	
H_FILES =	scanner.h classes.h matrix.h matrixCreation.h classification.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	scanner.o matrixCreation.o classification.o

#
# Main targets
#

all:	tokenize 

tokenize:	tokenize.o $(OBJFILES)
	$(CC) $(CFLAGS) -o tokenize tokenize.o $(OBJFILES) $(CLIBFLAGS)

#
# Dependencies
#

matrixCreation.o:	matrix.h
classification.o:       classification.h
scanner.o:		scanner.h
tokenize.o:	scanner.h classes.h matrix.h matrixCreation.h classification.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm -f $(OBJFILES) tokenize.o core

realclean:        clean
	-/bin/rm -f tokenize 
