#include "TimedCallbackScheduler.h"

namespace ire::core {

    TimedCallbackSchedulerCustomer::TimedCallbackSchedulerCustomer(TimedCallbackScheduler& scheduler) :
        m_scheduler(&scheduler)
    {
    }

    TimedCallbackSchedulerCustomer::~TimedCallbackSchedulerCustomer()
    {
        cancelAllCallbacks();
    }

    void TimedCallbackSchedulerCustomer::handleCallback(const util::OnlyCallableBy<TimedCallbackScheduler>& caller, TimedCallbackHandle handle, TimedCallback&& callback)
    {
        assert(&*caller == m_scheduler);

        stopTrackingCallback(handle);
        this->handleCallback(handle, std::move(callback));
    }

    TimedCallbackHandle TimedCallbackSchedulerCustomer::scheduleCallback(TimePoint time, TimedCallbackPayload&& payload)
    {
        auto handle = m_scheduler->scheduleCallback(*this, time, std::move(payload));
        m_scheduledCallbacks.emplace_back(handle);
        return handle;
    }

    void TimedCallbackSchedulerCustomer::cancelCallback(TimedCallbackHandle handle)
    {
        stopTrackingCallback(handle);
        m_scheduler->cancelCallback(*this, handle);
    }

    void TimedCallbackSchedulerCustomer::cancelAllCallbacks()
    {
        for (auto&& handle : m_scheduledCallbacks)
        {
            m_scheduler->cancelCallback(*this, handle);
        }

        m_scheduledCallbacks.clear();
    }

    void TimedCallbackSchedulerCustomer::stopTrackingCallback(TimedCallbackHandle handle)
    {
        auto it = std::find(std::begin(m_scheduledCallbacks), std::end(m_scheduledCallbacks), handle);

        assert(it != std::end(m_scheduledCallbacks));

        std::swap(*it, m_scheduledCallbacks.back());
        m_scheduledCallbacks.pop_back();
    }

    TimedCallbackHandle TimedCallbackScheduler::scheduleCallback(
        const util::OnlyCallableBy<TimedCallbackSchedulerCustomer>& caller,
        TimePoint time,
        TimedCallbackPayload&& payload
    )
    {
        return m_callbackQueue.emplace(*caller, time, std::move(payload));
    }

    void TimedCallbackScheduler::cancelCallback(
        const util::OnlyCallableBy<TimedCallbackSchedulerCustomer>& caller,
        TimedCallbackHandle handle
    )
    {
        m_callbackQueue.remove(handle);
    }

    void TimedCallbackScheduler::update(TimePoint now)
    {
        while(!m_callbackQueue.isEmpty())
        {
            auto& [handleRef, nextCallbackRef] = m_callbackQueue.top();
            if (nextCallbackRef.callbackTime() > now)
            {
                break;
            }

            TimedCallback nextCallback = std::move(nextCallbackRef);
            TimedCallbackHandle handle = handleRef;
            auto& creator = nextCallback.creator();
            m_callbackQueue.pop();

            creator.handleCallback(
                *this,
                handle,
                std::move(nextCallback)
            );
        }
    }

    TimedCallbackScheduler::~TimedCallbackScheduler()
    {
        // The callback scheduler must outlive all of its customers,
        // otherwise there will be dangling pointers to the scheduler.
        // It also doesn't make sense for the scheduler to be destroyed
        // before any customer is destroyed.
        // If scheduler didn't outlive some customers there will likely be
        // some scheduled callbacks left.
        assert(m_callbackQueue.isEmpty());
    }
}
