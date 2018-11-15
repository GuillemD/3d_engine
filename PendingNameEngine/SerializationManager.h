#ifndef _SERIALIZATION_H_
#define _SERIALIZATION_H_

#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/filereadstream.h"
#include "Globals.h"
#include "MathGeoLib\MathGeoLib.h"

#include <list>

#include "Module.h"
struct JSONFile
{
public:

	JSONFile(rapidjson::FileWriteStream* os, FILE* fp);
	JSONFile(rapidjson::FileReadStream* is, FILE* fp);
	~JSONFile();


	FILE * f = nullptr;

	rapidjson::Document* document = nullptr;
	rapidjson::Document::AllocatorType* allocator = nullptr;
private:
	rapidjson::FileWriteStream* os = nullptr;
	rapidjson::FileReadStream* is = nullptr;	

};

class SerializationManager: public Module {
public:
	SerializationManager(bool start_enabled = true);
	~SerializationManager();

	JSONFile* ReadWriteFile(const char* path, int r_w);
	void CloseFile(JSONFile* file);

};
#endif // !_SERIALIZATION_H_

