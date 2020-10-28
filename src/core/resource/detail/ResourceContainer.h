#ifndef IRE_RESOURCE_CONTAINER_H
#define IRE_RESOURCE_CONTAINER_H

#include "core/resource/ResourceLoader.h"
#include "core/resource/ResourcePath.h"

#include <filesystem>
#include <memory>
#include <mutex>

namespace ire::core::detail {

    // This is not an abstract base class but is meant to be used as one.
    // It only exposes the path accessor.
    struct AnyResource
    {

        template <typename PathT>
        AnyResource(PathT&& path) :
            m_path(std::forward<PathT>(path))
        {
        }

        AnyResource(const AnyResource&) = delete;
        AnyResource(AnyResource&&) = delete;

        AnyResource& operator=(const AnyResource&) = delete;
        AnyResource& operator=(AnyResource&&) = delete;

        virtual ~AnyResource() = default;

        [[nodiscard]] const ResourcePath& path() const
        {
            return m_path;
        }

    private:
        ResourcePath m_path;
    };

    // This is base class for resource containers.
    // Every inheriting resource container must
    // override the protected get() member to
    // return the underlying resource.
    template <typename T>
    struct SpecificResource : AnyResource
    {
        using ResourceType = T;
        using ResourceLoader = resource_loaders::ResourceLoader<T>;
        using ResourceStorageType = typename ResourceLoader::ResourceStorageType;

        using AnyResource::AnyResource;

        [[nodiscard]] const T& operator*() const
        {
            return this->get();
        }

        [[nodiscard]] const T* operator->() const
        {
            return &(this->get());
        }

    protected:
        virtual const T& get() const = 0;
    };

    // This class owns a resource and loads it
    // on creation. If the stored resource type
    // differs from the actual resource type
    // it calls ResourceLoader::unpack() on get().
    template <typename T>
    struct EagerResource : SpecificResource<T>
    {
        using BaseType = SpecificResource<T>;
        using typename BaseType::ResourceLoader;
        using typename BaseType::ResourceStorageType;

        template <typename PathT>
        EagerResource(PathT&& rpath) :
            BaseType(std::forward<PathT>(rpath)),
            m_resource(ResourceLoader::load(path()))
        {
        }

    protected:
        [[nodiscard]] const T& get() const override
        {
            if constexpr (std::is_same_v<T, ResourceStorageType>)
            {
                return m_resource;
            }
            else
            {
                static_assert(
                    std::is_same_v<const T&, decltype(ResourceLoader::unpack(m_resource))>,
                    "Resource loader must return a reference to the "
                    "underlying object. It must not be a temporary."
                );

                return ResourceLoader::unpack(m_resource);
            }
        }

    private:
        ResourceStorageType m_resource;
    };

    // This class owns a resource and loads it
    // on first use. If the stored resource type
    // differs from the actual resource type
    // it calls ResourceLoader::unpack() on get().
    template <typename T>
    struct LazyResource : SpecificResource<T>
    {
        using BaseType = SpecificResource<T>;
        using typename BaseType::ResourceLoader;
        using typename BaseType::ResourceStorageType;

        template <typename PathT>
        LazyResource(PathT&& rpath) :
            BaseType(std::forward<PathT>(rpath)),
            m_flag{}
        {
        }

    protected:
        [[nodiscard]] const T& get() const override
        {
            std::call_once(m_flag, [&res = m_resource, this]() {
                res = ResourceLoader::load(path());
            });

            if constexpr (std::is_same_v<T, ResourceStorageType>)
            {
                return m_resource;
            }
            else
            {
                static_assert(
                    std::is_same_v<const T&, decltype(ResourceLoader::unpack(m_resource))>,
                    "Resource loader must return a reference to the "
                    "underlying object. It must not be a temporary."
                );

                return ResourceLoader::unpack(m_resource);
            }
        }

    private:
        // The members are mutable but they are only mutated
        // in thread safe manner.
        mutable ResourceStorageType m_resource;
        mutable std::once_flag m_flag;
    };

}

#endif // !IRE_RESOURCE_CONTAINER_H
