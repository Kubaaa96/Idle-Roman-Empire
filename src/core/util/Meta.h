#ifndef IRE_CORE_UTIL_META_H
#define IRE_CORE_UTIL_META_H

namespace ire::core::util {

    template <typename T>
    constexpr bool AlwaysFalseV = false;

    template <typename AllowedCallerT>
    struct OnlyCallableBy
    {
        friend AllowedCallerT;

        OnlyCallableBy(const OnlyCallableBy&) = delete;
        OnlyCallableBy(OnlyCallableBy&&) = delete;

        OnlyCallableBy& operator=(const OnlyCallableBy&) = delete;
        OnlyCallableBy& operator=(OnlyCallableBy&&) = delete;

        AllowedCallerT& operator*() const { return m_caller; }
        AllowedCallerT* operator->() const { return &m_caller; }

    private:
        OnlyCallableBy(AllowedCallerT& caller) : m_caller(caller) { }

        AllowedCallerT& m_caller;
    };

}

#endif // !IRE_CORE_UTIL_META_H
