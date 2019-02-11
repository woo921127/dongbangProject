#pragma once

#define PI 3.141592f
#define PI2 2 * PI
#pragma warning(disable:4996)
namespace BRAVO_UTIL
{
	float getDistance(float x1, float y1, float x2, float y2);

	float getAngle(float x1, float y1, float x2, float y2);

	inline const string MakeImageName(const char* imageName, const char* folderName = nullptr)
	{
		string str = "";

		if (nullptr != folderName)
		{
			str.append(folderName);
			str.append("/");
		}

		str.append(imageName);
		str.append(".bmp");

		return str;
	}

	inline const string AppendInt(const char* imageName, int value)
	{
		string str = "";
		char num[128];

		itoa(value, num, 10);

		str.append(imageName);
		str.append(num);

		return str;
	}
}