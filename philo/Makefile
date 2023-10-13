
NAME	:= philo

#=================== DIRECTORIES ===================#
OBJ_DIR	:=	./obj
SRC_DIR	:=	.
INC_DIR	:=  ./include

#=================== LIBRARIES ===================#

CFLAGS	:=	-Wextra -Wall -Werror -pthread

ifdef OPTIM
	CFLAGS += -Ofast -flto -march=native
endif

ifdef DEBUG
	CFLAGS += -g -Og
endif

ifdef FSAN
	CFLAGS += -fsanitize=thread
	# CFLAGS += -fsanitize=address,undefined
endif

#=================== GENERAL VARIABLES ===================#

INCLUDE	:=	$(addprefix -I,$(INC_DIR))

SRC		:=	main.c init.c utils.c free.c philo.c time.c error.c observer.c actions.c

ODIR	:=	$(sort $(dir $(SRC:%=$(OBJ_DIR)/%)))

MAIN_OBJ:=	$(MAIN:%.c=$(OBJ_DIR)/%.o)
OBJS	:=	$(SRC:%.c=$(OBJ_DIR)/%.o)

#===============================================#
#=================== RECIPES ===================#
#===============================================#

all: $(ODIR) $(NAME)

optim:
	$(MAKE) OPTIM=1

reoptim:
	$(MAKE) fclean
	$(MAKE) optim

clean:
	@rm -rf $(OBJ_DIR)

fclean:
	@$(MAKE) clean
	@rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

debug:
	@$(MAKE) DEBUG=1

rebug:
	@$(MAKE) fclean
	@$(MAKE) debug

fsan:
	@$(MAKE) DEBUG=1 FSAN=1

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

.PHONY: all, optim, reoptim, clean, fclean, re, debug, rebug, fsan, resan
