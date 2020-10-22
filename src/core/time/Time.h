#ifndef IRE_CORE_TIME_H
#define IRE_CORE_TIME_H

#include "core/util/Meta.h"

#include <cstdint>
#include <chrono>
#include <string>
#include <iomanip>
#include <ctime>

namespace ire::core {

    struct TimePoint;

    struct TimeDuration
    {
        friend TimePoint;

        [[nodiscard]] static TimeDuration nanoseconds(std::int64_t count)
        {
            return TimeDuration(count);
        }

        [[nodiscard]] static TimeDuration microseconds(std::int64_t count)
        {
            return TimeDuration(count * 1'000);
        }

        [[nodiscard]] static TimeDuration milliseconds(std::int64_t count)
        {
            return TimeDuration(count * 1'000'000);
        }

        [[nodiscard]] static TimeDuration seconds(std::int64_t count)
        {
            return TimeDuration(count * 1'000'000'000);
        }

        TimeDuration() :
            TimeDuration(0)
        {
        }

        TimeDuration(const TimeDuration&) = default;
        TimeDuration(TimeDuration&&) = default;
        TimeDuration& operator=(const TimeDuration&) = default;
        TimeDuration& operator=(TimeDuration&&) = default;

        template <typename T = std::int64_t>
        [[nodiscard]] T nanoseconds() const
        {
            return scaled<T, 1>();
        }

        template <typename T = std::int64_t>
        [[nodiscard]] T microseconds() const
        {
            return scaled<T, 1'000>();
        }

        template <typename T = std::int64_t>
        [[nodiscard]] T milliseconds() const
        {
            return scaled<T, 1'000'000>();
        }

        template <typename T = std::int64_t>
        [[nodiscard]] T seconds() const
        {
            return scaled<T, 1'000'000'000>();
        }

        [[nodiscard]] friend bool operator==(TimeDuration lhs, TimeDuration rhs) noexcept
        {
            return lhs.m_nanoseconds == rhs.m_nanoseconds;
        }

        [[nodiscard]] friend bool operator!=(TimeDuration lhs, TimeDuration rhs) noexcept
        {
            return lhs.m_nanoseconds != rhs.m_nanoseconds;
        }

        [[nodiscard]] friend bool operator<(TimeDuration lhs, TimeDuration rhs) noexcept
        {
            return lhs.m_nanoseconds < rhs.m_nanoseconds;
        }

        [[nodiscard]] friend bool operator<=(TimeDuration lhs, TimeDuration rhs) noexcept
        {
            return lhs.m_nanoseconds <= rhs.m_nanoseconds;
        }

        [[nodiscard]] friend bool operator>(TimeDuration lhs, TimeDuration rhs) noexcept
        {
            return lhs.m_nanoseconds > rhs.m_nanoseconds;
        }

        [[nodiscard]] friend bool operator>=(TimeDuration lhs, TimeDuration rhs) noexcept
        {
            return lhs.m_nanoseconds >= rhs.m_nanoseconds;
        }

        [[nodiscard]] friend TimeDuration operator-(TimeDuration arg)
        {
            return TimeDuration(-arg.m_nanoseconds);
        }

        [[nodiscard]] friend TimeDuration operator+(TimeDuration lhs, TimeDuration rhs)
        {
            return TimeDuration(lhs.m_nanoseconds + rhs.m_nanoseconds);
        }

        [[nodiscard]] friend TimeDuration operator-(TimeDuration lhs, TimeDuration rhs)
        {
            return TimeDuration(lhs.m_nanoseconds - rhs.m_nanoseconds);
        }

        [[nodiscard]] friend TimeDuration operator%(TimeDuration lhs, TimeDuration rhs)
        {
            return TimeDuration(lhs.m_nanoseconds % rhs.m_nanoseconds);
        }

        [[nodiscard]] friend TimeDuration operator*(TimeDuration lhs, std::int64_t rhs)
        {
            return TimeDuration(lhs.m_nanoseconds * rhs);
        }

        [[nodiscard]] friend TimeDuration operator/(TimeDuration lhs, std::int64_t rhs)
        {
            return TimeDuration(lhs.m_nanoseconds / rhs);
        }

        TimeDuration& operator+=(TimeDuration rhs)
        {
            m_nanoseconds += rhs.m_nanoseconds;
            return *this;
        }

        TimeDuration& operator-=(TimeDuration rhs)
        {
            m_nanoseconds -= rhs.m_nanoseconds;
            return *this;
        }

        TimeDuration& operator%=(TimeDuration rhs)
        {
            m_nanoseconds %= rhs.m_nanoseconds;
            return *this;
        }

        TimeDuration& operator*=(std::int64_t rhs)
        {
            m_nanoseconds *= rhs;
            return *this;
        }

        TimeDuration& operator/=(std::int64_t rhs)
        {
            m_nanoseconds /= rhs;
            return *this;
        } 
        
        friend TimePoint operator+(TimePoint lhs, TimeDuration rhs);
        friend TimePoint operator-(TimePoint lhs, TimeDuration rhs);
        friend TimeDuration operator-(TimePoint lhs, TimePoint rhs);

    private:
        std::int64_t m_nanoseconds;

        TimeDuration(std::int64_t nanoseconds) :
            m_nanoseconds(nanoseconds)
        {
        }

        template <typename T, std::int64_t ScaleV>
        [[nodiscard]] T scaled() const
        {
            if constexpr (std::is_same_v<T, double>)
            {
                return m_nanoseconds * (1.0 / static_cast<double>(ScaleV));
            }
            else if constexpr (std::is_same_v<T, std::int64_t>)
            {
                return m_nanoseconds / ScaleV;
            }
            else
            {
                static_assert(util::AlwaysFalseV<T>, "Only double and int64_t are supported.");
            }
        }
    };

    struct TimePoint
    {
        using ClockType = std::chrono::system_clock;

        static constexpr const char* defaultTimeFormat = "%F %T %Z";

        [[nodiscard]] static TimePoint now()
        {
            auto tse = ClockType::now().time_since_epoch();
            auto tse_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(tse);
            return TimePoint(tse_ns.count());
        }

        TimePoint() :
            TimePoint(0)
        {
        }

        TimePoint(const TimePoint&) = default;
        TimePoint(TimePoint&&) = default;
        TimePoint& operator=(const TimePoint&) = default;
        TimePoint& operator=(TimePoint&&) = default;

        [[nodiscard]] friend bool operator==(TimePoint lhs, TimePoint rhs) noexcept
        {
            return lhs.m_nanoseconds == rhs.m_nanoseconds;
        }

        [[nodiscard]] friend bool operator!=(TimePoint lhs, TimePoint rhs) noexcept
        {
            return lhs.m_nanoseconds != rhs.m_nanoseconds;
        }

        [[nodiscard]] friend bool operator<(TimePoint lhs, TimePoint rhs) noexcept
        {
            return lhs.m_nanoseconds < rhs.m_nanoseconds;
        }

        [[nodiscard]] friend bool operator<=(TimePoint lhs, TimePoint rhs) noexcept
        {
            return lhs.m_nanoseconds <= rhs.m_nanoseconds;
        }

        [[nodiscard]] friend bool operator>(TimePoint lhs, TimePoint rhs) noexcept
        {
            return lhs.m_nanoseconds > rhs.m_nanoseconds;
        }

        [[nodiscard]] friend bool operator>=(TimePoint lhs, TimePoint rhs) noexcept
        {
            return lhs.m_nanoseconds >= rhs.m_nanoseconds;
        }

        [[nodiscard]] friend TimePoint operator+(TimePoint lhs, TimeDuration rhs)
        {
            return TimePoint(lhs.m_nanoseconds + rhs.m_nanoseconds);
        }

        [[nodiscard]] friend TimePoint operator-(TimePoint lhs, TimeDuration rhs)
        {
            return TimePoint(lhs.m_nanoseconds - rhs.m_nanoseconds);
        }

        [[nodiscard]] friend TimeDuration operator-(TimePoint lhs, TimePoint rhs)
        {
            return TimeDuration(lhs.m_nanoseconds - rhs.m_nanoseconds);
        }

        TimePoint& operator+=(TimeDuration rhs)
        {
            m_nanoseconds += rhs.m_nanoseconds;
            return *this;
        }

        TimePoint& operator-=(TimeDuration rhs)
        {
            m_nanoseconds -= rhs.m_nanoseconds;
            return *this;
        }

        // The `format` must be a std::put_time compatibile format.
        // Note: This function is not thread-safe.
        [[nodiscard]] std::string toString(const char* format) const
        {
            char buffer[128];

            const auto tp = 
                ClockType::time_point() 
                + std::chrono::duration_cast<ClockType::duration>(
                    std::chrono::nanoseconds(m_nanoseconds)
                );

            const auto t = ClockType::to_time_t(tp);
            const auto tm = *std::localtime(&t);

            const auto numWritten = std::strftime(buffer, sizeof(buffer), format, &tm);
            buffer[numWritten] = '\0';

            return std::string(buffer);
        }

        // Note: This function is not thread-safe.
        [[nodiscard]] std::string toString() const
        {
            return toString(defaultTimeFormat);
        }

    private:
        std::int64_t m_nanoseconds;

        TimePoint(std::int64_t nanoseconds) :
            m_nanoseconds(nanoseconds)
        {
        }
    };

}

#endif // !IRE_CORE_TIME_H
