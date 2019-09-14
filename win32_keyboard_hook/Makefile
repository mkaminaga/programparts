#
# Makefile
# Date: 2019-07-02 10:38:40
# Copyright 2019 Mamoru Kaminaga
#
TARGET = main.exe
PDB = main.pdb
MAP = main.map
RES =
SRC = main.cc util.cc
OBJ = $(OBJDIR)\main.obj
DLL = util.dll
LIB2 = util.lib
OBJDIR = build

CC = "$(VCINSTALLDIR)\cl.exe"
LINK = "$(VCINSTALLDIR)\link.exe"
CPPFLAGS = /nologo /W4 /Zi /O2 /MT /EHsc /Fd"$(TMPDIR)/" /DUNICODE /D_UNICODE \
					 /DDEBUG
LIB1 = "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" \
			 "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" \
 			 "odbc32.lib" "odbccp32.lib" "libcmt.lib"
LFLAGS = $(LIB1) /NOLOGO /SUBSYSTEM:WINDOWS /DEBUG /PROFILE

ALL: $(TARGET)

$(TARGET): $(OBJ) $(LIB2) $(DLL) $(RES)
	$(LINK) $(LIB2) $(LFLAGS) /OUT:$(TARGET) /PDB:"$(PDB)" /MAP:"$(MAP)" \
	$(OBJ) $(RES)

.cc{$(OBJDIR)}.obj:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	$(CC) $(CPPFLAGS) /Fo"$(OBJDIR)\\" /c $<

.cc.lib:
	$(CC) $(CPPFLAGS) /LD $(LIB1) $<

clean:
	rm $(OBJ) $(TARGET) *.map *.pdb *.ilk *.obj *.lib *.dll *.exp
