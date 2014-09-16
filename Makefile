# Build and run codejam problems

PROGS =2014/qual-a
PROGS+=2014/qual-b
PROGS+=2014/qual-c
PROGS+=2014/qual-d

CXX=g++
CXXFLAGS=-Wall -Werror -std=c++11 -g -O0

.PRONY: all clean check

all: $(PROGS)

$(PROGS): % : %.cpp
	@echo ">> BUILD: $@"; \
	$(CXX) $(CXXFLAGS) $< -o $@; \
	if [ $$? != 0 ]; then \
		echo "\033[0;31mFailure\033[0m"; \
	else \
		echo "\033[0;32mSuccess\033[0m"; \
	fi; \

check: $(PROGS)
	@for PROG in $(PROGS); do \
		echo ">> TEST: $${PROG}"; \
		$${PROG} < $${PROG}-input-small.txt; \
		if [ $$? != 0 ]; then \
			echo "\033[0;31mFailure\033[0m"; \
		else \
			echo "\033[0;32mSuccess\033[0m"; \
		fi; \
	done

clean:
	@rm $(PROGS) >/dev/null 2>&1 || echo "\033[0;32mCleaned\033[0m"
