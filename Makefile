
NAME		:= philo

#=================== DIRECTORIES ===================#
OBJ_DIR		:=	./obj
SRC_DIR		:=	./src
INC_DIR		:=  ./include

#=================== LIBRARIES ===================#

CFLAGS		:=	-Wextra -Wall -Werror -pthread -lc

ifdef OPTIM
	CFLAG += -Ofast -flto -march=native
endif

ifdef DEBUG
	CFLAGS += -g -Og
endif

ifdef FSAN
	CFLAGS += -fsanitize=address,undefined
endif

#=================== GENERAL VARIABLES ===================#

INCLUDE	:=	$(addprefix -I,$(INC_DIR))

MAIN	:=	src/main.c

SRC		:=	


ODIR	:=	$(sort $(dir $(SRC:%=$(OBJ_DIR)/%)))
SRC     :=	$(SRC:%=$(SRC_DIR)/%)

MAIN_OBJ:=	$(MAIN:src/%.c=$(OBJ_DIR)/%.o)
OBJS	:=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)


#===============================================#
#=================== RECIPES ===================#
#===============================================#

# echo:
# 	@echo

.PHONY: all
all: $(ODIR) $(NAME)

.PHONY: optim
optim:
	@$(MAKE) OPTIM=1

.PHONY: reoptim
reoptim:
	$(MAKE) fclean
	$(MAKE) optim

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR)

.PHONY: fclean
fclean:
	@$(MAKE) clean
	@rm -rf $(NAME)

.PHONY: re
re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: debug
debug:
	@$(MAKE) DEBUG=1

.PHONY: rebug
rebug:
	@$(MAKE) fclean
	@$(MAKE) debug

.PHONY: fsan
fsan:
	@$(MAKE) DEBUG=1 FSAN=1

.PHONY: resan
resan:
	@$(MAKE) fclean
	@$(MAKE) fsan

$(MAIN_OBJ): $(MAIN)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

$(ODIR):
	mkdir -p $@
