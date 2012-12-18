BUILDDIR      = build
SRCDIR        = src

# regex in gcc is broken (at least till 4.7.1)
CXX           = clang++
CXXFLAGS      = -std=c++11 -stdlib=libc++ -Wall -Wextra
LDFLAGS       = -stdlib=libc++
df            = $(BUILDDIR)/$(*F)
MAKEDEPEND    = $(CXX) -MM $(CXXFLAGS) -o $(df).d $<

SRCS          = $(shell egrep -L '^(int )?main' $(SRCDIR)/*.cpp | sort)
OBJS          = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o, $(SRCS))

TARGETSRCS    = $(shell egrep -l '^(int )?main' $(SRCDIR)/*.cpp | sort)
TARGETS       = $(patsubst $(SRCDIR)/%.cpp, %, $(TARGETSRCS))
BUILD_TARGETS = $(patsubst %, $(BUILDDIR)/%, $(TARGETS))

.DEFAULT_GOAL: all
all: spells

$(TARGETS): %: $(OBJS) $(BUILDDIR)/%.o
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(BUILDDIR)/.ghost
	@$(MAKEDEPEND) && \
	  cp $(df).d $(df).P && \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	    -e '/^$$/ d' -e 's/$$/ :/' < $(df).d >> $(df).P && \
	  rm -f $(df).d
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

$(BUILDDIR)/.ghost:
	mkdir -p $(BUILDDIR)
	touch $(BUILDDIR)/.ghost

#$(BUILD_TARGETS): % : %.o $(OBJS)


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
