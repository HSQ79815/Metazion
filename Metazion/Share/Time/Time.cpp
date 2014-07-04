#include "Metazion/Share/Time/Time.hpp"

#include <chrono>

using namespace std::chrono;

DECL_NAMESPACE_MZ_SHARE_BEGIN

int64_t GetNowMillisecond() {
    const auto timePoint = system_clock::now();
    const auto timeDuration = timePoint.time_since_epoch();
    return duration_cast<milliseconds>(timeDuration).count();
}

int64_t GetNowMicrosecond() {
    const auto timePoint = system_clock::now();
    const auto timeDuration = timePoint.time_since_epoch();
    return duration_cast<microseconds>(timeDuration).count();
}

DECL_NAMESPACE_MZ_SHARE_END
