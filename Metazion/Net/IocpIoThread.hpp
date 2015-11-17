#ifndef _MZ_NET_IOCPIOTHREAD_HPP_
#define _MZ_NET_IOCPIOTHREAD_HPP_

#include "Metazion/Net/NetInclude.hpp"

#if defined(NETWORK_USE_IOCP_MODEL)

#include <atomic>

#include <Metazion/Share/Thread/Thread.hpp>

#include "Metazion/Net/SocketCtrl.hpp"
#include "Metazion/Net/SocketDefine.hpp"

DECL_NAMESPACE_MZ_NET_BEGIN

class NetworkService;

class IocpIoThread : public NS_SHARE::Thread {
    MZ_DISALLOW_COPY_AND_ASSIGN(IocpIoThread)

    enum Result {
        RESULT_SUCCESS = 1,
        RESULT_FAILURE,
        RESULT_CLOSE,
        RESULT_TIMEOUT,
        RESULT_ERROR,
    };

private:
    NetworkService* m_networkService = nullptr;
    int m_index = 0;
    std::atomic<bool> m_stopDesired = { false };

public:
    IocpIoThread();

    ~IocpIoThread();

public:
    void Initialize(NetworkService* networkService, int index);

    void Finalize();

protected:
    void Execute() override final;

private:
    int AnalyseStatusResult(BOOL ret
        , OVERLAPPED* overlapped
        , DWORD numberOfBytes
        , DWORD error);
};

DECL_NAMESPACE_MZ_NET_END

#endif

#endif // _MZ_NET_IOCPIOTHREAD_HPP_
