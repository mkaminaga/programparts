# makefile
# @date 2019-10-13 17:41:15
# Copyright 2019 Mamoru Kaminaga
CC = "$(VCINSTALLDIR)\cl.exe"
LINK = "$(VCINSTALLDIR)\link.exe"

OBJDIR = build
TARGET = main.exe
PDB = main.pdb
MAP = main.map
SRC = main.cc
OBJ = $(OBJDIR)/main.obj

CPPFLAGS = /nologo /W4 /Zi /Od /Fa /EHsc /Fd"$(OBJDIR)/"
LFLAGS = "kernel32.lib" "user32.lib" /NOLOGO /SUBSYSTEM:CONSOLE /DEBUG \
	/PDB:"$(PDB)" /MAP:"$(MAP)"

ALL: $(TARGET)

$(TARGET): $(OBJ)
	$(LINK) $(LFLAGS) /OUT:$(TARGET) $(OBJ)

.cc{$(OBJDIR)}.obj:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	$(CC) $(CPPFLAGS) /Fo"$(OBJDIR)\\" /c $<

clean:
	rm $(OBJ) $(TARGET) *.exe *.map *.pdb *.ilk *.obj *.lib *.dll *.exp
