bin_PROGRAMS = pathspell-gtk
pathspell_gtk_SOURCES = pathspell-gtk.cpp \
                        gtkwindow.h gtkwindow.cpp
pathspell_gtk_CXXFLAGS = -Wall -Wextra -ggdb -std=c++11
pathspell_gtk_CPPFLAGS = -I$(top_srcdir)/librpg/include $(GTKMM_CFLAGS) 
pathspell_gtk_LDADD = ../librpg/src/librpg.la $(GTKMM_LIBS)
