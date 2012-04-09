#ifndef PATHSPELL_GTKWINDOW_H
#define PATHSPELL_GTKWINDOW_H

#include <string>
#include <vector>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treemodelcolumn.h>
#include <gtkmm/treeview.h>
#include <gtkmm/window.h>

#include "spell.h"
#include "storage.h"
#include "xmlspell.h"

class Gtk_Window : public Gtk::Window
{
public:
  Gtk_Window(const RPG::Spell_Storage& storage);

private:
  void read_spells();
  void display_spell( const Glib::ustring& );
  void on_search_entry_change() { display_spell( search_entry_.get_text() ); };
  void on_tree_view_row_activated(const Gtk::TreeModel::Path& path,
                                  Gtk::TreeViewColumn*);

  class Columns : public Gtk::TreeModel::ColumnRecord
  {
  public:
    Columns() { add(col_name_); };

    Gtk::TreeModelColumn< Glib::ustring > col_name_;
  };

  Columns columns_;
  Gtk::VBox vbox_;
  Gtk::HBox hbox_;
  Gtk::Entry search_entry_;
  Gtk::Label spell_label_;
  Gtk::TreeView tree_view_;
  Glib::RefPtr < Gtk::ListStore > ref_tree_model_;

  const RPG::Spell_Storage& storage_;
};

#endif // PATHSPELL_GTKWINDOW_H
