#pragma once

#include "Index.h"

namespace NanMonkey
{
	//class Index;

	class Dimention
	{
	public:
		//struct Iterator 
		//{
		//	using iterator_category = std::forward_iterator_tag;
		//	using difference_type   = std::ptrdiff_t;
		//	using value_type        = Index;
		//	using pointer           = value_type*;
		//	using reference         = value_type&;

		//	reference operator*() const;// { return *m_ptr; }
		//	pointer operator->();// { return m_ptr; }

		//	// Prefix increment
		//	Iterator& operator++(); //{ m_ptr++; return *this; }  

		//	// Postfix increment
		//	Iterator operator++(int);// { Iterator tmp = *this; ++(*this); return tmp; }

		//	friend bool operator== (const Iterator& a, const Iterator& b);// { return a.m_index == b.m_index; };
		//	friend bool operator!= (const Iterator& a, const Iterator& b);// { return a.m_index != b.m_index; };     

		//private:
		//	Dimention m_dimention;
		//	int m_offset;
		//};

		Dimention(const std::vector<int>& dimention);
		const int GetCount() const;
		const int GetValue(const int index) const;

		const int CalculateLength() const;
		const int CalculateOffset(const Index& index) const;
		const Index ReverseCalculateOffset(const int offset) const;

		const bool operator==(const Dimention& rhs) const;
		const bool operator!=(const Dimention& rhs) const;

	private:
		std::vector<int> m_data;
	};
}