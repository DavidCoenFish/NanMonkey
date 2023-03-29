#pragma once

#include "Stage.h"

namespace NanMonkey
{
	class TrainingData
	{
	public:
		class Data
		{
		public:
			Data(const std::shared_ptr<Stage>& input, const std::shared_ptr<Stage>& target);

			const Stage& GetInput() const { return (*m_input); }
			const Stage& GetTarget() const { return (*m_target); }

		private:
			std::shared_ptr<Stage> m_input;
			std::shared_ptr<Stage> m_target;
		};

	public:
		TrainingData(const std::vector<std::shared_ptr<Data>>& dataArray = std::vector<std::shared_ptr<Data>>());

		void Visit(const std::function<void(const Stage&,const Stage&)>& visitor) const;

	private:
		std::vector<std::shared_ptr<Data>> m_dataArray;

	};
}