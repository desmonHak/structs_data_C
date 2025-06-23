include config.mk

generate_lib: libdebug.a $(TARGET).a
	ar -t $(TARGET).a

generate_lib_debug: libdebug.a $(TARGET)_debug.a
	ar -t $(TARGET).a

all: generate_lib
	$(MAKE) -C . -f $(MAKE_NAME) examples

TESTS = code_array-list code_hash-table code_matriz-list code_vector-list \
		code_array-list_vector-list code_ast code_hash-table-dynamic

# Regla principal que genera todos los tests
examples: $(addprefix $(PATH_EXAMPLES)/, $(addsuffix .$(EXTENSION), $(TESTS)))
	@echo "generando tests... $^"

# Regla patrón: compila cada test a partir de su fuente .c
$(PATH_EXAMPLES)/%.$(EXTENSION): $(PATH_EXAMPLES)/%.c
	$(CC) $< $(CFLAGS_EXAMPLES) -o $@ 


libdebug.a:
	echo "generando librerias estatica... $@"
	$(MAKE) -C ./$(PATH_DEBUG) -f $(MAKE_NAME)


$(TARGET).a: $(OBJECTS)
	$(ARR) $(ARR_FLAGS) $@ $^
	ranlib $@

$(TARGET)_debug.a: $(OBJECTS_DEBUG)
	$(ARR) $(ARR_FLAGS) $(TARGET).a $^
	ranlib $(TARGET).a

hash-table.o: $(PATH_SRC)/hash-table.c
	$(CC) $(CFLAGS) -c $^ -o $@

hash-table-dynamic.o: $(PATH_SRC)/hash-table-dynamic.c
	$(CC) $(CFLAGS) -c $^ -o $@

array-list.o: $(PATH_SRC)/array-list.c
	$(CC) $(CFLAGS) -c $^ -o $@

matriz-list.o: $(PATH_SRC)/matriz-list.c
	$(CC) $(CFLAGS) -c $^ -o $@

vector-list.o: $(PATH_SRC)/vector-list.c
	$(CC) $(CFLAGS) -c $^ -o $@

ast.o: $(PATH_SRC)/ast.c
	$(CC) $(CFLAGS) -c $^ -o $@

hash-table_debug.o: $(PATH_SRC)/hash-table.c
	$(CC) $(CFLAGS_DEBUG) -c $^ -o $@

hash-table-dynamic_debug.o: $(PATH_SRC)/hash-table-dynamic_debug.c
	$(CC) $(CFLAGS) -c $^ -o $@

array-list_debug.o: $(PATH_SRC)/array-list.c
	$(CC) $(CFLAGS_DEBUG) -c $^ -o $@

matriz-list_debug.o: $(PATH_SRC)/matriz-list.c
	$(CC) $(CFLAGS_DEBUG) -c $^ -o $@

vector-list_debug.o: $(PATH_SRC)/vector-list.c
	$(CC) $(CFLAGS_DEBUG) -c $^ -o $@

ast_debug.o: $(PATH_SRC)/ast.c
	$(CC) $(CFLAGS_DEBUG) -c $^ -o $@

cleanobj:
	$(RM) $(RMFLAGS) $(OBJECTS) $(OBJECTS_DEBUG)
	$(MAKE) -C ./$(PATH_DEBUG) -f $(MAKE_NAME) cleanobj

cleanall: cleanobj
	$(RM) $(RMFLAGS) *.o $(TARGET).a \
	$(TARGET_DEBUG).a
	$(MAKE) -C ./$(PATH_DEBUG) -f $(MAKE_NAME) cleanall

.SILENT: clean cleanobj cleanall
.IGNORE: cleanobj cleanall
.PHONY:  cleanobj cleanall