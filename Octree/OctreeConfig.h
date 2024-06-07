#pragma once

#include <array>
#include <vector>
#include <functional>
#include <string>
#include <unordered_map>
#include <iostream>


using OctPointType = unsigned char;

enum class OctPoint : OctPointType
{
	Root = 0,
	NF1 = 1 << 0,
	NF2 = 1 << 1,
	NF3 = 1 << 2,
	NF4 = 1 << 3,
	NB1 = 1 << 4,
	NB2 = 1 << 5,
	NB3 = 1 << 6,
	NB4 = 1 << 7,
};


struct OctVector3
{
	union
	{
		float position[3];
		struct
		{
			float x;
			float y;
			float z;
		};
	};

	OctVector3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	OctVector3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	OctVector3 operator/(const float& value)
	{
		return OctVector3(this->x / value, this->y / value, this->z / value);
	}

	OctVector3 operator*(const float& value)
	{
		return OctVector3(this->x * value, this->y * value, this->z * value);
	}

	OctVector3 operator+(const OctVector3& vec3)
	{
		return OctVector3(this->x + vec3.x, this->y + vec3.y, this->z + vec3.z);
	}

	OctVector3 operator-(const OctVector3& vec3)
	{
		return OctVector3(this->x - vec3.x, this->y - vec3.y, this->z - vec3.z);
	}

	bool operator==(const OctVector3& vec3)
	{
		return this->x == vec3.x && this->y == vec3.y && this->z == vec3.z;
	}

	bool operator<=(const OctVector3& vec3)
	{
		return this->x <= vec3.x && this->y <= vec3.y && this->z <= vec3.z;
	}

	bool operator<(const OctVector3& vec3)
	{
		return this->x < vec3.x && this->y < vec3.y && this->z < vec3.z;
	}

	bool operator>=(const OctVector3& vec3)
	{
		return this->x >= vec3.x && this->y >= vec3.y && this->z >= vec3.z;
	}

	bool operator>(const OctVector3& vec3)
	{
		return this->x > vec3.x && this->y > vec3.y && this->z > vec3.z;
	}

	OctVector3& operator+=(const OctVector3& vec3)
	{
		this->x += vec3.x;
		this->y += vec3.y;
		this->z += vec3.z;
		return *this;
	}

	OctVector3& operator-=(const OctVector3& vec3)
	{
		this->x -= vec3.x;
		this->y -= vec3.y;
		this->z -= vec3.z;
		return *this;
	}
};

struct OctreeConfig
{
	static int SplitCount;
	static float MinBounds;
	static int ChildrenCount;
	static std::string getName(OctPoint point)
	{
		switch (point)
		{
		case OctPoint::Root:return "Root";
		case OctPoint::NF1:return "NF1";
		case OctPoint::NF2:return "NF2";
		case OctPoint::NF3:return "NF3";
		case OctPoint::NF4:return "NF4";
		case OctPoint::NB1:return "NB1";
		case OctPoint::NB2:return "NB2";
		case OctPoint::NB3:return "NB3";
		case OctPoint::NB4:return "NB4";
		default: return "Error";
		}
	}
};

