################################################################################
# BASIC VARIABLES															   #
################################################################################

export DEBUG		:= -g -O0

################################################################################
# LIBRARY VARIABLES															   #
################################################################################

export DIR_LIBFT	:= libft
export DIR_LIB		:= $(DIR_LIBFT)
export APP			:= lem_ipc

################################################################################
# RULES																		   #
################################################################################

.PHONY: all $(APP) $(DIR_LIB)

all:  $(APP)

$(DIR_LIB):
	@echo
	@echo \	MAKE $(RULE) in directory : $@
	@$(MAKE) --directory=$@  $(RULE)

$(APP): $(DIR_LIB)
	@echo
	@echo \	MAKE $(RULE) in directory : $@
	@$(MAKE) --directory=$@  $(RULE)

clean:
	@make RULE=clean

fclean:
	@make RULE=fclean

re:
	@make RULE=re

test:
	@make RULE=test
