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

class Gtk_Window : public Gtk::Window
{
public:
  Gtk_Window();
  Gtk_Window( std::vector < std::string > );
  virtual ~Gtk_Window();

  void import_spells( std::vector < std::string > );

private:
  void search( std::string );
  void on_search_entry_change() { search( search_entry_.get_text() ); };

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

  Gtk::TreeView tree_view_;
  Glib::RefPtr < Gtk::ListStore > ref_tree_model_;
};

#endif // PATHSPELL_GTKWINDOW_H
