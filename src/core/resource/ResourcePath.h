#ifndef IRE_RESOURCE_PATH_H
#define IRE_RESOURCE_PATH_H

#include <filesystem>
#include <exception>

namespace ire::core {

    struct PathEscapesWorkingDirectoryException : std::runtime_error
    {
        using BaseType = std::runtime_error;

        PathEscapesWorkingDirectoryException(const std::filesystem::path& path) :
            BaseType("Path \"" + path.string() + "\" escapes from the working directory.")
        {
        }
    };

    // A resource path is always stored in normal form.
    // Paths that escape the working directory are
    // not allowed and an exception will be raised
    // when such a path is created.
    struct ResourcePath
    {
        ResourcePath() = default;

        template <typename SourceT>
        explicit ResourcePath(SourceT&& path) :
            m_path(std::filesystem::path(std::forward<SourceT>(path)).lexically_normal())
        {
            if (escapesWorkingDirectory())
            {
                throw PathEscapesWorkingDirectoryException(m_path);
            }
        }

        ResourcePath(const ResourcePath&) = default;
        ResourcePath(ResourcePath&&) = default;

        ResourcePath& operator=(const ResourcePath&) = default;
        ResourcePath& operator=(ResourcePath&&) = default;

        [[nodiscard]] operator const std::filesystem::path& () const
        {
            return m_path;
        }

        [[nodiscard]] const std::filesystem::path& fspath() const
        {
            return m_path;
        }

        [[nodiscard]] friend bool operator==(const ResourcePath& lhs, const ResourcePath& rhs)
        {
            return lhs.m_path == rhs.m_path;
        }

        [[nodiscard]] friend bool operator!=(const ResourcePath& lhs, const ResourcePath& rhs)
        {
            return lhs.m_path != rhs.m_path;
        }

        [[nodiscard]] friend bool operator<(const ResourcePath& lhs, const ResourcePath& rhs)
        {
            return lhs.m_path < rhs.m_path;
        }

        [[nodiscard]] friend bool operator<=(const ResourcePath& lhs, const ResourcePath& rhs)
        {
            return lhs.m_path <= rhs.m_path;
        }

        [[nodiscard]] friend bool operator>(const ResourcePath& lhs, const ResourcePath& rhs)
        {
            return lhs.m_path > rhs.m_path;
        }

        [[nodiscard]] friend bool operator>=(const ResourcePath& lhs, const ResourcePath& rhs)
        {
            return lhs.m_path >= rhs.m_path;
        }

        [[nodiscard]] auto string() const
        {
            return m_path.string();
        }

    private:
        std::filesystem::path m_path;

        [[nodiscard]] bool escapesWorkingDirectory() const
        {
            return !m_path.is_relative() || m_path.string().find("..") == 0;
        }
    };
}

#endif // !IRE_RESOURCE_PATH_H
