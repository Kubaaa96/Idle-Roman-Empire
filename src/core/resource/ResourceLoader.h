#ifndef IRE_RESOURCE_LOADER_H
#define IRE_RESOURCE_LOADER_H

namespace ire::core::resource_loaders {

    // Users can define their own resource loaders by
    // specializing this template inside the
    // ire::core::resource_loaders namespace.
    // It is up to the user to ensure there are no
    // conflicting definitions for the same type
    // of a resource.
    //
    // A resource loader must provide two typedefs:
    //  - ResourceType = T
    //  - ResourceStorageType - the type used for storage
    //                          in the resource container.
    //
    // It must provide a static method
    // ResourceType load(const ResourcePath&) method that
    // (hopefully) loads a resource at the specified path.
    // It may throw if the resource couldn't be loaded.
    // 
    // If ResourceType != ResourceStorageType it must also provide
    // a static method
    // const ResourceType& unpack(const ResourceStorageType&)
    // that returns a reference to the underlying resource.
    // It must not be a temporary.
    template <typename T>
    struct ResourceLoader;

}

#endif // !IRE_RESOURCE_LOADER_H
