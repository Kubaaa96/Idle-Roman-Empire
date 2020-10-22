#include <catch2/catch.hpp>

#include "core/time/TimedCallbackScheduler.h"

#include <vector>
#include <cstdint>

TEST_CASE("General testing of TimedCallbackScheduler", "[timed_callback_scheduler]")
{
    using namespace ire::core;

    struct MockupCustomer : TimedCallbackSchedulerCustomer
    {
        MockupCustomer(TimedCallbackScheduler& scheduler) :
            TimedCallbackSchedulerCustomer(scheduler)
        {
        }

        void handleCallback(TimedCallbackHandle handle, TimedCallback&& callback) override
        {
            const auto i = callback.payload().data;

            if (i >= 4320 && i < 4330)
            {
                scheduleCallback(callback.callbackTime() + TimeDuration::seconds(1), { i + 1 });
            }

            handledCallbacks.emplace_back(handle, std::move(callback));
        }

        void scheduleInitialCallback(TimePoint now, std::uint64_t payload)
        {
            scheduleCallback(now + TimeDuration::seconds(1), { payload });
        }

        std::vector<std::pair<TimedCallbackHandle, TimedCallback>> handledCallbacks;
    };

    TimedCallbackScheduler scheduler;

    MockupCustomer customer(scheduler);

    TimePoint startTime = TimePoint::now();

    customer.scheduleInitialCallback(startTime, 123);

    REQUIRE(customer.handledCallbacks.empty());

    scheduler.update(startTime);

    REQUIRE(customer.handledCallbacks.empty());

    scheduler.update(startTime + TimeDuration::milliseconds(2));

    REQUIRE(customer.handledCallbacks.empty());

    scheduler.update(startTime + TimeDuration::seconds(2));

    REQUIRE(customer.handledCallbacks.size() == 1);
    REQUIRE(customer.handledCallbacks[0].second.payload().data == 123);
    return;

    scheduler.update(startTime + TimeDuration::seconds(4));

    REQUIRE(customer.handledCallbacks.size() == 1);

    customer.scheduleInitialCallback(startTime + TimeDuration::seconds(20), 4320);

    scheduler.update(startTime);

    REQUIRE(customer.handledCallbacks.size() == 1);

    scheduler.update(startTime + TimeDuration::seconds(19));

    REQUIRE(customer.handledCallbacks.size() == 1);

    scheduler.update(startTime + TimeDuration::seconds(20));

    REQUIRE(customer.handledCallbacks.size() == 2);
    REQUIRE(customer.handledCallbacks[1].second.payload().data == 4320);

    scheduler.update(startTime + TimeDuration::seconds(27));

    REQUIRE(customer.handledCallbacks.size() == 9);
    REQUIRE(customer.handledCallbacks[2].second.payload().data == 4321);
    REQUIRE(customer.handledCallbacks[3].second.payload().data == 4322);
    REQUIRE(customer.handledCallbacks[4].second.payload().data == 4323);
    REQUIRE(customer.handledCallbacks[5].second.payload().data == 4324);
    REQUIRE(customer.handledCallbacks[6].second.payload().data == 4325);
    REQUIRE(customer.handledCallbacks[7].second.payload().data == 4326);
    REQUIRE(customer.handledCallbacks[8].second.payload().data == 4327);

    scheduler.update(startTime + TimeDuration::seconds(100));
    REQUIRE(customer.handledCallbacks.size() == 11);
    REQUIRE(customer.handledCallbacks[9].second.payload().data == 4328);
    REQUIRE(customer.handledCallbacks[10].second.payload().data == 4329);
}