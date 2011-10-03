#include "gtkwindow.h"

Gtk_Window::Gtk_Window()
  : search_entry_()
{
  set_title( "pathspell" );
  set_border_width(5);
  set_default_size(640, 480);

  add(hbox_);

  hbox_.pack_start( vbox_ );
  // TODO include a spell display

  vbox_.pack_start( search_entry_ );
  vbox_.pack_start( tree_view_ );

  search_entry_.signal_changed().connect( sigc::mem_fun( *this,
	                &Gtk_Window::on_search_entry_change) );

  ref_tree_model_ = Gtk::ListStore::create( columns_ );
  tree_view_.set_model( ref_tree_model_ );

  show_all_children();
}

Gtk_Window::Gtk_Window( std::vector < std::string > spell_list )
  : search_entry_()
{
  set_title( "pathspell" );
  set_border_width(5);
  set_default_size(640, 480);

  add(hbox_);

  hbox_.pack_start( vbox_ );
  // TODO include a spell display

  vbox_.pack_start( search_entry_ );
  vbox_.pack_start( tree_view_ );

  search_entry_.signal_changed().connect( sigc::mem_fun( *this,
	                &Gtk_Window::on_search_entry_change) );

  ref_tree_model_ = Gtk::ListStore::create( columns_ );
  tree_view_.set_model( ref_tree_model_ );

  import_spells( spell_list );

  show_all_children();
}

Gtk_Window::~Gtk_Window()
{
}

void Gtk_Window::import_spells( std::vector < std::string > spell_list )
{
  std::vector < std::string >::const_iterator it = spell_list.begin();
  for ( ; it != spell_list.end() ; it++ )
    {
      Gtk::TreeModel::Row row = *( ref_tree_model_->append() );
      row[columns_.col_name_] = *it;
    }

  tree_view_.append_column( "Spell", columns_.col_name_ );
}

void Gtk_Window::search( std::string )
{
}
