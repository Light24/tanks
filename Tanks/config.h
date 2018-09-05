#pragma once
#include "game-object.h"
#include "container.h"
#include <functional>

namespace Config_Parser
{
	bool Is_Comment_Line(const char *in_Buf);
	const char *Read(const char *in_Buf, std::string &out_Val);
	const char *Read(const char *in_Buf, int &out_Val);
	const char *Read(const char *in_Buf, size_t &out_Val);
	const char *Read(const char *in_Buf, float &out_Val);
}

class File
{
public:
	File();
	~File();

public:
	bool Open(const char *in_Path, const char *in_Mode);
	void Close();

	bool ReadLine(std::string &out_Buf);
	bool WriteBuf(const char *in_Buf);

	bool IsFileEof() const;
	bool IsFileOpened() const;

private:
	FILE *m_Handle;
};

class ConfigManager
{
public:
	bool LoadGameObjects(const char *in_Path);
	// const Object *Get_Prortype();
	GameObject *Create_Object(Object_Subtype type) const;

	void SaveLevel(const char *in_FilePath, Container<Object> *in_Container);
	void LoadLevel(const char *in_FilePath, Container<Object> *in_Container);

public:
	typedef std::function <bool(const GameObject *)> EnumeratorPrototypes;
	void EnumeratePrototypes(EnumeratorPrototypes in_Enumerator);

private:
	bool saveObject(const GameObject *in_Object, std::string &out_Buf) const;
	bool loadObject(const char *in_Buf, GameObject **out_Object) const;

private:
	std::map<Object_Subtype, const GameObject *> m_Prototypes;

};