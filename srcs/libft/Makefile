NAME		:= libft.a

CFLAGS		:= -Wall -Werror -Wextra -ggdb3 -gdwarf-2
CPPFLAGS	:= -MMD -MP -I ./include 

CC			:= clang

DIRDUP		= mkdir -p $(@D)

###############################################################################

SRC_DIR		:= functions

BUILD_DIR	:= .obj

SRCS 		:=	libft/ft_bzero.c		\
	libft/ft_isdigit.c					\
	libft/ft_isalnum.c					\
	libft/ft_isascii.c					\
	libft/ft_isprint.c					\
	libft/ft_isspace.c					\
	libft/ft_strlen.c					\
	libft/ft_memset.c					\
	libft/ft_isalpha.c					\
	libft/ft_memcpy.c					\
	libft/ft_memmove.c					\
	libft/ft_strlcpy.c					\
	libft/ft_strlcat.c					\
	libft/ft_toupper.c					\
	libft/ft_tolower.c					\
	libft/ft_strchr.c					\
	libft/ft_strrchr.c					\
	libft/ft_strncmp.c					\
	libft/ft_memchr.c					\
	libft/ft_memcmp.c					\
	libft/ft_strnstr.c					\
	libft/ft_atoi.c						\
	libft/ft_atoll.c					\
	libft/ft_calloc.c					\
	libft/ft_strdup.c					\
	libft/ft_substr.c					\
	libft/ft_strjoin.c					\
	libft/ft_strjoin_free.c 			\
	libft/ft_strjoin_fs2.c  			\
	libft/ft_strtrim.c					\
	libft/ft_split.c 					\
	libft/ft_itoa.c						\
	libft/ft_strmapi.c					\
	libft/ft_striteri.c					\
	libft/ft_lstmap.c					\
	libft/ft_putchar_fd.c				\
	libft/ft_putstr_fd.c				\
	libft/ft_putendl_fd.c				\
	libft/ft_putnbr_fd.c				\
	libft/ft_lstnew.c					\
	libft/ft_lstadd_front.c				\
	libft/ft_lstsize.c					\
	libft/ft_lstlast.c					\
	libft/ft_lstadd_back.c				\
	libft/ft_lstdelone.c				\
	libft/ft_lstclear.c					\
	libft/ft_lstiter.c					\
	libft/ft_lstmap.c					\
	libft/ft_listlen.c					\
	libft/ft_atoi_base.c				\
	libft/ft_strcspn.c					\
	libft/count_args_2d.c				\
	libft/cpy_array2d.c					\
	libft/free_array2d.c				\
	libft/print_array2d.c				\
	libft/find_in_array2d.c				\
	libft/find_in.c						\
	libft/cut.c							\
	libft/count_c.c						\
	libft/compare.c						\
	libft/search_c.c					\
	libft/ft_strcmp.c					\
	libft/ft_strcpy.c					\
	printf/ft_printf.c					\
	printf/ft_printf_utils.c			\
	printf/ft_nbrlen.c					\

SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

DEPS		:= $(OBJS:.o=.d)

# Colors
GREEN		:= \033[0;32m
BLUE		:= \033[1;34m
YELLOW		:= \033[0;33m
NC			:= \033[0m

###############################################################################

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@echo "$(GREEN)$(NAME) built successfully.$(NC)"

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c
	@$(DIRDUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	@echo "$(BLUE)Compiled $< successfully.$(NC)"

-include $(DEPS)

###############################################################################

clean:
	@rm -rf $(BUILD_DIR)
	@echo "$(YELLOW)Cleaned object files.$(NC)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(YELLOW)Cleaned $(NAME).$(NC)"

re: fclean all
	@echo "$(YELLOW)Rebuilt everything.$(NC)"

.PHONY: all clean fclean re

###############################################################################