# ----------------------------------------------------------------------
# Makefile - Phonebook (Rubrica Telefonica)
#
#   make         compila il progetto in build/ e copia le risorse
#                (cartella resources/) accanto all'eseguibile
#   make clean   elimina la cartella build/
#
# Il programma cerca le cartelle Interfacce/ e Rubrica/ nella STESSA
# cartella dell'eseguibile, per questo vengono copiate dentro build/.
# Da usare in una shell MinGW/MSYS2 (servono make, gcc, cp, mkdir, rm).
# ----------------------------------------------------------------------

CC      = gcc
CFLAGS  = -Wall -g

SRC_DIR = src
BUILD   = build
TARGET  = $(BUILD)/Rubrica_Telefonica.exe

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD)/%.o,$(SRCS))

.PHONY: all clean

all: $(TARGET) $(BUILD)/.risorse

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@

$(BUILD)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Copia Interfacce/ e Rubrica/ accanto all'eseguibile
$(BUILD)/.risorse: $(wildcard resources/*/*) | $(BUILD)
	cp -r resources/. $(BUILD)/
	touch $@

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

-include $(OBJS:.o=.d)
