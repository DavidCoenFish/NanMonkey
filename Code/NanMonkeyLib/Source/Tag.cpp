#include "pch.h"
#include "NanMonkey/Tag.h"


NanMonkey::Tag::Tag(
	const std::string& name,
	const float value
	)
	: m_name(name)
	, m_value(value)
{
	return;
}
