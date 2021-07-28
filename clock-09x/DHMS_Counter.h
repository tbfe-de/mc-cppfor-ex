#ifndef DHMS_COUNTER_H
#define DHMS_COUNTER_H

#include <cstdint>
#include <stdexcept>
#include <type_traits>

class DHMS_Counter {
public:
    using dhms_type = std::uint32_t;
    using value_type = std::uint8_t;
private:
    dhms_type dhms_{};
public:
    DHMS_Counter(value_type days = 0,
                 value_type hours = 0,
                 value_type minutes = 0,
                 value_type seconds = 0)
        : dhms_{static_cast<dhms_type>(((days*24 + hours)*60 + minutes)*60 + seconds)}
    {}
    value_type GetDays() const { return dhms_/(24*60*60) % 256; }
    value_type GetHours() const { return dhms_/(60*60) % 24; }
    value_type GetMinutes() const { return dhms_/60 % 60; }
    value_type GetSeconds() const { return dhms_ % 60; }
    void SetDays(value_type v) { dhms_ = dhms_ - 24*60*60*GetDays() + (v%256)*(24*60*60); }
    void SetHours(value_type v) { dhms_ = dhms_ - 60*60*GetHours() + (v%24)*(60*60) ; }
    void SetMinutes(value_type v) { dhms_ = dhms_ - 60*GetMinutes() + (v%60)*60; }
    void SetSeconds(value_type v) { dhms_ = dhms_ - GetSeconds() + (v%60); }

    bool IsLowBound() const { return (dhms_ == 0); }
    void DownCount() { if (!IsLowBound()) --dhms_; }
    bool IsHighBound() const { return (dhms_+1 == 256*24*60*60); }
    void UpCount() { if (!IsHighBound()) ++dhms_; }

};

#endif
