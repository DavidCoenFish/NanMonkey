#pragma once

#include "Dimention.h"

/*
want more data for each pixel to guide training
*/
namespace NanMonkey
{
	class Stage;

	class TrainingScore
	{
	public:
		class PixelData
		{
		public:
			PixelData();
			void AddSample(const float target, const float actualResult);

			const float GetAverage() const;
			const float GetScore() const;

			//void AddTarget(const float );
		private:
			int m_sampleCount;
			float m_sumPositive;
			float m_sumNegative;

			bool m_targetValid;
			float m_targetLow;
			float m_targetHigh;
		};

		TrainingScore(const Dimention& dimention);

		void GatherScore(const Stage& target, const Stage& actualResult);
		const float GetDeltaScore();

		const Dimention& GetDimention() const { return m_dimention; }

		//BackwardsPropegateScore(const NeuralNetwork& neuralNetwork);
		//GatherWorstPixels(std::vector<{step,index,score}>&, const int maxGather = 16);
	private:
		Dimention m_dimention;
		std::vector<PixelData> m_pixelDataArray;

		bool m_deltaScoreValid;
		float m_deltaScore;

	};
}