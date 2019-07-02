#
# Makefile
# Date: 2019-07-02 10:38:40
# Copyright 2019 Mamoru Kaminaga
#
TARGET = main.exe
PDB = main.pdb
MAP = main.map
RES = resource.res
SRC = main.cc
TMPDIR = build
OBJ = $(TMPDIR)\main.obj

CC = "$(VCINSTALLDIR)\cl.exe"
LINK = "$(VCINSTALLDIR)\link.exe"

CPPFLAGS = /nologo /W4 /Zi /O2 /MT /EHsc /Fd"$(TMPDIR)/" /DUNICODE /D_UNICODE \
					 /DDEBUG
LFLAGS = "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" \
				 "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" \
				 "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" "libcmt.lib" \
				 /NOLOGO /SUBSYSTEM:WINDOWS /DEBUG

ALL: $(TARGET)

$(TARGET): $(OBJ) $(RES)
	$(LINK) $(LFLAGS) /OUT:$(TARGET) /PDB:"$(PDB)" /MAP:"$(MAP)" \
	$(OBJ) $(RES)

.cc{$(TMPDIR)}.obj:
	@[ -d $(TMPDIR) ] || mkdir $(TMPDIR)
	$(CC) $(CPPFLAGS) /Fo"$(TMPDIR)\\" /c $<

clean:
	rm $(TARGET) $(OBJ) $(TMPDIR)\* *.map *.pdb *.ilk *.obj *.lib
