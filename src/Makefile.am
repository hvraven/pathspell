bin_PROGRAMS = pathspell
pathspell_SOURCES = pathspell.cpp \
xml.h xmlspelllist.cpp xmldecoder.cpp \
spell.h spell.cpp school.cpp level.cpp components.cpp savingthrow.cpp spellresistance.cpp target.cpp\
gtkwindow.h gtkwindow.cpp \
error.h \
strmanip.h strmanip.cpp
pathspell_CXXFLAGS = -Wall -Werror -Wextra
pathspell_CPPFLAGS = $(GTKMM_CFLAGS) 
#-I/usr/include/boost
pathspell_LDADD = $(GTKMM_LIBS)
