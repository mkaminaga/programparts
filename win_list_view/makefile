# makefile
# date 2019-9-17
# Copyright 2017 Mamoru Kaminaga
CC = "$(VCINSTALLDIR)\cl.exe"
LINK = "$(VCINSTALLDIR)\link.exe"

OBJDIR = build
TARGET = main.exe
PDB = main.pdb
MAP = main.map
RES = resource.res
SRC = main.cc util.cc ../list_view.cc \
			../win32_edit_mini/edit.cc
OBJ = $(OBJDIR)/main.obj $(OBJDIR)/util.obj $(OBJDIR)/list_view.obj \
			$(OBJDIR)/edit.obj

CPPFLAGS = /nologo /W4 /Zi /O2 /D"UNICODE" /D"_UNICODE" /D"DEBUG" /EHsc /Fd"$(OBJDIR)/"
LFLAGS = "kernel32.lib" "user32.lib" "comctl32.lib"\
				 /NOLOGO /SUBSYSTEM:WINDOWS /DEBUG /PDB:"$(PDB)" /MAP:"$(MAP)"

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
