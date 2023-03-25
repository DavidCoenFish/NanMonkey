#include "Index.h"

namespace NanMonkey
{
	class StagePixel
	{
	private:
		class Reference
		{
		private:
			float m_weight;
			StageIndex m_index;
		}

		std::vector<Reference> m_inputArray;
	};
}