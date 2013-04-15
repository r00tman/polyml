#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace pml
{
	class pml_node
	{
	private:
		std::string m_data;
		std::vector<pml_node*> m_children;
		size_t size();
		size_t children_size();

	public:
		pml_node(std::string data = "");
		virtual ~pml_node();

		void set_data(const std::string &data);
		std::string data() const;

		void add_child(pml_node *child);
		const std::vector<pml_node*> *get_children() const;
		size_t children_count() const;

		void write(std::ostream &stream);
		void read(std::istream &stream);

		bool operator ==(const pml_node &b) const;
		bool operator !=(const pml_node &b) const;
	};
}
