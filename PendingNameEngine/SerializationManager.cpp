#include "SerializationManager.h"

SerializationManager::SerializationManager(bool start_enabled)
{
}

SerializationManager::~SerializationManager()
{
}



JSONFile * SerializationManager::ReadWriteFile(const char * path, int r_w)
{
	if (r_w == 0) //READ
	{
		FILE* fp = fopen(path, "rb");
		char readBuffer[65536];

		if (fp != nullptr)
			return new JSONFile(new rapidjson::FileReadStream(fp, readBuffer, sizeof(readBuffer)), fp);
		else
			return nullptr;
	}
	else //WRITE
	{
		FILE* fp = fopen(path, "wb");
		char writeBuffer[65536];

		if (fp != nullptr)
			return new JSONFile(new rapidjson::FileWriteStream(fp, writeBuffer, sizeof(writeBuffer)), fp);
		else
			return nullptr;
	}
}

void SerializationManager::CloseFile(JSONFile * file)
{
	fclose(file->f);
	RELEASE(file);

	file = nullptr;
}

JSONFile::JSONFile(rapidjson::FileWriteStream * os, FILE * fp): os(os), f(fp)
{
	document = new rapidjson::Document();
	document->SetObject();

	allocator = &document->GetAllocator();
}

JSONFile::JSONFile(rapidjson::FileReadStream * is, FILE * fp): is(is), f(fp)
{
	document = new rapidjson::Document();
	document->ParseStream(*is);

	allocator = &document->GetAllocator();
}

JSONFile::~JSONFile()
{
	

	RELEASE(document);

	RELEASE(is);
	RELEASE(os);
}


