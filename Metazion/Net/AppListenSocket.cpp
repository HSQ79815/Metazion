#include "Metazion/Net/AppListenSocket.hpp"

DECL_NAMESPACE_MZ_NET_BEGIN

AppListenSocket::AppListenSocket()
    : m_accepter(*this) {}

AppListenSocket::~AppListenSocket() {}

void AppListenSocket::Reset() {
    ListenSocket::Reset();

    m_accepter.Reset();

    DerivedReset();
}

void AppListenSocket::Prepare() {
    ListenSocket::Prepare();

    DerivedPrepare();
}

void AppListenSocket::Tick(int64_t now, int interval) {
    ListenSocket::Tick(now, interval);

    DerivedTick(now, interval);
}

void AppListenSocket::Dispatch() {
    ListenSocket::Dispatch();

    DerivedDispatch();
}

void AppListenSocket::OnWatched() {
    ListenSocket::OnWatched();

    DerivedOnWatched();
}

void AppListenSocket::OnUnwatched() {
    ListenSocket::OnUnwatched();

    DerivedOnUnwatched();
}

bool AppListenSocket::OnAccepted(const SockId_t& sockId, const Host& host) {
    auto ret = ListenSocket::OnAccepted(sockId, host);
    if (!ret) {
        return false;
    }

    ret = m_accepter.Accept(sockId, host);
    if (!ret) {
        return false;
    }

    return DerivedOnAccepted(sockId, host);
}

DECL_NAMESPACE_MZ_NET_END
