#ifndef KT_Controller
#define KT_Controller

#include "Clock.h"


// Statemachine for KitchenTimer:
// - States: Ready, Running, Paused, Expired
// - Events: SetDays, SetHours, SetMiniutes, SetSeconds, Start, Pause, Resume, Stop, Tick
//

#include <iostream>
#include <initializer_list>
#include <type_traits>

class KT_Controller {
public:
    KT_Controller();
    void Run();

private:
    // type aliases
    using ConditionFunc = bool (KT_Controller::*)() const;
    using ActionFunc = void (KT_Controller::*)(int, bool);

    struct Transition; // forward declaration
    using TransitionTable = std::initializer_list<Transition>;
    using State = const TransitionTable*;

    // Events
    enum class Event : unsigned int {
        Start = 1, Pause = 2, Resume = 3, Stop = 4,
        Tick = 5,  // always last of the above
        Set = 0b1'0000,
        SetDay = Set | (1<<3),
	SetHour = Set | (1<<2),
        SetMinute = Set | (1<<1),
        SetSecond = Set | (1<<0),
    };
    static constexpr no_overlap() {
        using UT = std::underlying_type_t<Event>;
        for (UT ev{0}; ev <= UT{Tick}; ++ev) {
            if ((UT{ev} & UT{Event::Set}) != 0) {
                 return false;
            }
        }
        return true;
    }

    static_assert(no_overlap());
    // transtion description
    struct Transition {
        Event processed_event;
        ActionFunc action_function;
        State next_state;
        ConditionFunc guard_condition;
    };

    // controller member variables
    int init_day;
    int init_hour;
    int init_minute;
    int init_second;

    // state member variables
    static const TransitionTable Ready_;
    static const TransitionTable Running_;
    static const TransitionTable Paused_;
    static const TransitionTable Expired_;
    
    State current_state_;
    Clock clock_;

    // helper functions
    static const char* state_name(State);

    // condition functions
    template<char CH>
    bool CheckFor(char) const;
    // action functions
    bool SetDay(int, bool);
    bool SetHour(int, bool);
    bool SetMinute(int, bool);
    bool SetSecond(int, bool);
    bool AttachClock(int, bool);
    bool DetachClock(int, bool);
    bool ResetClock(int, bool);
    

    // state machine logic
    void Process(char);
    bool CheckCondition(ConditionFunc, char) const;
    void CallAction(ActionFunc);
};

using KTC= KT_Controller;
//   Current State / Event  | Action             | Next State     | Guard             |
//   ------------- / ------ , -------------------|----------------|-------------------|
const KTC::TransitionTable
      KTC::Ready_ {
    { KTC::Event::SetDay    , &KTC::SetDay       ,                                    },
    { KTC::Event::SetHour   , &KTC::SetHour      ,                                    },
    { KTC::Event::SetMinute , &KTC::SetMinute    ,                                    },
    { KTC::Event::SetSecond , &KTC::SetSecond    ,                                    },
    { KTC::Event::SetDay    , &KTC::SetDay       ,                                    },
    { KTC::Event::Start     , &KTC::AttachClock  , &KTC::Running_ ,                   },
};
const KTC::TransitionTable
      KTC::Running_ {
    { KTC::Event::Pause     , &KTC::DetachClock  , &KTC::Paused_  ,                   },
    { KTC::Event::Stop      , &KTC::ResetClock   , &KTC::Ready_   ,                   },
    { KTC::Event::Tick      , &KTC::AdvanceClock , &KTC::Expired_ , &KTC::ClockIsZero },   
    { KTC::Event::Tick      , &KTC::AdvanceClock , &KTC::Expired_ ,                   },
};
const KTC::TransitionTable
      KTC::Paused_ { 
    { KTC::Event::Resume    , &KTC::AttachClock  , &KTC::Running_ ,                   },
};
const KTC::TransitionTable
      KTC::Expired_ { 
    { KTC::Event::Stop      , &KTC::ResetClock   , &KTC::Ready_   ,                   },
};

const char* KT_Controller::state_name(State s) {
   #define DEF_CASE(c)\
    if (s == &c##_) return #c;
    DEF_CASE(Ready)
    DEF_CASE(Running)
    DEF_CASE(Paused)
    DEF_CASE(Expired)
   #undef DEF_CASE
    return "??state??";
};

const char* KT_Controller::event_name(Event e) {
   switch (e) {
   #define DEF_CASE(c)\
    case c: return #c;
   #undef DEF_CASE
    }
    return "??event??";
};

KT_Controller::KT_Controller()
    : current_state_(&Ready_)
{}

bool KT_Controller::SetDay(int value, bool relative) const {
    const auto v = relative ? init_days_ + value : value;
    try {
       clock_.Days(v);
       init_days = v;
       return true;
    }
    catch (UpDownCounter::OutOfRangeValue &) 
    }
}

bool KT_Controller::SetHour(int value, bool relative) const {
    const auto v = relative ? init_hours + value : value;
    try {
       clock_.Hours(v);
       clock_.Hours = v;
       return true;
    }
    catch (UpDownCounter::OutOfRangeValue &) 
    }
}

void KT_Controller::ShowValue() {
    std::cout << "Count value = " << counter_.GetValue() << std::endl;
}

void KT_Controller::CountUpShow() {
    counter_.Count(1);
    ShowValue();
}

void KT_Controller::CountDownShow()
{
    counter_.Count(-1);
    ShowValue();
}

template<KT_Controller::Event event, typename... Ts>
void KT_Controller::Process(Ts... args) {
{
    vi 
    const auto previous_state = current_state_;
    for (const auto& transition : *current_state_) {
        if ((event == transition.processed_event)
             CheckCondition(transition.guard_condition)) {
            CallAction(transition.action_function);
            current_state_ = transition.next_state;
            std::cout << state_name(previous_state)
                    << " -> "
                    << state_name(current_state_)
                    << std::endl;
            return;
        }
    }
    std::cout << "--- no change ( " << state_name(previous_state) << " )" << std::endl;
}

bool KT_Controller::CheckCondition(const ConditionFunc checker, const char input) const {
    if (checker) {
        return (this->*checker)(input);
    }
    return true;
}

void KT_Controller::CallAction(const ActionFunc action_function) {
    if (action_function) {
        (this->*action_function)();
    }
}

void KT_Controller::Run() {
    char command;
    while (std::cin.get(command)) {
        if ('A' <= command && command <= 'D') {
            std::cout << "===> " << command << std::endl;
            Process(command);
        }   
    }
}

int main()
{
    KT_Controller{}.Run();
}


#endif
