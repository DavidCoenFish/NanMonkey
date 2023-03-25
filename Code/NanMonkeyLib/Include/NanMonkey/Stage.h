#pragma once

#include "Dimention.h"

namespace NanMonkey
{
	class Stage
	{
	public:
		Stage(const Dimention& dimention, const std::vector<float>& data = std::vector<float>());

		const bool CheckDimention(const Dimention& dimention) const;
		const float GetValue(const Index& index) const;

	private:
		Dimention m_dimention;
		std::vector<float> m_data;
	};
}