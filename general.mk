include config.mk

all: generate_lib
	$(MAKE) -C . -f $(MAKE_NAME) examples

generate_lib: libdebug.a $(TARGET).a
	ar -t $(TARGET).a

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

hash-table.o: $(PATH_SRC)/hash-table.c
	$(CC) $(CFLAGS) -c $^ -o $@

array-list.o: $(PATH_SRC)/array-list.c
	$(CC) $(CFLAGS) -c $^ -o $@

matriz-list.o: $(PATH_SRC)/matriz-list.c
	$(CC) $(CFLAGS) -c $^ -o $@

vector-list.o: $(PATH_SRC)/vector-list.c
	$(CC) $(CFLAGS) -c $^ -o $@

cleanobj:
	$(RM) $(RMFLAGS) $(OBJECTS)
	$(MAKE) -C ./$(PATH_DEBUG) -f $(MAKE_NAME) cleanobj

cleanall: cleanobj
	$(RM) $(RMFLAGS) $(TARGET).o $(TARGET).a \
	$(TARGET_DEBUG).a
	$(MAKE) -C ./$(PATH_DEBUG) -f $(MAKE_NAME) cleanall

.SILENT: clean cleanobj cleanall
.IGNORE: cleanobj cleanall
.PHONY:  cleanobj cleanall