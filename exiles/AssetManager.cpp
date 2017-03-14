#include "AssetManager.h"

std::map<std::string, std::function<asset_ptr ()>> AssetManager::m_factories;

void AssetManager::Bind(const std::string & name, std::function<asset_ptr ()> factory)
{
	m_factories[name] = factory;
}

void AssetManager::Unbind(const std::string & name)
{
	auto it = m_factories.find(name);
	if (it != m_factories.end()) {
		m_factories.erase(it);
	}
}

void AssetManager::Clear()
{
	m_factories.clear();
}
