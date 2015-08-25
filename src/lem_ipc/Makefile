################################################################################
# BASIC VARIABLES															   #
################################################################################

SRCS				:= main.c get_shmem.c exit_shmem.c semaph.c player.c \
						play_turn.c map.c get_semaph.c get_player.c msg.c \
						designate_target.c

PATH_OBJ			:= obj
PATH_OBJT			:= objt
PATH_SRC			:= src
PATH_INC			:= inc
PATH_TEST			:= test

CFLAGS				:= -Wall -Wextra -Werror
OBJECTS				:= $(patsubst %.c, $(PATH_OBJ)/%.o, $(SRCS))
OBJECTS_TEST		:= $(patsubst %.c, $(PATH_OBJT)/%, $(SRCS_TEST))

TEST_CMD			:= $(patsubst %.c, $(PATH_OBJT)/%;, $(SRCS_TEST))

################################################################################
# LIBRARY VARIABLES															   #
################################################################################

export DIR_LIBFT	:= ../libft

LIB_FT				:= -L$(DIR_LIBFT) -lft

export DIR_LIB 		:= $(DIR_LIBFT)
LIBRARY				:= $(LIB_FT)
INCLUDES			:= -I$(DIR_GLFW)/inc -I ~/.brew/include \
						-I./$(PATH_INC) $(patsubst %,-I%/inc,$(DIR_LIB))

################################################################################
# BASIC RULES																   #
################################################################################

.PHONY: all test

all: $(APP)

$(APP): $(OBJECTS)
	cc -o $@ $(OBJECTS) $(LIBRARY) $(DEBUG)

test: $(OBJECTS)
	@echo plopasdi
	@rm -rf $(PATH_OBJT)
	@$(MAKE)
	@$(MAKE) $(OBJECTS_TEST)
	@$(TEST_CMD)

$(PATH_OBJT)/%: $(addprefix $(PATH_TEST)/,%.c)
	@mkdir -p $(PATH_OBJT)
	$(CC) -o $@ $^ $(filter-out ,$(VAR)) $(DEBUG) $(LIBRARY) $(INCLUDES) -L. -lmath

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/,%.c)
	@mkdir -p $(PATH_OBJ)
	cc -c -o $@ $(CFLAGS) $^ $(DEBUG) $(INCLUDES)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(APP)

re: fclean $(APP)
