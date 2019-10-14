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
SRC = main.cc util.cc ../win32_edit_mini/edit.cc \
			system_performance_monitor.cc \
			process_performance_monitor.cc
OBJ = $(OBJDIR)/main.obj $(OBJDIR)/util.obj $(OBJDIR)/edit.obj \
			$(OBJDIR)/system_performance_monitor.obj \
			$(OBJDIR)/process_performance_monitor.obj

CPPFLAGS = /nologo /W4 /Zi /O2 /D"UNICODE" /D"_UNICODE" /EHsc /Fd"$(OBJDIR)/"
LFLAGS = "kernel32.lib" "user32.lib" \
				 /NOLOGO /SUBSYSTEM:WINDOWS /DEBUG /PDB:"$(PDB)" /MAP:"$(MAP)"

ALL: $(TARGET)

$(TARGET): $(OBJ) $(RES)
	$(LINK) $(LFLAGS) /OUT:$(TARGET) $(OBJ) $(RES)
	nmake -f load.mk

{../win32_edit_mini}.cc{$(OBJDIR)}.obj:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	$(CC) $(CPPFLAGS) /Fo"$(OBJDIR)\\" /c $<

.cc{$(OBJDIR)}.obj:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	$(CC) $(CPPFLAGS) /Fo"$(OBJDIR)\\" /c $<

clean:
	rm $(OBJ) $(TARGET) *.exe *.map *.pdb *.ilk *.obj *.lib *.dll *.exp
