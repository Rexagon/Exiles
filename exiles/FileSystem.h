#pragma once

#include <string>
#include <fstream>
#include <map>

class FileSystem
{
public:
	static void SetPackage(const std::string& path);

	static std::string GetFileData(const std::string& path);
private:
	static bool m_usePackage;
	static std::ifstream m_package;

	struct FileInfo
	{
		unsigned int packageOffset;
		unsigned int compressedSize;
	};

	static std::map<std::string, FileInfo> m_files;
};