.PHONY: all clean test

all:
	$(MAKE) -C src

clean:
	$(MAKE) -C src clean
	$(MAKE) -C tests clean || true

test: all
	$(MAKE) -C tests test
