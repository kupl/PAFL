SUFFIX = .cpp
COMPILER = g++
CXXFLAGS = -std=c++20 -O2

SRCDIR = .
INCLUDE = .
EXEDIR = .

SOURCES = $(wildcard $(SRCDIR)/*$(SUFFIX))
OBJECTS = $(notdir $(SOURCES:$(SUFFIX)=.o))
TARGETS = $(notdir $(basename $(SOURCES)))

define MAKEALL
$(1): $(1).o
	$(COMPILER) -I$(INCLUDE) $(CXXFLAGS) -o $(EXEDIR)/$(1) $(1).o
	@$(RM) $(1).o
$(1).o:
	$(COMPILER) -I$(INCLUDE) $(CXXFLAGS) -c $(SRCDIR)/$(1)$(SUFFIX)
endef

.PHONY: all
all: $(TARGETS)
$(foreach VAR,$(TARGETS),$(eval $(call MAKEALL,$(VAR))))
