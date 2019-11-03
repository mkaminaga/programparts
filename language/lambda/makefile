# makefile
# date 2019-9-17
# Copyright 2017 Mamoru Kaminaga
CC = "$(VCINSTALLDIR)\cl.exe"
LINK = "$(VCINSTALLDIR)\link.exe"

OBJDIR = build
TARGET = main.exe
PDB = main.pdb
MAP = main.map
RES =
SRC = main.cc
OBJ = $(OBJDIR)/main.obj

CPPFLAGS = /nologo /W4 /Zi /O2 /EHsc /Fd"$(OBJDIR)/" /D"UNICODE" /D"_UNICODE" \
					 /D"WINVER=_WIN32_WINNT_WINBLUE" /D"NTDDI_VERSION=NTDDI_WINBLUE" \
					 /D"_WIN32_WINNT=_WIN32_WINNT_WINBLUE" /D"DEBUG"
LFLAGS = "kernel32.lib" "user32.lib" "comctl32.lib" "shell32.lib"\
				 /NOLOGO /SUBSYSTEM:CONSOLE /DEBUG /PDB:"$(PDB)" /MAP:"$(MAP)"

ALL: $(TARGET)

$(TARGET): $(OBJ) $(RES)
	$(LINK) $(LFLAGS) /OUT:$(TARGET) $(OBJ) $(RES)

{../win32_edit_mini}.cc{$(OBJDIR)}.obj:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	$(CC) $(CPPFLAGS) /Fo"$(OBJDIR)\\" /c $<

.cc{$(OBJDIR)}.obj:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	$(CC) $(CPPFLAGS) /Fo"$(OBJDIR)\\" /c $<

clean:
	rm $(OBJ) $(TARGET) *.exe *.map *.pdb *.ilk *.obj *.lib *.dll *.exp *.res
