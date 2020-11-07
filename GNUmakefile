TESTBIN:=\
	001-loadfile.test \
	002-loadconfig.test \
	003-loadconfig-errors.test \
	004-passml.test \
	005-number-appender.test

CPP:=g++

CFLAGS:=\
	-Wall

BOLD:=\033[1m
NORM:=\033[0m
GREN:=\033[32m

ifdef VERBOSE
	HUSH:=
else
	HUSH:=@
endif

all::$(TESTBIN)

.PRECIOUS: %.o

# CREAR EL OBJETO SI EXISTE EL CPP
%.o: %.cpp
	@echo "$(BOLD)$(GREN) ♼ $(NORM) $(BOLD)COMP $@ $(NORM)from $^"
	$(HUSH)$(CPP) -c $^

# CREAR EL TEST SI ESTÁN TODOS LOS OBJETOS
%.test: %.o passgen.o tinyxml2.o appenders.o
	@echo "$(BOLD)$(GREN) ♼ $(NORM) $(BOLD)GENR $@ $(NORM)from $^"
	$(HUSH)$(CPP) -o $@ $^
