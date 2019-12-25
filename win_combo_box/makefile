# makefile
# date 2019-12-25
# Copyright 2017 Mamoru Kaminaga
CC = "$(VCINSTALLDIR)\cl.exe"
LINK = "$(VCINSTALLDIR)\link.exe"

OBJDIR = build
TARGET = main.exe
PDB = main.pdb
MAP = main.map
RES = resource.res
SRC = main.cc util.cc
OBJ = $(OBJDIR)/main.obj $(OBJDIR)/util.obj

CPPFLAGS = /nologo /W4 /Zi /O2 /EHsc /Fd"$(OBJDIR)/" \
					 /D"WINVER=_WIN32_WINNT_WINBLUE" /D"NTDDI_VERSION=NTDDI_WINBLUE" \
					 /D"_WIN32_WINNT=_WIN32_WINNT_WINBLUE" /D"DEBUG"
LFLAGS = "kernel32.lib" "user32.lib" "comctl32.lib" "shell32.lib" "ole32.lib" \
				 /NOLOGO /SUBSYSTEM:WINDOWS /DEBUG /PDB:"$(PDB)" /MAP:"$(MAP)"

ALL: $(TARGET)

$(TARGET): $(OBJ) $(RES)
	$(LINK) $(LFLAGS) /OUT:$(TARGET) $(OBJ) $(RES)

.cc{$(OBJDIR)}.obj:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	$(CC) $(CPPFLAGS) /Fo"$(OBJDIR)\\" /c $<

clean:
	rm -rf $(TARGET) || true
	rm -rf $(OBJ) || true
	rm -rf *.dll || true
	rm -rf *.exe || true
	rm -rf *.exp || true
	rm -rf *.ilk || true
	rm -rf *.lib || true
	rm -rf *.map || true
	rm -rf *.obj || true
	rm -rf *.pdb || true
