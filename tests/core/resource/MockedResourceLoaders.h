#ifndef IRE_MOCKED_RESOURCE_LOADERS_H
#define IRE_MOCKED_RESOURCE_LOADERS_H

#include "core/resource/ResourceLoader.h"
#include "core/resource/ResourcePath.h"

namespace ire::core::resource_loaders {

    template <>
    struct ResourceLoader<std::string>
    {
        using ResourceType = std::string;
        using ResourceStorageType = std::string;

        static inline ResourceStorageType load(const ResourcePath& path)
        {
            return "TestString " + path.fspath().filename().string();
        }
    };

    template <>
    struct ResourceLoader<int>
    {
        using ResourceType = int;
        using ResourceStorageType = std::unique_ptr<int>;

        static inline ResourceStorageType load(const ResourcePath& path)
        {
            return std::make_unique<int>(std::stoi(path.fspath().string()));
        }

        static inline const int& unpack(const ResourceStorageType& packed)
        {
            return *packed;
        }
    };

}

#endif // !IRE_MOCKED_RESOURCE_LOADERS_H
