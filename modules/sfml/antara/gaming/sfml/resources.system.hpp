/******************************************************************************
 * Copyright © 2013-2019 The Komodo Platform Developers.                      *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * Komodo Platform software, including this file may be copied, modified,     *
 * propagated or distributed except according to the terms contained in the   *
 * LICENSE file                                                               *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

#pragma once

#include <filesystem>
#include <utility>
#include <entt/core/hashed_string.hpp>
#include "antara/gaming/sfml/resources.loader.hpp"
#include "antara/gaming/core/real.path.hpp"

namespace antara::gaming::sfml
{
    class resources_system
    {
    public:
        template<typename TLoader, typename TCache, typename ... TArgs>
        static auto load(TCache &cache, const char *id, TArgs &&...args)
        {
            const auto identifier = entt::hashed_string::to_value(id);
            return cache.template load<TLoader>(identifier, std::forward<TArgs>(args)...);
        }

        auto load_texture(const char *resource_id)
        {
            return resources_system::load<textures_loader, textures_cache>(textures_cache_, resource_id,
                                                                           (textures_path_ / resource_id).string());
        }

        auto load_font(const char *resource_id)
        {
            return resources_system::load<fonts_loader, fonts_cache>(fonts_cache_, resource_id,
                                                                     (fonts_path_ / resource_id).string());
        }

    private:
        std::filesystem::path assets_path_{antara::gaming::core::assets_real_path()};
        std::filesystem::path musics_path_{assets_path_ /= "musics"};
        std::filesystem::path textures_path_{assets_path_ /= "textures"};
        std::filesystem::path fonts_path_{assets_path_ /= "fonts"};
        std::filesystem::path sounds_path{assets_path_ /= "sounds"};
        textures_cache textures_cache_;
        musics_cache musics_cache_;
        sounds_cache sounds_cache_;
        fonts_cache fonts_cache_;
    };
}