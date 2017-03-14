#include "FileSystem.h"

#include <vector>

#include <zlib.h>

bool FileSystem::m_usePackage = false;
std::ifstream FileSystem::m_package;
std::map<std::string, FileSystem::FileInfo> FileSystem::m_files;

std::string DecompressBuffer(const std::vector<char>& buffer)
{
	z_stream zs;
	memset(&zs, 0, sizeof(zs));

	if (inflateInit(&zs) != Z_OK) {
		throw(std::runtime_error("inflateInit failed while decompressing."));
	}

	zs.next_in = (Bytef*)buffer.data();
	zs.avail_in = static_cast<uInt>(buffer.size());

	int ret;
	char outbuffer[32768];
	std::string outstring;

	do {
		zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
		zs.avail_out = sizeof(outbuffer);

		ret = inflate(&zs, 0);

		if (outstring.size() < zs.total_out) {
			outstring.append(outbuffer,
				zs.total_out - outstring.size());
		}

	} while (ret == Z_OK);

	inflateEnd(&zs);

	if (ret != Z_STREAM_END) {
		throw std::runtime_error(zs.msg);
	}

	return outstring;
}

void FileSystem::SetPackage(const std::string & path)
{
	m_usePackage = true;
	m_package.open(path, std::ios::binary);
	if (m_package.is_open()) {
		m_package.seekg(6);

		unsigned int numFiles;
		m_package.read(reinterpret_cast<char*>(&numFiles), sizeof(numFiles));

		for (unsigned int i = 0; i < numFiles; ++i) {
			unsigned int nameLength;
			m_package.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

			std::string name(nameLength, '\0');
			m_package.read(&name[0], nameLength);

			FileInfo file;
			m_package.read(reinterpret_cast<char*>(&file.packageOffset), sizeof(file.packageOffset));
			m_package.read(reinterpret_cast<char*>(&file.compressedSize), sizeof(file.compressedSize));

			m_files[name] = file;
		}
	}
	else {
		throw std::runtime_error("Unable to open package file: \"" + path + "\"");
	}
}

std::string FileSystem::GetFileData(const std::string & path)
{
	if (m_usePackage) {
		auto it = m_files.find(path);
		if (it != m_files.end()) {
			FileInfo file = it->second;
			std::vector<char> buffer(file.compressedSize);
			m_package.seekg(file.packageOffset);
			m_package.read(reinterpret_cast<char*>(&buffer[0]), buffer.size());

			return DecompressBuffer(buffer);
		}
	}
	else {
		std::FILE* file = std::fopen(path.c_str(), "rb");
		if (file) {
			std::fseek(file, 0, SEEK_END);

			unsigned int sourceLength = static_cast<unsigned int>(std::ftell(file));

			std::string source;
			source.resize(sourceLength);

			std::rewind(file);
			size_t resultLength = std::fread(&source[0], 1, source.size(), file);
			std::fclose(file);

			return source;
		}
	}

	throw std::runtime_error("Unable to load file: \"" + path + "\"");
}
