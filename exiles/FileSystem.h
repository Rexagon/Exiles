#pragma once

#include <string>
#include <fstream>
#include <map>

class FileSystem
{
public:
	// Меняет источник данных для игры на указанный архив
	static void SetPackage(const std::string& path);

	// Возвращает массив байтов указанного файла
	//@ если не была вызвана ф-я SetPackage, то путь относительно корня игры
	//@ если используется архив, то соответствующий файл ищется в нём
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