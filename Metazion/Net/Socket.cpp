#include "Metazion/Net/Socket.hpp"

DECL_NAMESPACE_MZ_NET_BEGIN

Socket::Socket()
    : m_reference(0)
    , m_working(false)
    , m_sockId(INVALID_SOCKID)
    , m_index(-1)
    , m_socketServer(nullptr) {}

Socket::~Socket() {}

void Socket::Reset() {
    m_reference = 0;
    m_working = false;
    m_sockId = INVALID_SOCKID;
    m_index = -1;
    m_socketServer = nullptr;
}

void Socket::Destory() {
    delete this;
}

void Socket::Tick(int interval) {}

void Socket::OnAttached() {}

void Socket::OnDetached() {}

void Socket::OnStarted() {}

void Socket::OnClosed() {}

bool Socket::OnAccepted(const SockId_t& sockId) {
    return true;
}

int Socket::OnSendData(const void* data, int length) {
    return length;
}

int Socket::OnRecvData(const void* data, int length) {
    return length;
}

bool Socket::OnError(int error) {
    return true;
}

bool Socket::IsActive() const {
    if (!IsReady()) {
        return false;
    }

    return true;
}

bool Socket::IsClosed() const {
    if (IsReady()) {
        return false;
    }

    return true;
}

bool Socket::IsAlive() const {
    if (IsValid()) {
        return true;
    }

    return false;
}

void Socket::Start() {
    OnStarted();
    m_working = true;
}

void Socket::Close() {
    if (INVALID_SOCKID == m_sockId) {
        return;
    }

    m_lock.Lock();
    if (INVALID_SOCKID == m_sockId) {
        m_lock.Unlock();
        return;
    }

    m_working = false;
    DetachSockId();
    m_lock.Unlock();

    OnClosed();
}

void Socket::Retain() {
    m_lock.Lock();
    ++m_reference;
    m_lock.Unlock();
}

void Socket::Release() {
    m_lock.Lock();
    --m_reference;
    m_lock.Unlock();
}

void Socket::AttachSockId(const SockId_t& sockId) {
    m_sockId = sockId;
}

void Socket::DetachSockId() {
    if (INVALID_SOCKID != m_sockId) {
        DestroySockId(m_sockId);
        m_sockId = INVALID_SOCKID;
    }
}

DECL_NAMESPACE_MZ_NET_END
