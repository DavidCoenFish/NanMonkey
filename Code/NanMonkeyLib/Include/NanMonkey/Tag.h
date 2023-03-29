#pragma once

namespace NanMonkey
{
	class Tag
	{
	public:
		Tag(
			const std::string& name//,
			//const float value
			);
		const std::string GetName() const { return m_name; }
		//const float GetValue() const { return m_value; }
	private:
		std::string m_name;
		//flag screen based pixel coord x, y
		//float m_value;
	};
}