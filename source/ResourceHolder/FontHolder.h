#pragma once
#include "ResourceIdentifier.h"

#include "raylib.h"

#include <string>
#include <map>
#include <memory>

class FontHolder
{
public:
	FontHolder();
	~FontHolder();

	static FontHolder& getInstance();
	void load(FontID id, const std::string& filename);
	Font& get(FontID id);
	const Font& get(FontID id) const;
private:
	std::map<FontID, std::unique_ptr<Font>> mResourceMap;
};

