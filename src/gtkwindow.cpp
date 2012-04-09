#include "gtkwindow.h"
#include <algorithm>

Gtk_Window::Gtk_Window(const RPG::Spell_Storage& storage)
  : search_entry_(),
    spell_label_(),
    storage_(storage)
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

  read_spells();

  search_entry_.signal_changed().connect( sigc::mem_fun( *this,
	                &Gtk_Window::on_search_entry_change) );
  tree_view_.signal_row_activated().connect( sigc::mem_fun( *this,
		        &Gtk_Window::on_tree_view_row_activated) );

  show_all_children();
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

void
Gtk_Window::read_spells()
{
  // elements are unsorted in storage_, thus we sort them first
  std::vector<std::string> sorter;
  sorter.reserve(storage_.size());
  for (const auto& e : storage_)
    sorter.push_back(e.first);
  std::sort(begin(sorter), end(sorter));

  for (const auto& e : sorter)
    {
      Gtk::TreeModel::Row row = *(ref_tree_model_->append());
      row[columns_.col_name_] = e;
    }

  tree_view_.append_column("Spell", columns_.col_name_);
}

void Gtk_Window::display_spell(const Glib::ustring& spell_name)
{
  const RPG::Pathfinder::Spell *const pspell
    (&(storage_.find(spell_name)->second));

  Glib::ustring result = "<span font_size=\"medium\"><b>"
    + pspell->name
    + "</b>\n</span>";

  result += "<b>School:</b> "
    + pspell->school.print()
    + " ";

  result += "<b>Level:</b> "
    + pspell->levels.print();

  result += "\n<b>Casting:</b>\n";

  result += "<b>Casting Time</b>: "
    + pspell->casting_time.print()
    + " ";

  result += "<b>Components:</b> "
    + pspell->components.print();

  result += "\n<b>Effect:</b>\n";

  result += "<b>Range:</b> "
    + pspell->range.print()
    + " ";

  /*if ( spell.check_target() )
    {
      result += "<b>Target:</b> "
	+ spell[TARGET].print()
	+ "; ";
	}*/

  result += "<b>Duration:</b> "
    + pspell->duration.print()
    + " ";

  result += "<b>Saving Throw:</b> "
    + pspell->saving_throw.print()
    + " ";

  result += "<b>Spell Resistance:</b> "
    + pspell->spell_resistance.print();

  result += "\n<b>Description:</b>\n"
    + pspell->description;

  spell_label_.set_markup( result );
}
