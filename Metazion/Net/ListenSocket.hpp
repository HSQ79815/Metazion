#ifndef _MZ_NET_LISTENSOCKET_HPP_
#define _MZ_NET_LISTENSOCKET_HPP_

#include "Metazion/Net/NetInclude.hpp"

#include "Metazion/Net/Socket.hpp"

DECL_NAMESPACE_MZ_NET_BEGIN

class ListenSocket : public Socket {
    MZ_DISALLOW_COPY_AND_ASSIGN(ListenSocket)

    friend class ListenStrategy;

public:
    ListenSocket();

    virtual ~ListenSocket();

public:
    void Reset() override;

    void Prepare() override;

    IoStrategy& GetIoStrategy() override final;

    bool IsAlive() const override final;

    void OnAttached() override final;

    void OnDetached() override final;

    void OnStart() override final;

    void OnStop() override final;

    void OnError(int error) override final;

    void SetLocalHost(const Host& host);

    bool Listen(int backlog);

protected:
    virtual void OnWatched();

    virtual void OnUnwatched();

    virtual bool OnAccepted(const SockId_t& sockId);

protected:
    ListenStrategy m_listenStrategy;
    Host m_localHost;

#if defined(MZ_ENABLE_STATISTIC)
    int64_t m_watchedTime;
    int64_t m_unwatchedTime;
    int64_t m_firstAcceptTime;
    int64_t m_lastAcceptTime;
    int64_t m_acceptedNumber;
#endif
};

inline IoStrategy& ListenSocket::GetIoStrategy() {
    return m_listenStrategy;
}

DECL_NAMESPACE_MZ_NET_END

#endif // _MZ_NET_LISTENSOCKET_HPP_
