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
	// Привязывает к имени фабрику ресурсов
	static void Bind(const std::string& name, std::function<asset_ptr()> factory);

	// Отвязывает от имени фабрику ресурсов
	static void Unbind(const std::string& name);

	// Возвращает объект из фабрики ресурсов для указанного имени
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

	// Удаляет все фабрики ресурсов
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