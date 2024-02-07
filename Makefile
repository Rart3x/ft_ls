NAME = ft_ls

SRC_DIR = requirements/ls/functions
SRC_SUBDIRS := $(shell find $(SRC_DIR) -type d)
OBJ_DIR = .obj

SRCS := $(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.c))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

LIBS_TARGET = requirements/libft/libft.a
INCLUDES = requirements/libft/include

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
	@make clean -C requirements/libft
	@printf "\033[0;32mCleanup successful.\033[0m\n"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C requirements/libft
	@printf "\033[0;32mFull cleanup successful.\033[0m\n"

re: fclean all

.PHONY: all clean fclean re test

TEST_DIR = requirements/tests
TEST_OBJ_DIR = $(TEST_DIR)/.test_obj
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS := $(TEST_SRCS:$(TEST_DIR)/%.c=$(TEST_OBJ_DIR)/%.o)
TEST_EXE = test

TEST_CFLAGS := -Wall -Wextra -Werror $(CFLAGS) $(addprefix -I,$(INCLUDES))

test: $(TEST_EXE)

$(TEST_EXE): $(TEST_OBJS) $(LIBS_TARGET)
	@printf "\033[0;32mCompiling test executable.\033[0m\n"
	@$(CC) $(LDFLAGS) $(TEST_OBJS) -o $(TEST_EXE) $(LIBS_TARGET)

$(TEST_OBJ_DIR)/%.o : $(TEST_DIR)/%.c
	@$(DIRDUP)
	@$(CC) $(TEST_CFLAGS) -c -o $@ $<

.PHONY: test

cleantest:
	@rm -rf $(TEST_OBJ_DIR)
	@rm -f $(TEST_EXE)
	@printf "\033[0;32mTest cleanup successful.\033[0m\n"