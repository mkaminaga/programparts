# makefile
# date 2019-9-25
# Copyright 2017 Mamoru Kaminaga
CC = "$(VCINSTALLDIR)\cl.exe"
LINK = "$(VCINSTALLDIR)\link.exe"

TARGET = main.exe
SRC = main.cc
OBJ = main.obj

CPPFLAGS = /nologo /EHsc /DUNICODE /D_UNICODE /MT
LFLAGS = /NOLOGO /SUBSYSTEM:WINDOWS /MAP

all: $(TARGET)

$(TARGET): $(OBJ)
	$(LINK) $(LFLAGS) /OUT:$(TARGET) $(OBJ)

.cc.obj:
	$(CC) $(CPPFLAGS) /c $<

clean:
	rm -f $(TARGET) $(OBJ) *.pdb *.map *.ilk
