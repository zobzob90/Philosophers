# 🛠 Variables
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/parsing.c \
		$(SRC_DIR)/pars_utils.c \
		$(SRC_DIR)/routine.c \
		$(SRC_DIR)/time.c \
		$(SRC_DIR)/monitoring.c \
		$(SRC_DIR)/color.c \
		$(SRC_DIR)/utils.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# 🏗️ Compilation principale avec barre de chargement
all: $(NAME)

$(NAME): $(OBJ)
	@clear
	@echo "🔨 Compilation en cours..."
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -I $(INC_DIR)
	@echo "✅ Compilation terminée !"
	@echo "⏳ Chargement..."
	@$(MAKE) --no-print-directory loading
	@echo "🟢 Démarrage dans :"
	@sleep 1
	@echo "\t3️⃣"
	@sleep 1
	@echo "\t2️⃣"
	@sleep 1
	@echo "\t1️⃣"
	@sleep 1
	@echo "🍝 Les philosophes sont à table !"

# 🏗️ Barre de chargement animée
loading:
	@echo -n "\t["
	@for i in $$(seq 1 20); do \
		echo -n "█"; \
		sleep 0.1; \
	done
	@echo "] ✅\n"

# 🏗️ Compilation des fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@
	@echo "🔄 Compilation de $< ... ✔️"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# 🧹 Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJ_DIR)
	@echo "🗑️  Suppression des fichiers objets."

# 🗑️ Nettoyage complet
fclean: clean
	@rm -f $(NAME)
	@echo "🗑️  Suppression complète des fichiers compilés."

# 🔄 Recompilation complète
re: fclean all

# 📄 Dépendances
.PHONY: all clean fclean re loading