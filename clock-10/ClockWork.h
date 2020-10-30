#ifndef CLOCKWORK_H
#define CLOCKWORK_H

#include <algorithm>
#include <cstdint>
#include <functional>
#include <unordered_map>
#include <random>

class ClockWork {
public:
    using ID_Generator = std::mt19937_64;
    using CallBackID = ID_Generator::result_type;
    using CallBackFunction = std::function<void()>;
    using CallBackRegistry = std::unordered_map<CallBackID, CallBackFunction>;
private:
    CallBackRegistry subscribers;
    static ID_Generator rand_id;
    auto next_unused_id() {
        CallBackID result{};
        do result = rand_id();
        while (subscribers.count(result) > 0);
        return result;
    }
public:
    ClockWork()                           =default;  
    ClockWork(const ClockWork&)            =delete;
    ClockWork& operator=(const ClockWork&) =delete;
    ClockWork(ClockWork&&)                 =delete;
    ClockWork& operator=(ClockWork&&)      =delete;
    ~ClockWork()                          =default;
    CallBackID subscribe(CallBackFunction cf) {
        const auto id = next_unused_id();
        subscribers.emplace(id, cf);
        return id;
    }
    void unsubscribe(CallBackID id) {
        subscribers.erase(id);
    }
    void tick();
    void run(unsigned long long);
};

#endif
