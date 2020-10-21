#include <catch2/catch.hpp>

#include "core/time/Time.h"

TEST_CASE("TimePoint tests", "[time]")
{
    using namespace ire::core;

    TimePoint tp{};

    REQUIRE(tp == tp);
    REQUIRE(tp <= tp);
    REQUIRE(tp >= tp);
    REQUIRE(!(tp != tp));
    REQUIRE(!(tp < tp));
    REQUIRE(!(tp > tp));

    // This relies on system clock returning a value greater than 0,
    // but it should be a reasonable assumption.
    tp = TimePoint::now();

    REQUIRE(tp > TimePoint{});
}

TEST_CASE("Duration tests", "[time]")
{
    using namespace ire::core;

    TimeDuration d{};

    REQUIRE(d == d);
    REQUIRE(d <= d);
    REQUIRE(d >= d);
    REQUIRE(!(d != d));
    REQUIRE(!(d < d));
    REQUIRE(!(d > d));
    REQUIRE(d.nanoseconds() == 0);

    d += TimeDuration::seconds(2);

    REQUIRE(d.nanoseconds() == 2'000'000'000);

    d += TimeDuration::milliseconds(3);

    REQUIRE(d.nanoseconds() == 2'003'000'000);

    d += TimeDuration::microseconds(4);

    REQUIRE(d.nanoseconds() == 2'003'004'000);

    d += TimeDuration::nanoseconds(5);

    REQUIRE(d.nanoseconds() == 2'003'004'005);

    d = -d;

    REQUIRE(d.nanoseconds() == -2'003'004'005);
    REQUIRE(d.seconds<double>() == Approx(-2.003004005));
    REQUIRE(d.milliseconds<double>() == Approx(-2003.004005));
    REQUIRE(d.microseconds<double>() == Approx(-2003004.005));
    REQUIRE(d.nanoseconds<double>() == Approx(-2003004005));

    d *= -2;

    REQUIRE(d.nanoseconds() == 4'006'008'010);
}

TEST_CASE("TimePoint and TimeDuration interaction tests", "[test]")
{
    using namespace ire::core;

    TimePoint tp = TimePoint::now();
    TimeDuration d = TimeDuration::seconds(2);

    REQUIRE(tp + d > tp);
    REQUIRE(tp - d < tp);
    REQUIRE(tp + d * 2 > tp + d);
    REQUIRE(tp + d / 2 < tp + d);

    auto oldTp = tp;
    tp += d;

    REQUIRE(tp == oldTp + d);
    REQUIRE(tp - oldTp == d);
    REQUIRE(oldTp - tp == -d);
}