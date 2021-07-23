#ifndef ICOUNTER_H
#define ICOUNTER_H

class ICounter {
public:
    virtual ~ICounter() {}
    
    virtual void Count() =0;
    virtual void Reset() =0;
};

#endif