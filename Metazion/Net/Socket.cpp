#include "Metazion/Net/Socket.hpp"

DECL_NAMESPACE_MZ_NET_BEGIN

Socket::Socket()
    : m_refCount(0)
    , m_ioAvailable(false)
    , m_sockId(INVALID_SOCKID)
    , m_index(-1)
    , m_socketServer(nullptr) {}

Socket::~Socket() {}

void Socket::Reset() {
    m_refCount = 0;
    m_ioAvailable = false;
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

bool Socket::IsActive() {
    if (!IsReady()) {
        return false;
    }

    return true;
}

bool Socket::IsClosed() {
    if (IsReady()) {
        return false;
    }

    return true;
}

bool Socket::IsClosing() {
    if (IsValid()) {
        return true;
    }

    return false;
}

void Socket::Rework() {
    OnStarted();
    m_ioAvailable = true;
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

    m_ioAvailable = false;
    DetachSockId();
    m_lock.Unlock();

    OnClosed();
}

bool Socket::IsValid() const {
    return m_refCount > 0;
}

bool Socket::IsReady() const {
    return INVALID_SOCKID != m_sockId;
}

void Socket::GrabRef() {
    m_lock.Lock();
    ++m_refCount;
    m_lock.Unlock();
}

void Socket::ReleaseRef() {
    m_lock.Lock();
    --m_refCount;
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
