#include "pml_node.h"

namespace pml
{
	void write_size_t(std::ostream &stream, size_t s) {
		union
		{
			size_t sz;
			char data[4];
		};
		sz = s;
		stream.write(data, 4);
	}

	size_t read_size_t(std::istream &stream) {
		union
		{
			size_t sz;
			char data[4];
		};

		stream.read(data, 4);
		return sz;
	}

	pml_node::pml_node(const std::vector<char> &data) : 
		m_data(data)
	{
	}

	pml_node::pml_node(const std::string &data) : 
		m_data(data.begin(), data.end())
	{
	}

	pml_node::~pml_node()
	{
		for (size_t i = 0; i < children_count(); i++) 
		{
			if (m_children[i] != NULL) 
			{
				delete m_children[i];
				m_children[i] = NULL;
			}
		}
	}

	void pml_node::set_data(const std::vector<char> &data)
	{
		m_data = data;
	}
	
        void pml_node::set_data(const std::string &data)
	{
		m_data = std::vector<char>(data.begin(), data.end());
	}

	std::vector<char> pml_node::data() const
	{
		return m_data;
	}

	std::string pml_node::str_data() const
	{
		return std::string(m_data.begin(), m_data.end());
        }

	void pml_node::add_child(pml_node *child)
	{
		m_children.push_back(child);
	}

	const std::vector<pml_node*> *pml_node::get_children() const
	{
		return &m_children;
	}

	size_t pml_node::children_count() const
	{
		return m_children.size();
	}

	void pml_node::write(std::ostream &stream)
	{
		write_size_t(stream, size());
		write_size_t(stream, children_size());

		stream.write(&(*m_data.begin()), m_data.size());

		for (size_t i = 0; i < m_children.size(); i++)
			m_children[i]->write(stream);
	}

	size_t pml_node::size()
	{
		return sizeof(size_t) + sizeof(size_t) + children_size() + m_data.size();
	}

	size_t pml_node::children_size()
	{
		size_t sz = 0;
		for (size_t i = 0; i < m_children.size(); i++)
			sz += m_children[i]->size();
		return sz;
	}

	void pml_node::read(std::istream &stream)
	{
		size_t total_size = read_size_t(stream);
		size_t child_size = read_size_t(stream);

		size_t data_size = total_size - child_size - sizeof(size_t) - sizeof(size_t);

		m_data.resize(data_size, 0);
		stream.read(&m_data[0], data_size);

		size_t start_pos = stream.tellg();
		size_t current_pos = start_pos;
		while (current_pos - start_pos < child_size)
		{
			pml_node *child = new pml_node();
			child->read(stream);
			m_children.push_back(child);
			current_pos = stream.tellg();
		}
	}

	bool pml_node::operator==(const pml_node &b) const
	{
		if (children_count() != b.children_count())
		{
			return false;
		}

		if (data() != b.data())
		{
			return false;
		}

		for (size_t i = 0; i < children_count(); i++)
		{
			if (*(*get_children())[i] != *(*b.get_children())[i])
			{
				return false;
			}
		}
		return true;
	}

	bool pml_node::operator!=(const pml_node &b) const
	{
		return !(*this==b);
	}
}
