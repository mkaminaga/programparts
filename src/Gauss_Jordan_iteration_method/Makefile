# Makefile_header
# http://www.gnu.org/software/make/manual/html_node/Automatic-Prerequisites.html#Automatic-Prerequisites

PROGRAM = main
SRC = main.c ../../lib/gauss_jordan_iteration_method.c
OBJS = $(patsubst %.c,%.o,${SRC})
DEPENDS = $(patsubst %.c,%.d,${SRC})

CC = gcc
CFLAGS = -Wall -I../../lib
LDFLAGS = -L../../lib

${PROGRAM}: ${OBJS}
	${CC} -o $@ $(notdir ${OBJS})

.c.o:
	${CC} ${CFLAGS} ${LDFLAGS} -c $<

.PHONY: clean depend
clean:
	-${RM} ${PROGRAM} $(notdir ${OBJS}) $(notdir ${DEPENDS})

%.d: %.c
	@set -e; ${CC} -M ${CPPFLAGS} $< \
		| echo generating $(notdir $*).d

-include $(DEPENDS)
