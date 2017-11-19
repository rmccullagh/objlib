default: all

.DEFAULT:
	cd src && $(MAKE) $@

test:
	cd src/test && $(MAKE)
