#include "FontHolder.h"
#include <assert.h>
#include <utility>

FontHolder::FontHolder()
{
}

FontHolder::~FontHolder()
{
    for (auto& p : this->mResourceMap)
        UnloadFont(*p.second); 
}

FontHolder& FontHolder::getInstance()
{
    // TODO: insert return statement here
    static FontHolder instance; 
    return instance;
}

void FontHolder::load(FontID id, const std::string& filename)
{
    std::unique_ptr<Font> resource(new Font()); 
    *resource = LoadFontEx(filename.c_str(), 72, nullptr, 0);
    auto inserted = this->mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

Font& FontHolder::get(FontID id)
{
    // TODO: insert return statement here
    auto found = this->mResourceMap.find(id); 
    assert(found != this->mResourceMap.end());
    return *found->second.get();
}

const Font& FontHolder::get(FontID id) const
{
    // TODO: insert return statement here
    auto found = this->mResourceMap.find(id);
    assert(found != this->mResourceMap.end());
    return *found->second.get();
}
