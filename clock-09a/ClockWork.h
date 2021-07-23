#ifndef CLOCKWORK_H
#define CLOCKWORK_H

#include <algorithm>
#include <cstdint>
#include <functional>
#include <map>
#include <random>

class ClockWork {
public:
    typedef std::mt19937_64 ID_Generator;
    typedef ID_Generator::result_type CallBackID;
    typedef std::function<void()> CallBackFunction;
    typedef std::map<CallBackID, CallBackFunction> CallBackRegistry;
private:
    CallBackRegistry subscribers_;
    static ID_Generator rand_id;
    CallBackID next_unused_id() {
        CallBackID result;
        do result = rand_id();
        while (subscribers_.count(result) > 0);
        return result;
    }
private:
    ClockWork(const ClockWork&);            // avoid compiler default
    ClockWork& operator=(const ClockWork&); // avoid compiler default
public:
    ClockWork() {}
    ~ClockWork() {}
    CallBackID subscribe(CallBackFunction cf) {
        const CallBackID id = next_unused_id();
        subscribers_.insert(CallBackRegistry::value_type(id, cf));
        return id;
    }
    void unsubscribe(CallBackID id) {
        subscribers_.erase(id);
    }
    void tick();
    void run(unsigned long long);
};

#endif
