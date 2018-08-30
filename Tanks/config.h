#pragma once
#include "game-object.h"

namespace Config_Parser
{
	bool Is_Comment_Line(const char *in_Buf);
	const char *Read(const char *in_Buf, std::string &out_Val);
	const char *Read(const char *in_Buf, int &out_Val);
	const char *Read(const char *in_Buf, float &out_Val);
}

class ConfigManager
{
public:
	bool Load(const char *path);
	// const Object *Get_Prortype();
	GameObject *Create_Object(Object_Type type) const;

private:
	size_t Read_Line(FILE *in_File, char *out_Buf, const size_t in_BufSize) const;

private:
	std::map<Object_Type, const GameObject *> m_Prototypes;

};