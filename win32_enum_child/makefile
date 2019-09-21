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
SRC = main.cc
OBJ = $(OBJDIR)/main.obj

# Debug build
CPPFLAGS = /nologo /W4 /Zi /O2 /MTd /D"UNICODE" /D"_UNICODE" /D"DEBUG" /DEBUG\
					 /EHsc /Fd"$(OBJDIR)/" /I"$(LIBRARIES)\libpng"
LFLAGS = "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" \
				 "advapi32.lib" "shell32.lib" "ole32.lib"	"oleaut32.lib" "uuid.lib"\
				 "odbc32.lib" "odbccp32.lib" "libcmtd.lib" \
				 /NOLOGO /SUBSYSTEM:WINDOWS /DEBUG /PDB:"$(PDB)" /MAP:"$(MAP)"

ALL: $(TARGET)

$(TARGET): $(OBJ) $(RES)
	$(LINK) $(LFLAGS) /OUT:$(TARGET) $(OBJ) $(RES)

.cc{$(OBJDIR)}.obj:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	$(CC) $(CPPFLAGS) /Fo"$(OBJDIR)\\" /c $<

clean:
	rm $(OBJ) $(TARGET) *.map *.pdb *.ilk *.obj *.lib *.dll *.exp
