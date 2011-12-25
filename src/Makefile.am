bin_PROGRAMS = pathspell
pathspell_SOURCES = pathspell.cpp \
gtkwindow.h gtkwindow.cpp
pathspell_CXXFLAGS = -Wall -Wextra -Werror -ggdb -std=gnu++0x
pathspell_CPPFLAGS = -I$(top_srcdir)/include $(GTKMM_CFLAGS) 
pathspell_LDADD = ../librpg/librpg.la $(GTKMM_LIBS)
