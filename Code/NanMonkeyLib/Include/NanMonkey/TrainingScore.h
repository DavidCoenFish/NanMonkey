#pragma once

#include "Dimention.h"

/*
want more data for each pixel to guide training
*/
namespace NanMonkey
{
	class Stage;
	class NeuralNetwork;
	class TrainingData;

	class TrainingScore
	{
	public:
		class PixelData
		{
		public:
			PixelData();
			void AddSample(const float delta);

			const float GetAverage() const;
			const float GetScore() const;

		private:
			int m_sampleCount;
			float m_sumPositive;
			float m_sumNegative;

		};

		class TargetData
		{
		public:
			TargetData();
			void AddSample(const float target);
			void Visit(const std::function<void(const bool, const float, const float)>& visitor) const;
		private:
			bool m_targetValid;
			float m_targetLow;
			float m_targetHigh;
		};

		//class ScoreStep
		//{
		//public:
		//	ScoreStep(const int size);
		//	void GatherScore(const NanMonkey::Stage& target, const NanMonkey::Stage& actualResult);
		//	const float GetDeltaScore();
		//private:
		//	std::vector<PixelData> m_pixelDataArray;
		//};

		static std::shared_ptr<TrainingScore> Factory(const Dimention& dimention, const NeuralNetwork& neuralNetwork, const TrainingData& trainingData);
		//TrainingScore(const Dimention& dimention, const std::vector<std::shared_ptr<ScoreStep>>& scoreStepArray, const std::vector<TargetData>& targetDataArray);
		TrainingScore(const Dimention& dimention, const std::vector<PixelData>& pixelDataArray, const std::vector<TargetData>& targetDataArray);

		const float GetDeltaScore();
		const Dimention& GetDimention() const { return m_dimention; }

		void VisitTargetRange(const std::function<void(const bool, const float, const float)>& visitor) const;

	private:
		Dimention m_dimention;
		//std::vector<std::shared_ptr<ScoreStep>> m_scoreStepArray;
		std::vector<PixelData> m_pixelDataArray;
		std::vector<TargetData> m_targetDataArray;

		bool m_deltaScoreValid;
		float m_deltaScore;

	};
}