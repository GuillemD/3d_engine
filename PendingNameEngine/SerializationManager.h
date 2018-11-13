#ifndef _SERIALIZATION_H_
#define _SERIALIZATION_H_

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/filereadstream.h"
#include "Globals.h"
#include "MathGeoLib\MathGeoLib.h"

#include <vector>


struct JSON_Value
{
public:

	JSON_Value(rapidjson::Document::AllocatorType* allocator) : allocator(allocator)
	{
		value = new rapidjson::Value(rapidjson::kObjectType);
	}

	~JSON_Value();

	//This will remove all added elements of the JSON_Value
	void convertToArray();

	void addInt(const char* name, int value);
	void addUint(const char* name, uint value);
	void addFloat(const char* name, float value);
	void addString(const char* name, const char* value);
	void addBool(const char* name, bool value);
	void addVector2(const char* name, float2 vec);
	void addVector3(const char* name, float3 vec);
	void addQuat(const char* name, Quat quat);
	void addTransform(const char* name, float4x4 mat);

	int getInt(const char* name);
	uint getUint(const char* name);
	float getFloat(const char* name);
	const char* getString(const char* name);
	bool getBool(const char* name);
	float2 getVector2(const char* name);
	float3 getVector3(const char* name);
	Quat getQuat(const char* name);
	float4x4 getTransform(const char* name);

	JSON_Value* createValue();
	void addValue(const char* name, JSON_Value* value);
	JSON_Value* getValue(const char* name);
	JSON_Value* getValueFromArray(int index);

	void setValue(rapidjson::Value* value);
	rapidjson::Value* getRapidJSONValue();

private:

	rapidjson::Value* value = nullptr;
	rapidjson::Document::AllocatorType* allocator = nullptr;
	std::vector<JSON_Value*> allocatedValues;
};

struct JSON_File
{
public:

	JSON_File(rapidjson::FileWriteStream* os, FILE* fp);
	JSON_File(rapidjson::FileReadStream* is, FILE* fp);
	~JSON_File();

	bool Write();

	JSON_Value* createValue();
	void addValue(const char* name, JSON_Value* value);
	JSON_Value* getValue(const char* name);

	void closeFile();

private:

	FILE * fp = nullptr;

	rapidjson::Document* document = nullptr;
	rapidjson::FileWriteStream* os = nullptr;
	rapidjson::FileReadStream* is = nullptr;

	rapidjson::Document::AllocatorType* allocator = nullptr;
	std::vector<JSON_Value*> allocatedValues;
};
#endif // !_SERIALIZATION_H_

