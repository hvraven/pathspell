#ifndef LIBRPG_ELEMENTFILTERLIST_H
#define LIBRPG_ELEMENTFILTERLIST_H

namespace RPG
{
	
	template <typename T>
	class ElementFilterList<T> : public RPG::ElementList<T>
	{
	public:
		virtual void add_filter(Filter);
		virtual void remove_filter(int);
		virtual void clear_filter();
		virtual void activate_filter();
		virtual void deactivate_filter();
		virtual void toggle_filter();

		virtual bool filter_is_active();

	private:
		std::vector<Filter> filters_;
		bool filter_state_;
	};

}

#endif /* LIBRPG_ELEMENTFILTERLIST_H */
