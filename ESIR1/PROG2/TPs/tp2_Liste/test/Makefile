# root of Google Test
GTEST_DIR = ./../../google_test

# Flags passed to the preprocessor.
CPPFLAGS += -I$(GTEST_DIR)/include

# Flags passed to the C++ compiler.
CXXFLAGS += -ggdb -Wall -Wextra -std=c++20

# Optionally define VALGRIND flag only when requested.
ifdef USE_VALGRIND
  CXXFLAGS += -DVALGRIND
endif

# libs to link statically
LIBS  =  $(GTEST_DIR)/lib/libgtest.a

sources = $(wildcard test_p*.cc)
progs   = $(patsubst %.cc,%,$(sources))

.PHONY: all delete test clean raz

all : $(progs)

%.o : %.cc %.hh Liste.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $*.o

%.o : %.cpp %.hpp Liste.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $*.o

# test de la partie 1 sans valgrind avec vérifications assertions
test_p1 : main_test.o common_p1.o test_p1.o
	$(CXX) $(LDFLAGS) $^ $(LIBS) -lpthread -o $@

test_p2 : main_test.o common_p1.o test_p2.o
	$(CXX) $(LDFLAGS) $^ $(LIBS) -lpthread -o $@

test_p24 : main_test.o common_p1.o test_p24.o
	$(CXX) $(LDFLAGS) $^ $(LIBS) -lpthread -o $@

test_p3 : main_test.o common_p1.o test_p3.o
	$(CXX) $(LDFLAGS) $^ $(LIBS) -lpthread -o $@

test_p32 : main_test.o common_p1.o test_p32.o
	$(CXX) $(LDFLAGS) $^ $(LIBS) -lpthread -o $@

test_p4 : main_test.o common_p1.o test_p4.o
	$(CXX) $(LDFLAGS) $^ $(LIBS) -lpthread -o $@

# test de la partie 1 avec valgrind pour vérifier les fuites mémoire
# (ne fonctionne pas avec les assertions)
test_p1_valgrind : main_test.o common_p1.o test_p1_valgrind.o
	$(CXX) $(LDFLAGS) $^ $(LIBS) -lpthread -o $@

test_p1_valgrind.o : test_p1.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $*.o

# 'delete' target: remove all object files and executables.
delete:
	@echo "Deleting all object files and executables..."
	-rm -f *.o *~ $(progs) test_p1_valgrind

# 'test' target: compile and then run all tests.
test: all
	@echo "Running tests..."
	@for prog in $(progs) test_p1_valgrind; do \
	  if [ -x $$prog ]; then \
	    echo "Running $$prog:"; \
	    ./$$prog; \
	    echo ""; \
	  else \
	    echo "$$prog is not executable or not present, skipping."; \
	  fi; \
	done

raz clean:
	-rm -f *.o *~ test_p1 test_p1_valgrind
