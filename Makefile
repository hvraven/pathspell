BUILDDIR      = build
SRCDIR        = src

# regex in gcc is broken (at least till 4.7.1)
CXX           = clang++
CXXFLAGS      = -std=c++11 -stdlib=libc++ -Wall -Wextra -ggdb
LDFLAGS       = -stdlib=libc++ -lpugixml
MAKEDEPEND    = $(CXX) -MM $(CXXFLAGS) $<

SRCS          = $(shell egrep -L '^(int )?main' $(SRCDIR)/*.cpp | sort)
OBJS          = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o, $(SRCS))

TARGETSRCS    = $(shell egrep -l '^(int )?main' $(SRCDIR)/*.cpp | sort)
TEST_TARGETS  = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%, $(filter $(SRCDIR)/test%, $(TARGETSRCS)))
TARGETS       = $(patsubst $(SRCDIR)/%.cpp, %, $(filter-out $(SRCDIR)/test%, $(TARGETSRCS)))
BUILD_TARGETS = $(patsubst %, $(BUILDDIR)/%, $(TARGETS))

.DEFAULT_GOAL: all
all: $(TARGETS)

test: $(TEST_TARGETS)

$(TARGETS): %: $(OBJS) $(BUILDDIR)/%.o
	$(CXX) $(LDFLAGS) $^ -o $@

$(TEST_TARGETS): %: $(OBJS) %.o
	$(CXX) $(LDFLAGS) $^ -o $@
	$@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(BUILDDIR)/.ghost
	@$(MAKEDEPEND) | sed -e 's:^$(@F):$@:' > $(@:.o=.P)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

$(BUILDDIR)/.ghost:
	mkdir -p $(BUILDDIR)
	touch $(BUILDDIR)/.ghost

%.P: %.o

.PHONY: clean distclean
clean:
	-find $(BUILDDIR) -maxdepth 1 -iname '*.o' -delete or -iname '*.a' -delete \
	  -or -type f -executable -delete

distclean:
	rm -r $(BUILDDIR)
	rm -f $(TARGETS)

-include $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.P)
-include $(TARGETS:%=$(BUILDDIR)/%.P)
