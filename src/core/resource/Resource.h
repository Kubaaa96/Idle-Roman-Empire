#ifndef IRE_RESOURCE_H
#define IRE_RESOURCE_H

#include "detail/ResourceContainer.h"

#include "ResourcePath.h"

#include <filesystem>
#include <memory>
#include <mutex>

namespace ire::core {

    struct ResourceManager;

    // This is a non-owning pointer to a resource container
    // that provides a resource of type T.
    // It can only be initialized with a valid resource
    // pointer from ResourceManager, otherwise
    // it can only be reset to nullptr.
    // It defers the dereference to the underlying
    // resource container.
    template <typename T>
    struct ResourcePtr
    {
        friend struct ResourceManager;

        ResourcePtr() :
            m_resource(nullptr)
        {
        }

        ResourcePtr(std::nullptr_t) :
            m_resource(nullptr)
        {
        }

        ResourcePtr(const ResourcePtr&) = default;
        ResourcePtr(ResourcePtr&&) = default;

        ResourcePtr& operator=(const ResourcePtr&) = default;
        ResourcePtr& operator=(ResourcePtr&&) = default;

        ResourcePtr& operator=(std::nullptr_t)
        {
            m_resource = nullptr;
        }

        [[nodiscard]] const T& operator*() const
        {
            return **m_resource;
        }

        [[nodiscard]] const T* operator->() const
        {
            return &**m_resource;
        }

        [[nodiscard]] operator bool() const
        {
            return m_resource != nullptr;
        }

    private:
        const detail::SpecificResource<T>* m_resource;

        ResourcePtr(const detail::SpecificResource<T>* resource) :
            m_resource(resource)
        {
        }
    };

}

#endif // !IRE_RESOURCE_H
