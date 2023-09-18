GREEN = \033[0;92;1m
YELLOW = \033[0;33;1m
PINK = \033[0;95;1m
BLUE = \033[0;94;1m
DEF_COLOR = \033[0;37m

NAME        = pipex
NAME_BONUS  = pipex_bonus
LIBFT_DIR   = ./inc/libft/
LIBFT_NAME  = $(LIBFT_DIR)libft.a
GNL_DIR		= ./inc/gnl/
GNL_NAME	= $(GNL_DIR)gnl.a

SRC_MAIN_DIR = ./src/
SRC_MAIN     = main.c    errors.c  children.c  freeing.c
OBJ_MAIN     = $(addprefix $(SRC_MAIN_DIR), $(SRC_MAIN:%.c=%.o))

SRC_BONUS_DIR = ./bonus/
SRC_BONUS     = main.c    errors.c  children.c  freeing.c\
                files.c    here_doc.c
OBJ_BONUS    = $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS:%.c=%.o))

HDR_DIR      = ./inc/
HDR_MAIN     = pipex.h    pipex_bonus.h
HDR          = $(addprefix $(HDR_DIR), $(HDR_MAIN))

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror
NOPR    = --no-print-directory -sC

all: $(LIBFT_NAME) $(GNL_NAME) $(NAME)

bonus: $(LIBFT_NAME) $(GNL_NAME) $(NAME_BONUS)

$(LIBFT_NAME):
	@make $(NOPR) $(LIBFT_DIR)

$(GNL_NAME):
	@make $(NOPR) $(GNL_DIR)

$(NAME): $(OBJ_MAIN) $(LIBFT_NAME) $(GNL_NAME) $(HDR)
	@$(RM) $(OBJ_BONUS)
	@$(CC) $(OBJ_MAIN) $(LIBFT_NAME) $(GNL_NAME) -o $(NAME)
	@echo "$(DEF_COLOR)   	  ( \   / ) \n \
		$(DEF_COLOR)  ( ･ ⌵ ･ )    💬 $(PINK)" pipex compiled successfully ☆" \n \
		$(DEF_COLOR) c( っ    っ\n $(DEF_COLOR)"

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT_NAME) $(GNL_NAME) $(HDR)
	@$(RM) $(OBJ_MAIN)
	@$(CC) $(OBJ_BONUS) $(LIBFT_NAME) $(GNL_NAME) -o $(NAME_BONUS)
	@touch $(NAME_BONUS)
		@echo "$(DEF_COLOR)   	  ( \   / ) \n \
		$(DEF_COLOR)  ( ･ ◡ ･ )    💬 $(BLUE)" pipex+ compiled successfully ☆" \n \
		$(DEF_COLOR) c( っ    っ\n $(DEF_COLOR)"


%.o: %.c $(HDR) Makefile
	@$(CC) $(CFLAGS) -I$(HDR_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -c $< -o $@

clean:
	@$(RM) $(OBJ_MAIN)
	@$(RM) $(OBJ_BONUS)
	@make clean $(NOPR) $(LIBFT_DIR)
	@make clean $(NOPR) $(GNL_DIR)
		@echo "$(DEF_COLOR)   	  ( \   / ) \n \
		$(DEF_COLOR)  ( ･ o ･ )    💬 $(YELLOW)"  object files removed ☆ " \n \
		$(DEF_COLOR) c( っ    っ\n $(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@make fclean $(NOPR) $(LIBFT_DIR)
	@make fclean $(NOPR) $(GNL_DIR)
	clear
		@echo "$(DEF_COLOR)   	  ( \   / ) \n \
		$(DEF_COLOR)  ( ･ □ ･ )    💬 $(GREEN)"  everything cleaned ☆ " \n \
		$(DEF_COLOR) c( っ    っ\n $(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re bonus