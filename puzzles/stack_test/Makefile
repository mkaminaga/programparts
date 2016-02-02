# Makefile_header
# http://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html#Automatic-Prerequisites

PROGRAM = main
SRC = main.c ../lib/stack.c
OBJS = $(patsubst %.c,%.o,$(notdir ${SRC}))
DEPENDS = $(patsubst %.c,%.d,$(notdir ${SRC}))

CC = gcc
CFLAGS = "-Wall"

${PROGRAM}: ${OBJS}
	${CC} -o $@ ${OBJS}

.c.o:
	${CC} ${CFLAGS} -c $<

.PHONY: clean depend
clean:
	-${RM} ${PROGRAM} ${OBJS} ${DEPENDS}

%.d: %.c
	@set -e; $(CC) -M ${CPPFLAGS} $< \
		| sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' > $@; \
		[ -s $@ ] || rm -f $@
-include $(DEPENDS)
