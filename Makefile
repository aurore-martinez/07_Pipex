V = false

ifeq ($(V),true)
    ECHO =
else
    ECHO = @
endif

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = lib/libft.a
SRC = main/main.c utils/error_management.c src/pipex.c src/process.c utils/utils.c
OBJ = $(SRC:.c=.o)

# Séquences d'échappement ANSI pour les couleurs
GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

# Symboles Unicode
CHECK_MARK = ✔
UNCHECKED_MARK = ✘
COMP_SUCCESS = $(GREEN)$(CHECK_MARK)$(RESET)
COMP_FAILURE = $(RED)$(UNCHECKED_MARK)$(RESET)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compilation de $(NAME) en cours..."
	@$(ECHO)make -C lib --silent --no-print-directory     && { echo "Compilation de la Libft ($(COMP_SUCCESS))" ; }     || { echo "Erreur : Compilation de la Libft échouée ($(COMP_FAILURE))" ; exit 1; }
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)     && { echo "$(NAME) a été créé avec succès ($(COMP_SUCCESS))" ; }     || { echo "Erreur : Compilation de $(NAME) échouée ($(COMP_FAILURE))" ; exit 1; }
	@echo "Compilation réussie, Aurore ($(COMP_SUCCESS))"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(ECHO)make clean -C lib --silent --no-print-directory
	$(ECHO)rm -f $(OBJ)
	@echo "Nettoyage réussi, Aurore ($(COMP_SUCCESS))"

fclean: clean
	$(ECHO)rm -f $(NAME)
	$(ECHO)rm -f lib/libft.a
	@echo "Nettoyage complet réussi, Aurore ($(COMP_SUCCESS))"

re: fclean all

.PHONY: all clean fclean re
