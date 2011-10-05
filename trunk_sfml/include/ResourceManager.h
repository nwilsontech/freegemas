/**
 * @file ResourceManager.h
 * 
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */


#ifndef _RESMANAGER_H_
#define _RESMANAGER_H_

#include <SFML/Graphics.hpp>

#include <tr1/unordered_map>
#include <tr1/memory>

#include <string>

#define ResMgr ResourceManager::instance()

/**
 * @class ResourceManager
 *
 * @brief Manages resources automatically collecting garbage.
 *
 * It uses shared pointers to manage resources ownership and usage,
 * deleting every unused resource. It collects garbage every time a
 * new resource is requested, or when collectGarbage() is manually
 * called.
 *
 * This class is a Singleton, so in order to
 * access any of its methods you can use:
 *
 * \code
 * ResourceManager::instance() -> method();
 * // or using the macro ResMgr
 * ResMgr -> method();
 * \endcode
 *
 * @author José Tomás Tocino García <theom3ga@gmail.com> 
 *
 */

class ResourceManager{
public:

    /// Returns the instance of the resource manager.
    static std::tr1::shared_ptr<ResourceManager> instance();

    static void delInstance();

    /// Returns the requested image
    sf::Image& getImage (std::string path);

    /// Returns a shared_ptr to the requested font.
    sf::Font& getFont (std::string path, size_t size);

    /// Checks usage of resources and collects garbage, freeing unused resources.
    void collectGarbage(std::string bypass = "");

    ~ResourceManager();
protected:

    /// Protected constructor to avoid multi-instantiation
    ResourceManager();

private:
    /// Map of loaded images
    std::tr1::unordered_map<std::string, sf::Image> imageMap;

    /// Map of loaded fonts
    std::tr1::unordered_map<std::string, sf::Font > fontMap;

    /// Iterator type definition for the map of images
    typedef std::tr1::unordered_map<std::string, sf::Image>::iterator imageMapIterator;

    /// Iterator type definition for the map of fonts
    typedef std::tr1::unordered_map<std::string, sf::Font >::iterator fontMapIterator;

    /// Instance of the class
    static std::tr1::shared_ptr<ResourceManager> pointerInstance;
};

#endif /* _RESMANAGER_H_ */
