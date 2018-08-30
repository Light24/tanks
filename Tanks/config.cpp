#include "Config.h"

namespace Config_Parser
{
#define PARSER_PARAMETER_COMMENT '#'
#define PARSER_PARAMETER_NEXT    ':'

	bool Is_Comment_Line(const char *in_Buf)
	{
		// symbol '#' precedes comment line, skip line
		return (in_Buf[0] == PARSER_PARAMETER_COMMENT);
	}

	const char *Get_Word_Pos_End(const char *in_Buf)
	{
		const size_t size = strlen(in_Buf);
		if (!size)
			return NULL;

		for (size_t i = 0; i != size; ++i)
		{
			if (in_Buf[i] == PARSER_PARAMETER_NEXT)
				return &in_Buf[i];
		}

		return (in_Buf + size);
	}

	const char *Read(const char *in_Buf, std::string &out_Val)
	{
		const char *pWordEnd = NULL;
		pWordEnd = Config_Parser::Get_Word_Pos_End(in_Buf);
		if (pWordEnd)
			out_Val = std::string(in_Buf, 0, (pWordEnd - in_Buf));

		if (*pWordEnd == PARSER_PARAMETER_NEXT)
			++pWordEnd;
		return pWordEnd;
	}

	const char *Read(const char *in_Buf, float &out_Val)
	{
		const char *pWordEnd = NULL;
		pWordEnd = Config_Parser::Get_Word_Pos_End(in_Buf);
		if (pWordEnd)
			out_Val = std::stof(std::string(in_Buf, 0, (pWordEnd - in_Buf)));

		if (*pWordEnd == PARSER_PARAMETER_NEXT)
			++pWordEnd;
		return pWordEnd;
	}

	const char *Read(const char *in_Buf, int &out_Val)
	{
		const char *pWordEnd = NULL;
		pWordEnd = Config_Parser::Get_Word_Pos_End(in_Buf);
		if (pWordEnd)
			out_Val = std::stoi(std::string(in_Buf, 0, (pWordEnd - in_Buf)));

		if (*pWordEnd == PARSER_PARAMETER_NEXT)
			++pWordEnd;
		return pWordEnd;
	}
}

bool ConfigManager::Load(const char *path)
{
	FILE *pFile = fopen(path, "r");
	if (!pFile)
	{
		printf("File %s not found", path);
		return false;
	}

	const size_t Buffer_Size = 256;
	char buf[Buffer_Size];

	size_t readSize;
	while ((readSize = this->Read_Line(pFile, buf, Buffer_Size)))
	{
		if (Config_Parser::Is_Comment_Line(buf))
			continue;

		const GameObject *prototype = GameObject::Create(buf);
		m_Prototypes[prototype->GetType()] = prototype;
	}

	fclose(pFile);
	return true;
}

size_t ConfigManager::Read_Line(FILE *in_File, char *out_Buf, const size_t in_BufSize) const
{
	char *pBuf = out_Buf;

	size_t readCount;
	while ((readCount = fread(pBuf, sizeof(char), 1, in_File)))
	{
		pBuf += readCount;

		if (*(pBuf - 1) == '\n')
		{
			*(pBuf - 1) = '\0';
			break;
		}

		if ((pBuf - out_Buf) >= in_BufSize)
		{
			printf("Buffer too small for read line");
			debug_assert("Buffer too small for read line");
			*(pBuf) = '\0';
			break;
		}
	}

	return (pBuf - out_Buf);
}

GameObject *ConfigManager::Create_Object(Object_Type type) const
{
	auto it = m_Prototypes.find(type);
	if (it == m_Prototypes.end())
	{
		printf("Create object error: not found prototype for type %d", (int)type);
		return NULL;
	}

	return it->second->Clone();
}
