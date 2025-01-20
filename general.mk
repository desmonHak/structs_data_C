include config.mk

generate_lib: libdebug.a $(TARGET).a
	ar -t $(TARGET).a

generate_lib_debug: libdebug.a $(TARGET)_debug.a
	ar -t $(TARGET).a

all: generate_lib
	$(MAKE) -C . -f $(MAKE_NAME) examples

examples: generate_lib
	$(CC) examples/code_array-list.c    		 $(CFLAGS_EXAMPLES)   -o examples/code_array-list.$(EXTENSION)
	$(CC) examples/code_hash-table.c    		 $(CFLAGS_EXAMPLES)   -o examples/code_hash-table.$(EXTENSION)
	$(CC) examples/code_matriz-list.c   		 $(CFLAGS_EXAMPLES)   -o examples/code_matriz-list.$(EXTENSION)
	$(CC) examples/code_vector-list.c   		 $(CFLAGS_EXAMPLES)   -o examples/code_vector-list.$(EXTENSION)
	$(CC) examples/code-array-list_vector-list.c $(CFLAGS_EXAMPLES)	-o examples/code-array-list_vector-list.$(EXTENSION)

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

array-list.o: $(PATH_SRC)/array-list.c
	$(CC) $(CFLAGS) -c $^ -o $@

matriz-list.o: $(PATH_SRC)/matriz-list.c
	$(CC) $(CFLAGS) -c $^ -o $@

vector-list.o: $(PATH_SRC)/vector-list.c
	$(CC) $(CFLAGS) -c $^ -o $@

hash-table_debug.o: $(PATH_SRC)/hash-table.c
	$(CC) $(CFLAGS_DEBUG) -c $^ -o $@

array-list_debug.o: $(PATH_SRC)/array-list.c
	$(CC) $(CFLAGS_DEBUG) -c $^ -o $@

matriz-list_debug.o: $(PATH_SRC)/matriz-list.c
	$(CC) $(CFLAGS_DEBUG) -c $^ -o $@

vector-list_debug.o: $(PATH_SRC)/vector-list.c
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