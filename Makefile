DIRS = $(wildcard [0-9][0-9]-*)

all:
	@for d in $(DIRS); do $(MAKE) -s -C $$d || exit 1; done

clean:
	@for d in $(DIRS); do $(MAKE) -s -C $$d clean; done

.PHONY: all clean
