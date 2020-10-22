#ifndef IRE_CORE_TIMED_CALLBACK_SCHEDULER_H
#define IRE_CORE_TIMED_CALLBACK_SCHEDULER_H

#include "Time.h"

#include "core/util/Meta.h"
#include "core/util/UpdatablePriorityQueue.h"

#include <cstdint>
#include <vector>
#include <utility>
#include <functional>

namespace ire::core {

    struct TimedCallbackScheduler;
    struct TimedCallbackSchedulerCustomer;

    struct TimedCallbackPayload
    {
        std::uint64_t data;
    };

    struct TimedCallback
    {
        TimedCallback(
            TimedCallbackSchedulerCustomer& creator,
            TimePoint callbackTime,
            TimedCallbackPayload&& payload
        ) :
            m_creator(&creator),
            m_callbackTime(callbackTime),
            m_payload(std::move(payload))
        {
        }

        [[nodiscard]] friend bool operator<(const TimedCallback& lhs, const TimedCallback& rhs) noexcept
        {
            return lhs.m_callbackTime < rhs.m_callbackTime;
        }

        [[nodiscard]] const TimedCallbackSchedulerCustomer& creator() const
        {
            return *m_creator;
        }

        [[nodiscard]] TimedCallbackSchedulerCustomer& creator()
        {
            return *m_creator;
        }

        [[nodiscard]] TimePoint callbackTime() const
        {
            return m_callbackTime;
        }

        [[nodiscard]] TimedCallbackPayload& payload()
        {
            return m_payload;
        }

        [[nodiscard]] const TimedCallbackPayload& payload() const
        {
            return m_payload;
        }

    private:
        TimedCallbackSchedulerCustomer* m_creator;
        TimePoint m_callbackTime;
        TimedCallbackPayload m_payload;
    };

    using TimedCallbackSchedulerQueueType = util::UpdatablePriorityQueue<TimedCallback, std::less<>>;
    using TimedCallbackHandle = typename TimedCallbackSchedulerQueueType::ItemHandle;

    struct TimedCallbackSchedulerCustomer
    {
        friend struct TimedCallbackScheduler;

        TimedCallbackSchedulerCustomer(TimedCallbackScheduler& scheduler);

        TimedCallbackSchedulerCustomer(const TimedCallbackSchedulerCustomer&) = delete;
        TimedCallbackSchedulerCustomer(TimedCallbackSchedulerCustomer&&) = delete;

        TimedCallbackSchedulerCustomer& operator=(const TimedCallbackSchedulerCustomer&) = delete;
        TimedCallbackSchedulerCustomer& operator=(TimedCallbackSchedulerCustomer&&) = delete;

        ~TimedCallbackSchedulerCustomer();

    protected:

        virtual void handleCallback(TimedCallbackHandle handle, TimedCallback&& callback) = 0;

        TimedCallbackHandle scheduleCallback(TimePoint time, TimedCallbackPayload&& payload);

        void cancelCallback(TimedCallbackHandle handle);

    private:

        TimedCallbackScheduler* m_scheduler;
        std::vector<TimedCallbackHandle> m_scheduledCallbacks;

        void handleCallback(const util::OnlyCallableBy<TimedCallbackScheduler>& caller, TimedCallbackHandle handle, TimedCallback&& callback);

        void cancelAllCallbacks();

        void stopTrackingCallback(TimedCallbackHandle handle);
    };
    
    struct TimedCallbackScheduler final
    {
        friend struct TimedCallbackSchedulerCustomer;

        ~TimedCallbackScheduler();

        void update(TimePoint now);

    private:

        TimedCallbackHandle scheduleCallback(
            const util::OnlyCallableBy<TimedCallbackSchedulerCustomer>& caller,
            TimePoint time,
            TimedCallbackPayload&& payload
        );

        void cancelCallback(
            const util::OnlyCallableBy<TimedCallbackSchedulerCustomer>& caller,
            TimedCallbackHandle handle
        );

        TimedCallbackSchedulerQueueType m_callbackQueue;
    };

}

#endif // !IRE_CORE_TIMED_CALLBACK_SCHEDULER_H
