#pragma once

#include "Dimention.h"

namespace NanMonkey
{
	class Tag;

	class Stage
	{
	public:
		static std::shared_ptr<Stage> FactoryTag(const Dimention& dimention, const std::vector<Tag>& tag);
		static std::shared_ptr<Stage> Factory(const Dimention& dimention, const std::vector<float>& data);

		Stage(const Dimention& dimention, const std::vector<float>& data = std::vector<float>());

		const bool CheckDimention(const Dimention& dimention) const;
		const float GetValue(const Index& index) const;

		static void DeltaVisitor(const Stage& target, const Stage& actualResult, const std::function<void(const float)>& visitor);
		//static void GatherDelta(std::vector<float>& delta, const Stage& target, const Stage& actualResult);

	private:
		Dimention m_dimention;
		std::vector<float> m_data;
	};
}