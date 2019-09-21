#
# Makefile
# Date 2019-09-21 18:22:39
# Copyright 2019 Mamoru Kaminaga
#
TARGET = ScreenCaptureTool.exe
PDB = ScreenCaptureTool.pdb
MAP = ScreenCaptureTool.map
RES = resource.res
SRC = main.cc folder_dialog.cc key_hook.cc
OBJ = $(OBJDIR)\main.obj $(OBJDIR)\folder_dialog.obj
DLL = key_hook.dll
MYLIB = key_hook.lib
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

$(TARGET): $(OBJ) $(MYLIB) $(DLL) $(RES)
	$(LINK) $(MYLIB) $(LFLAGS) /OUT:$(TARGET) /PDB:"$(PDB)" /MAP:"$(MAP)" \
	$(OBJ) $(RES)

.cc{$(OBJDIR)}.obj:
	@[ -d $(OBJDIR) ] || mkdir $(OBJDIR)
	$(CC) $(CPPFLAGS) /Fo"$(OBJDIR)\\" /c $<

.cc.lib:
	$(CC) $(CPPFLAGS) /LD $(LIB1) $<

clean:
	rm $(OBJ) $(TARGET) *.map *.pdb *.ilk *.obj *.lib *.dll *.exp
