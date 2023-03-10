namespace NanMonkey
{
#if defined(UNITTEST)
	const bool UnitTest();
#endif

	const int GetSize(const int x, const int y, const int z);
	const int GetOffset(const int x, const int y, const int z, const int indexX, const int indexY, const int indexZ);

	//const int GetOffset(const int x, const int y, const int z, const int indexX, const int indexY, const int indexZ);
	const float Clamp(const float input, const float lowInclusive = -1.0f, const float hightInclusive = 1.0f);

	const float ByteToNormalisedFloat(const unsigned char value);
	const float ByteToFloat(const unsigned char value);

};