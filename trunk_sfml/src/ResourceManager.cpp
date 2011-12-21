#include "ResourceManager.h"
#include "log.h"
#include "Util.h"

#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>

#include <algorithm>

std::tr1::shared_ptr<ResourceManager> ResourceManager::pointerInstance;

std::tr1::shared_ptr<ResourceManager> ResourceManager::instance(){
    if(pointerInstance == 0)
        pointerInstance.reset(new ResourceManager);

    return pointerInstance;
}

void ResourceManager::delInstance(){
    if(pointerInstance != 0)
        pointerInstance.reset();
}

sf::Image& ResourceManager::getImage(std::string path){
    imageMapIterator it = imageMap.find(path);

    if(it == imageMap.end()){

        // Caution: unordered_map::insert returns a PAIR, with an iterator and a boolean
        it = imageMap.insert (std::make_pair(path, sf::Image())).first;
        it -> second.LoadFromFile (path);
        it -> second.SetSmooth (false);
    }
        
    return it -> second;
}

sf::Font& ResourceManager::getFont(std::string path, size_t size){
    std::string key = path + to_string(size);
    fontMapIterator it = fontMap.find(key);

    if(it == fontMap.end()){
        it = fontMap.insert (std::make_pair(key, sf::Font())).first;
        it -> second.LoadFromFile(path, size);
    }

    return it -> second;
}

ResourceManager::ResourceManager(){ 
    lDEBUG << Log::CON("ResourceManager");
}

ResourceManager::~ResourceManager(){ 
    lDEBUG << Log::DES("ResourceManager");
}

void ResourceManager::collectGarbage(std::string bypass){
    
}
