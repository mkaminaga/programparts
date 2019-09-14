# makefile
# date 2017-12-07
# Copyright 2017 Mamoru Kaminaga
CC = "$(VCINSTALLDIR)\cl.exe"
LINK = "$(VCINSTALLDIR)\link.exe"

OBJDIR = build
TARGET = main.exe
PDB = main.pdb
MAP = main.map
RES = resource.res
SRC = main.cc
OBJ = $(OBJDIR)/main.obj
LIB1 = "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib"\
				"advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib"\
				"odbc32.lib" "odbccp32.lib" "comctl32.lib"

# Release build
#CPPFLAGS = /nologo /W4 /Zi /O2 /MT /D"UNICODE" /D"_UNICODE" /EHsc /Fd"$(OBJDIR)/"
#LFLAGS = $(LIB1) /NOLOGO /SUBSYSTEM:WINDOWS /PDB:"$(PDB)" /MAP:"$(MAP)"

# Debug build
CPPFLAGS = /nologo /W4 /Zi /O2 /MT /D"UNICODE" /D"_UNICODE" /D"DEBUG" /EHsc /Fd"$(OBJDIR)/"
LFLAGS = $(LIB1) /NOLOGO /SUBSYSTEM:WINDOWS /DEBUG /PDB:"$(PDB)" /MAP:"$(MAP)"

ALL: $(TARGET)

$(TARGET): $(OBJ) $(RES)
	$(LINK) $(LFLAGS) /OUT:$(TARGET) $(OBJ) $(RES)

.cc{$(OBJDIR)}.obj:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	$(CC) $(CPPFLAGS) /Fo"$(OBJDIR)\\" /c $<
