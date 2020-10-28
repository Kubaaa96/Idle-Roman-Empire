#ifndef IRE_RESOURCE_MANAGER_H
#define IRE_RESOURCE_MANAGER_H

#include "detail/ResourceContainer.h"

#include "ResourcePath.h"
#include "Resource.h"

#include <set>
#include <map>
#include <typeindex>
#include <filesystem>
#include <mutex>
#include <memory>
#include <type_traits>

namespace ire::core {

    namespace detail {

        // The resource manager utilizes type erasure for the
        // polymorphic calls to get() because the resource
        // type is only known in the ResourceManager::get<T>.
        // This is safe because SpecificResourceManagers are
        // indexed by matching std::type_index.
        struct AnyResourceManager
        {
            [[nodiscard]] virtual const void* get(const ResourcePath&) = 0;
        };

        template <typename T>
        struct SpecificResourceManager : AnyResourceManager
        {
            // For now we assume all resource types to be lazy.
            // In the future we may make it dependent on some
            // external, possibly per type, value.
            static constexpr bool isLazy = true;

            using ResourceType = T;
            using ResourceContainerType =
                std::conditional_t<
                    isLazy,
                    detail::LazyResource<T>,
                    detail::EagerResource<T>
                >;

            [[nodiscard]] const void* get(const ResourcePath& path) override
            {
                std::unique_lock lock(m_mutex);

                auto it = m_resources.find(path);
                if (it == m_resources.end())
                {
                    std::unique_ptr<SpecificResource<T>> newResource =
                        std::make_unique<ResourceContainerType>(path);

                    it = m_resources.emplace_hint(it, std::move(newResource));
                }

                // This won't load the resource because we're just
                // returning the pointer to the resource container.
                // The get() is on the unique_ptr.
                return it->get();
            }

        private:
            struct Comparator
            {
                using is_transparent = std::true_type;

                using ValueType = std::unique_ptr<SpecificResource<T>>;

                [[nodiscard]] bool operator()(const ValueType& lhs, const ValueType& rhs) const
                {
                    return lhs->path() < rhs->path();
                }

                [[nodiscard]] bool operator()(const ValueType& lhs, const ResourcePath& rhs) const
                {
                    return lhs->path() < rhs;
                }

                [[nodiscard]] bool operator()(const ResourcePath& lhs, const ValueType& rhs) const
                {
                    return lhs < rhs->path();
                }
            };

            // Since the resources have immutable paths
            // and are themselves not movable nor copyable
            // we can safely store the pointer to their
            // internal path member.
            // Also we make sure that the resource containers
            // are never moved in memory so that the created
            // pointers are valid for the whole lifetime
            // of this class.
            std::set<std::unique_ptr<SpecificResource<T>>, Comparator> m_resources;
            mutable std::mutex m_mutex;
        };

    }

    // This class is a resource manager singleton.
    // It outlives all local (non-static) references
    // to the resources acquired from it.
    struct ResourceManager
    {
        [[nodiscard]] static ResourceManager& instance()
        {
            static ResourceManager s_instance;
            return s_instance;
        }

        template <typename T, typename PathT>
        [[nodiscard]] ResourcePtr<T> get(PathT&& patharg)
        {
            const ResourcePath path(std::forward<PathT>(patharg));

            std::unique_lock lock(m_mutex);

            auto idx = std::type_index(typeid(T));
            auto it = m_specificResourceManagers.find(idx);
            if (it == m_specificResourceManagers.end())
            {
                it = m_specificResourceManagers.emplace_hint(
                    it,
                    idx, 
                    std::make_unique<detail::SpecificResourceManager<T>>()
                );
            }

            auto srm = it->second.get();
            lock.unlock();

            auto resource = static_cast<const detail::SpecificResource<T>*>(srm->get(path));
            return ResourcePtr<T>(resource);
        }

    private:
        std::map<std::type_index, std::unique_ptr<detail::AnyResourceManager>> m_specificResourceManagers;
        mutable std::mutex m_mutex;

        ResourceManager() = default;
    };

}

#endif // !IRE_RESOURCE_MANAGER_H
