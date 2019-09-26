# makefile
# date 2019-9-25
# Copyright 2017 Mamoru Kaminaga
CC = "$(VCINSTALLDIR)\cl.exe"
LINK = "$(VCINSTALLDIR)\link.exe"

TARGET = main.exe
SRC = main.cc sub.cc
OBJ = main.obj sub.obj
MAP = main.map
PDB = main.pdb

CPPFLAGS = /nologo /W4 /EHsc /DUNICODE /D_UNICODE /Z7
LFLAGS = /NOLOGO /SUBSYSTEM:WINDOWS /MAP:$(MAP) /PDB:$(PDB)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(LINK) $(LFLAGS) /OUT:$(TARGET) $(OBJ)

.cc.obj:
	$(CC) $(CPPFLAGS) /c $<

clean:
	rm -f $(TARGET) $(OBJ) *.pdb *.map *.ilk
