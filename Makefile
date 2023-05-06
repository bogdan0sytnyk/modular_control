CC = clang
C_OPTS = $(MAC_OPTS) -std=gnu11 -g -Wall -Wextra -Wformat-security -Wfloat-equal -Wshadow -Wconversion -Wlogical-not-parentheses -Wnull-dereference -Wno-unused-variable -Werror=vla $(LAB_OPTS)
LAB_OPTS = -I./src src/lib.c -lm
clean:
	rm -rf dist
prep:
	mkdir dist
compile: main.bin
compile: test.bin
test.bin: test/test.c
	$(CC) $(C_OPTS) $< -fprofile-instr-generate -fcoverage-mapping -o ./dist/$@ -lcheck -lrt -lpthread -lsubunit
test: clean prep compile
	LLVM_PROFILE_FILE="dist/test.profraw" ./dist/test.bin
	llvm-profdata merge -sparse dist/test.profraw -o dist/test.profdata
	llvm-cov report dist/test.bin -instr-profile=dist/test.profdata src/*.c
	llvm-cov show dist/test.bin -instr-profile=dist/test.profdata src/*.c --format html > dist/coverage.html
main.bin: src/main.c
	$(CC) $(C_OPTS) $< -o ./dist/$@
run: clean prep compile
	./dist/main.bin
check:
	clang-format --verbose -dry-run --Werror src/*
	clang-tidy src/*.c  -checks=-readability-uppercase-literal-suffix,-readability-non-const-parameter,-readability-magic-numbers,-clang-analyzer-deadcode.DeadStores,-clang-analyzer-security.insecureAPI.rand
	rm -rf src/*.dump
doxygen:
	doxygen
