#
# Makefile
# Date 2019-10-02 18:22:39
# Copyright 2019 Mamoru Kaminaga
#
TARGET = main.exe
PDB = main.pdb
MAP = main.map
RES =
TMPDIR = build
SRC = main.cc
OBJ = $(TMPDIR)\main.obj

CC = "$(VCINSTALLDIR)\cl.exe"
LINK = "$(VCINSTALLDIR)\link.exe"

LIBS = "kernel32.lib" "user32.lib"
CPPFLAGS = /nologo /W4 /Zi /EHsc /MT /O1 /Fd"$(TMPDIR)/"
LFLAGS = $(LIBS) /NOLOGO /SUBSYSTEM:CONSOLE /DEBUG /PDB:"$(PDB)" /MAP:"$(MAP)"

all: $(TARGET)

$(TARGET): $(OBJ) $(RES)
	$(LINK) $(LFLAGS) /OUT:$(TARGET) /PDB:$(PDB)\
		/MAP:$(MAP) $(OBJ) $(RES)

.cc{$(TMPDIR)}.obj:
	@[ -d $(TMPDIR) ] || mkdir $(TMPDIR)
	$(CC) $(CPPFLAGS) /Fo"$(TMPDIR)\\" /c $<

clean:
	rm -f $(OBJ)
	rm -f $(TARGET)
	rm -f $(TMPDIR)/*
	rm -f *.dll
	rm -f *.exe
	rm -f *.exp
	rm -f *.ilk
	rm -f *.lib
	rm -f *.map
	rm -f *.obj
	rm -f *.pdb
	rm -f *.png
