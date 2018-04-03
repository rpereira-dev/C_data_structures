NAME 		= libcstruct.a
TESTS_NAME	= test.out

SRCDIR	= src
INCDIR	= includes
BINDIR	= bin
OBJDIR	= obj
TESTDIR	= tests
DOCDIR	= doc

INCLUDES =	$(wildcard $(INCDIR)/*.h)
SOURCES	 =	$(wildcard $(SRCDIR)/*.c)
OBJECTS	=	$(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TARGET		= $(BINDIR)/$(NAME)

TESTS_SOURCES	= $(shell find $(TESTDIR) -name "*.c")
TESTS_OBJECTS	= $(TESTS_SOURCES:$(TESTDIR)/%.c=$(OBJDIR)/$(TESTDIR)/%.o)
TESTS_TARGET	= $(BINDIR)/$(TESTS_NAME)

INC	= -I $(INCDIR)
FLAGS	= -ansi -Wall -Wextra -Werror -g

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $(TARGET))
	ar rc $(TARGET) $(OBJ)
	ranlib $(TARGET)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@-mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INC) -c $< -o $@

$(TESTS_OBJECTS): $(OBJDIR)/$(TESTDIR)/%.o : $(TESTDIR)/%.c
	@-mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(INC) -c $< -o $@ 

doc:
	cd doc ; doxygen

tests: $(TESTS_TARGET)

$(TESTS_TARGET): $(OBJECTS) $(TESTS_OBJECTS)
	$(CC) $(FLAGS) $(filter-out obj/main.o, $(OBJECTS)) $(TESTS_OBJECTS) -o $(TESTS_TARGET) -lcunit

clean:
	rm -rf $(OBJECTS)
	rm -rf $(TESTS_OBJECTS)
	rm -rf $(TESTS_TARGET)

fclean: clean
	rm -rf $(TARGET)
	rm -rf $(OBJDIR)

re: fclean all

.PHONY: all test clean doc tests standart ncurses sdl
