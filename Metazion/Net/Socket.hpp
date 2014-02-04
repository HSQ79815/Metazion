#ifndef _MZ_NET_SOCKET_HPP_
#define _MZ_NET_SOCKET_HPP_

#include "Metazion/Net/NetInclude.hpp"

#include <Metazion/Share/Sync/AutoGuard.hpp>
#include <Metazion/Share/Sync/MutexLock.hpp>

#include "Metazion/Net/Host.hpp"
#include "Metazion/Net/IoStrategy.hpp"
#include "Metazion/Net/SocketDefine.hpp"

DECL_NAMESPACE_MZ_NET_BEGIN

class SocketServer;

class Socket {
    DISALLOW_COPY_AND_ASSIGN(Socket)

public:
    Socket();

    virtual ~Socket();

public:
    virtual int GetType() const = 0;

    virtual IoStrategy& GetIoStrategy() = 0;

    virtual void Reset();

    virtual void Destory();

    virtual void Tick(int interval);

    virtual void OnAttached();

    virtual void OnDetached();

    virtual void OnStarted();

    virtual void OnClosed();

    virtual bool OnAccepted(const SockId_t& sockId);

    virtual int OnSendData(const void* data, int length);

    virtual int OnRecvData(const void* data, int length);

    virtual bool OnError(int error);

    virtual bool IsActive() const;
    
    virtual bool IsClosed() const;

    virtual bool IsAlive() const;

public:
    bool IsValid() const;

    bool IsReady() const;

    bool IsWorking() const;

    void Start();
    
    void Close();

    void Retain();

    void Release();

    const SockId_t& GetSockId() const;

    void AttachSockId(const SockId_t& sockId);

    void DetachSockId();

    int GetIndex() const;

    void SetIndex(int index);

    SocketServer* GetSocketServer();

    void SetSocketServer(SocketServer* socketServer);

protected:
    NS_SHARE::MutexLock m_lock;
    volatile int m_reference;
    volatile bool m_working;
    SockId_t m_sockId;
    int m_index;
    SocketServer* m_socketServer;
};

inline bool Socket::IsValid() const {
    return m_reference > 0;
}

inline bool Socket::IsReady() const {
    return INVALID_SOCKID != m_sockId;
}

inline bool Socket::IsWorking() const {
    return m_working;
}

inline const SockId_t& Socket::GetSockId() const {
    return m_sockId;
}

inline int Socket::GetIndex() const {
    return m_index;
}

inline void Socket::SetIndex(int index) {
    m_index = index;
}

inline SocketServer* Socket::GetSocketServer() {
    return m_socketServer;
}

inline void Socket::SetSocketServer(SocketServer* socketServer) {
    m_socketServer = socketServer;
}

DECL_NAMESPACE_MZ_NET_END

#endif // _MZ_NET_SOCKET_HPP_
