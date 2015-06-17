#ifndef _MZ_NET_EPOLLSTRATEGY_HPP_
#define _MZ_NET_EPOLLSTRATEGY_HPP_

#include "Metazion/Net/NetInclude.hpp"

#if defined(NETWORK_USE_EPOLL_MODEL)

DECL_NAMESPACE_MZ_NET_BEGIN

class EpollStrategy {
    MZ_DISALLOW_COPY_AND_ASSIGN(EpollStrategy)

public:
    EpollStrategy() {}

    virtual ~EpollStrategy() {}

public:
    virtual void Reset() = 0;

    virtual void Prepare() = 0;

    virtual void Start() = 0;

    virtual bool IsBusy() const = 0;

    virtual void PostInput() = 0;

    virtual void PostOutput() = 0;

    virtual void EnableOutput() = 0;
};

DECL_NAMESPACE_MZ_NET_END

#endif

#endif // _MZ_NET_EPOLLSTRATEGY_HPP_
