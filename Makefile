NAME = ft_ls

SRC_DIR = srcs/ls/functions
SRC_SUBDIRS := $(shell find $(SRC_DIR) -type d)
OBJ_DIR = .obj

SRCS := $(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.c))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

LIBS_TARGET = srcs/libft/libft.a
INCLUDES = srcs/libft/include

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -gdwarf-2 -ldirent -lpwd -lxattr
CPPFLAGS = -MMD -MP $(addprefix -I,$(INCLUDES))

LDFLAGS = -L$(dir $(LIBS_TARGET))

DIRDUP = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	@printf "\033[0;32mCompilation successful.\033[0m\n"
	@$(CC) $(LDFLAGS) $(OBJS) -lreadline -lft -o $(NAME)

$(LIBS_TARGET):
	@$(MAKE) -C $(dir $@)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(DIRDUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEPS)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C srcs/libft
	@printf "\033[0;32mCleanup successful.\033[0m\n"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C srcs/libft
	@printf "\033[0;32mFull cleanup successful.\033[0m\n"

re: fclean all

.PHONY: all clean fclean re