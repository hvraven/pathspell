#include "gtkwindow.h"

Gtk_Window::Gtk_Window( Spell_List * const spells )
  : search_entry_(),
    spell_label_(),
    spells_(spells)
{
  set_title( "pathspell" );
  set_border_width(5);
  set_default_size(800, 600);

  add(hbox_);

  hbox_.set_spacing(5);
  spell_label_.set_line_wrap(true);
  spell_label_.set_alignment(0,0);

  hbox_.pack_start( vbox_, Gtk::PACK_SHRINK );
  hbox_.pack_start( spell_label_, Gtk::PACK_EXPAND_WIDGET );

  vbox_.set_spacing(5);
  tree_view_.set_vexpand( true );

  vbox_.pack_start( search_entry_, Gtk::PACK_SHRINK );
  vbox_.pack_start( tree_view_, Gtk::PACK_EXPAND_WIDGET );

  ref_tree_model_ = Gtk::ListStore::create( columns_ );
  tree_view_.set_model( ref_tree_model_ );

  import_spells( spells_->get_spell_list() );

  search_entry_.signal_changed().connect( sigc::mem_fun( *this,
	                &Gtk_Window::on_search_entry_change) );
  tree_view_.signal_row_activated().connect( sigc::mem_fun( *this,
		        &Gtk_Window::on_tree_view_row_activated) );

  show_all_children();
}

Gtk_Window::~Gtk_Window()
{
}

void Gtk_Window::on_tree_view_row_activated
    ( const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn* )
{
  Gtk::TreeModel::iterator it = ref_tree_model_->get_iter(path);

  if ( it )
    {
      Gtk::TreeModel::Row row = *it;
      display_spell( row[columns_.col_name_] );
    }
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

void Gtk_Window::display_spell( const Glib::ustring& spell_name )
{
  Spell spell = spells_->get_spell( spell_name );

  Glib::ustring result = "<span font_size=\"large\"><b>"
    + spell[NAME].print()
    + "</b>\n</span>";

  result += "<b>School:</b> "
    +spell[SCHOOL].print()
    + " ";

  result += "<b>Level:</b> "
    + spell[LEVEL].print();

  result += "\n<b>Casting:</b>\n";

  result += "<b>Casting Time</b>: "
    + spell[CASTING_TIME].print()
    + " ";

  result += "<b>Components:</b> "
    + spell[COMPONENTS].print();

  result += "\n<b>Effect:</b>\n";

  result += "<b>Range:</b> "
    + spell[RANGE].print()
    + " ";

  /*if ( spell.check_target() )
    {
      result += "<b>Target:</b> "
	+ spell[TARGET].print()
	+ "; ";
	}*/

  result += "<b>Duration:</b> "
    + spell[DURATION].print()
    + " ";

  result += "<b>Saving Throw:</b> "
    + spell[SAVING_THROW].print()
    + " ";

  result += "<b>Spell Resistance:</b> "
    + spell[SPELL_RESISTANCE].print();

  result += "\n<b>Description:</b>\n"
  + spell[DESCRIPTION].print();

  spell_label_.set_markup( result );
}
