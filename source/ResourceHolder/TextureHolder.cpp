#include "TextureHolder.h"

#include <utility>

TextureHolder::TextureHolder()
{
	this->mResourceMap[TextureID::None] = std::make_unique<Texture2D>(); 
}

TextureHolder::~TextureHolder()
{
	for (auto& texture : mResourceMap)
		UnloadTexture(*texture.second);
}

void TextureHolder::load(TextureID id, const std::string& filename)
{
	std::unique_ptr<Texture2D> resource(new Texture()); 
	*resource = LoadTexture(filename.c_str()); 
	auto inserted = this->mResourceMap.insert(std::make_pair(id, std::move(resource)));
	assert(inserted.second); 
}

Texture2D& TextureHolder::get(TextureID id)
{
	// TODO: insert return statement here
	auto found = this->mResourceMap.find(id); 
	if (found == this->mResourceMap.end())
	{
		return *mResourceMap[TextureID::None];
	}
	SetTextureFilter(*found->second, TEXTURE_FILTER_BILINEAR);
	return *found->second; 
}

const Texture2D& TextureHolder::get(TextureID id) const
{
	// TODO: insert return statement here
	auto found = this->mResourceMap.find(id);
	if (found == this->mResourceMap.end())
	{
		return *mResourceMap.at(TextureID::None);
	}
	SetTextureFilter(*found->second, TEXTURE_FILTER_BILINEAR);
	return *found->second;
}
