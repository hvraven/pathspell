#ifndef LIBRPG_GENERIC_H
#define LIBRPG_GENERIC_H

#include <string>
#include <vector>
#include <unordered_map>

typedef std::string Identifier

namespace RPG
{
	class Element
	{
	public:
		Element(const Identifier&);

		const Identifier& get_identifier() const 
		{
		  return identifier_;
		}

	private:
		const Identifier identifier_;
	};

	template <typename T>
	class Access<T>
	{
	public:
		Access<T>() {};

		virtual bool has_element(const Identifier&) const = 0;
		virtual const T& get_element(const Identifier&) const = 0;
		virtual void import_elements(const Access<T>&) = 0;
		virtual std::vector<T> export_elements() const = 0;

		virtual void add_element(const T&) = 0;
		
	private:
		std::unordered_map<Identifier, T> elements_;
	};

	template<typename T>
	class ElementList<T>
	{
	public:
		virtual void add_element(const T&);
		virtual void remove_element(const T&);
		virtual bool has_element(const T&);
		virtual bool has_element(const Identifier&);

		virtual void import_elements(const Access&);
		virtual void export_elements(const Access&);
	};

	template <typename T>
	class ElementSortList<T> : public ElementList<T>
	{

	};

	class Filter
	{
	public:

	private:

	};

	template <typename T>
	class ElementFilterList<T> : public ElementList<T>
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

#endif /* LIBRPG_GENERIC_H */
