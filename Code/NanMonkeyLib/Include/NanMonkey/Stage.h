#pragma once

#include "Dimention.h"

namespace NanMonkey
{
	class Tag;

	class Stage
	{
	public:
		static std::shared_ptr<Stage> FactoryTag(const Dimention& dimention, const std::vector<Tag>& tag, const std::map<std::string, float>& tagValue);
		static std::shared_ptr<Stage> Factory(const Dimention& dimention, const std::vector<float>& data);

		Stage(const Stage& rhs);
		Stage(const Dimention& dimention, const std::vector<float>& data = std::vector<float>());

		//const bool CheckDimention(const Dimention& dimention) const;
		const Dimention& GetDimention() const { return m_dimention; }
		const float GetValue(const Index& index) const;

		static void Visitor(const Stage& target, const std::function<void(const float)>& visitor);
		static void DeltaVisitor(const Stage& target, const Stage& actualResult, const std::function<void(const float, const float)>& visitor);
		//static void GatherDelta(std::vector<float>& delta, const Stage& target, const Stage& actualResult);

	private:
		Dimention m_dimention;
		std::vector<float> m_data;
	};
}