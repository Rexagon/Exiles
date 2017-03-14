#pragma once

#include <functional>
#include <memory>
#include <string>
#include <map>

#include "Log.h"

class Asset
{
public:
	virtual ~Asset() {}
};

typedef std::shared_ptr<Asset> asset_ptr;


class AssetManager
{
public:
	// ����������� � ����� ������� ��������
	static void Bind(const std::string& name, std::function<asset_ptr()> factory);

	// ���������� �� ����� ������� ��������
	static void Unbind(const std::string& name);

	// ���������� ������ �� ������� �������� ��� ���������� �����
	template<class T>
	static std::shared_ptr<T> Get(const std::string& name) 
	{
		auto it = m_factories.find(name);
		if (it == m_factories.end()) {
			return nullptr;
		}
		else {
			asset_ptr asset = it->second();

			auto raw = reinterpret_cast<T*>(asset.get());
			return std::shared_ptr<T>(asset, raw);
		}
	}

	// ������� ��� ������� ��������
	static void Clear();
private:
	static std::map<std::string, std::function<asset_ptr ()>> m_factories;
};


class AssetFactory {
public:
	virtual asset_ptr Load() = 0;

	asset_ptr operator()() 
	{
		return Load();
	}

	void SetFilePath(const std::string& path) { m_path = path; }
	std::string GetFilePath() const { return m_path; }
private:
	std::string m_path;
};