TESTBIN:=\
	001-loadfile.test \
	002-loadconfig.test \
	003-loadconfig-errors.test

CPP:=g++

CFLAGS:=\
	-Wall

all:$(TESTBIN)

# CREAR EL OBJETO SI EXISTE EL CPP
%.o: %.cpp
	@echo COMP $@ from $<
	@$(CPP) -c $?

# CREAR EL TEST SI ESTÁN TODOS LOS OBJETOS
%.test: %.o passgen.o
	@echo GENT $@ from $?
	@$(CPP) -o $@ $?
