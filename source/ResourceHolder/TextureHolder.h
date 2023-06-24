#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H

#include "ResourceIdentifier.h"
#include "raylib.h"
#include <string>
#include <map>
#include <assert.h>
#include <memory>

class TextureHolder {
public:
	TextureHolder(); 
	~TextureHolder(); 

	void load(TextureID id, const std::string& filename);
	Texture2D& get(TextureID id); 
	const Texture2D& get(TextureID id) const; 
private:
	std::map<TextureID, std::unique_ptr<Texture2D>> mResourceMap;
};

#endif // !TEXTUREHOLDER_H

