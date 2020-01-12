include ../Common.mk

TARGET = CPLD_ProgrammerApp
MODULE = module

EXE_DEFS = -DUSE_ICON

$(TARGET):
	@echo ''
	@echo  Building $@
	@echo "================================================================"
	$(MAKE) exe -f Target.mk TARGET=$@ BUILDDIR=$@$(BUILDDIR_SUFFIX) MODULE=$(MODULE) CDEFS='$(EXE_DEFS)'

all: $(TARGET)

clean: 
	${RMDIR} $(TARGET)$(BUILDDIR_SUFFIX)

.PHONY: all clean 
.PHONY: $(TARGET)