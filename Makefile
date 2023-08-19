
NAME		:= philo

#=================== DIRECTORIES ===================#
OBJ_DIR		:=	./obj
SRC_DIR		:=	./src
INC_DIR		:=  ./include
LIBFT_DIR	:=	./libs/libft_ext

#=================== LIBRARIES ===================#

CFLAGS		:=	-Wextra -Wall -Werror

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

LIBFT	:=	$(LIBFT_DIR)/libft.a

#===============================================#
#=================== RECIPES ===================#
#===============================================#

# echo:
# 	@echo

.PHONY: all
all: $(ODIR) $(NAME)

.PHONY: clean
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR) clean

.PHONY: fclean
fclean:
	@$(MAKE) clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

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

$(NAME): $(OBJS) $(MAIN_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $(NAME)

$(LIBFT):
	@git submodule update --init --recursive
	@$(MAKE) -C $(LIBFT_DIR)

$(ODIR):
	mkdir -p $@
