#ifndef _MZ_NET_EPOLLSTRATEGY_HPP_
#define _MZ_NET_EPOLLSTRATEGY_HPP_

#include "Metazion/Net/NetInclude.hpp"

#if defined(MZ_PLATFORM_LINUX)

DECL_NAMESPACE_MZ_NET_BEGIN

class EpollStrategy {
    DISALLOW_COPY_AND_ASSIGN(EpollStrategy)

public:
    EpollStrategy() {}

    virtual ~EpollStrategy() {}

public:
    virtual void Reset() = 0;

    virtual void OnStarted() = 0;

    virtual bool IsBusy() const = 0;

    virtual void Input() = 0;

    virtual void Output() = 0;

    virtual void ExecuteInput() = 0;

    virtual void ExecuteOutput() = 0;

    virtual void EnableOutput() = 0;
};

DECL_NAMESPACE_MZ_NET_END

#endif // MZ_PLATFORM_LINUX

#endif // _MZ_NET_EPOLLSTRATEGY_HPP_
