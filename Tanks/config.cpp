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

	const char *Read(const char *in_Buf, size_t &out_Val)
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

File::File() : m_Handle(NULL)
{

}

File::~File()
{

}


bool File::Open(const char *in_Path, const char *in_Mode)
{
	m_Handle = fopen(in_Path, in_Mode);
	if (!in_Path)
	{
		printf("File %s not found", in_Path);
		return false;
	}

	return true;
}

void File::Close()
{
	fclose(m_Handle);
	m_Handle = NULL;
}

bool File::ReadLine(std::string &out_Buf)
{
	if (!IsFileOpened())
		return false;
	if (IsFileEof())
		return false;

	const size_t Buffer_Size = 256;
	char buf[Buffer_Size];

	char readedChar;
	while (fread(&readedChar, sizeof(char), 1, m_Handle))
	{
		if (readedChar == '\n')
			break;

		out_Buf += readedChar;
	}

	return true;
}

bool File::WriteBuf(const char *in_Buf)
{
	if (!IsFileOpened())
		return false;

	const size_t writedBytes = fwrite(in_Buf, strlen(in_Buf), 1, m_Handle);
	return (writedBytes == strlen(in_Buf));
}

bool File::IsFileEof() const
{
	return feof(m_Handle);
}

bool File::IsFileOpened() const
{
	return m_Handle;
}


bool ConfigManager::LoadGameObjects(const char *path)
{
	File file;
	file.Open(path, "r");
	if (!file.IsFileOpened())
		return false;

	std::string strLine;
	while (file.ReadLine(strLine))
	{
		if (Config_Parser::Is_Comment_Line(strLine.c_str()))
		{
			strLine.clear();
			continue;
		}

		const GameObject *prototype = GameObject::Create(strLine.c_str());
		m_Prototypes[prototype->GetType()] = prototype;

		strLine.clear();
	}
	file.Close();

	return true;
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


void ConfigManager::SaveLevel(const char *in_FilePath, Container<GameObject> *in_Container)
{
	File file;
	file.Open(in_FilePath, "w");
	for (size_t i = 0; i != in_Container->GetWidgetsCount(); ++i)
	{
		const GameObject *object = in_Container->GetWidget(i);
		std::string objectBuf;
		saveObject(object, objectBuf);
		file.WriteBuf(objectBuf.c_str());
		file.WriteBuf("\n");
	}
}

void ConfigManager::LoadLevel(const char *in_FilePath, Container<GameObject> *in_Container)
{
	File file;
	file.Open(in_FilePath, "r");

	std::string buf;
	while (file.ReadLine(buf))
	{
		GameObject *object;
		loadObject(buf.c_str(), &object);

		in_Container->AddWidget(object);
	}
}

bool ConfigManager::saveObject(const GameObject *in_Object, std::string &out_Buf) const
{
	const size_t &type = in_Object->GetType();
	out_Buf += type;

	const sf::Vector2f &pos = in_Object->GetPos();
	out_Buf += pos.x;
	out_Buf += pos.y;

	return true;
}

bool ConfigManager::loadObject(const char *in_Buf, GameObject **out_Object) const
{
	size_t type;
	Config_Parser::Read(in_Buf, type);
	*out_Object = this->Create_Object((Object_Type) type);

	sf::Vector2f pos;
	Config_Parser::Read(in_Buf, pos.x);
	Config_Parser::Read(in_Buf, pos.y);
	(*out_Object)->SetPos(pos);

	return true;
}
