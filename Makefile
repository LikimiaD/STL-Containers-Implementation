EXTRA_BUILD_FLAGS=
CLANG_ARGS=--style=Google **/*.cpp **/*.h

.RECIPEPREFIX=>

all: test gcov_report

debug:
> xmake config -P . -m debug
> xmake build -P . s21_containers_test $(EXTRA_BUILD_FLAGS)

clean:
> xmake clean -P .
> rm -f *.a

lint:
> clang-format -n $(CLANG_ARGS)

format:
> clang-format -i $(CLANG_ARGS)

intellisense:
> xmake project -P . -k compile_commands

test:
> xmake config -P . -m release
> xmake build -P . -g test $(EXTRA_BUILD_FLAGS)
> xmake run -P . -g test

gcov_report:
> xmake config -P . -m coverage
> xmake build -P . -g test $(EXTRA_BUILD_FLAGS)
> xmake run -P . -g test
> DIR=$$(find build -mindepth 2 -type d -not -path '*/.*' -name 'coverage') && \
	genhtml -o $$DIR/report $$DIR/*.info && \
	xdg-open $$DIR/report/index.html

valgrind:
> xmake config -P . -m valgrind
> xmake build -P . -g test $(EXTRA_BUILD_FLAGS)
> xmake run -P . -g test

fclean: clean
> rm -rf build .xmake

.PHONY: clean lint format test intellisense gcov_report fclean

