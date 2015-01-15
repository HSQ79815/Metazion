#ifndef _MZ_NET_TCPSOCKETBUFFER_HPP_
#define _MZ_NET_TCPSOCKETBUFFER_HPP_

#include "Metazion/Net/NetInclude.hpp"

#include <mutex>

#include <Metazion/Share/Memory/PieceBuffer.hpp>
#include <Metazion/Share/Memory/StepBuffer.hpp>

DECL_NAMESPACE_MZ_NET_BEGIN

class SocketBuffer {
    MZ_DISALLOW_COPY_AND_ASSIGN(SocketBuffer)

    using Lock_t = std::mutex;
    using LockGuard_t = std::lock_guard<Lock_t>;

public:
    using SendCache_t = NS_SHARE::StepBuffer<1024 * 4, 1024 * 256>;
    using RecvCache_t = NS_SHARE::StepBuffer<1024 * 4, 1024 * 256>;
    using SendBuffer_t = NS_SHARE::PieceBuffer<1024 * 4>;
    using RecvBuffer_t = NS_SHARE::PieceBuffer<1024 * 4>;

public:
    SocketBuffer();
    
    ~SocketBuffer();

public:
    void Reset();

    void Prepare();

    void SetSendCachePool(SendCache_t::BufferPool_t& bufferPool);

    void SetRecvCachePool(SendCache_t::BufferPool_t& bufferPool);

    int PrepareSendBuffer();

    int PreserveRecvBuffer();

    bool HasDataToSend() const;

    bool HasDataRecvedYet() const;

public:
    std::mutex m_sendLock;
    std::mutex m_recvLock;
    SendCache_t m_sendCache;
    SendCache_t::BufferPool_t* m_sendCachePool;
    RecvCache_t m_recvCache;
    RecvCache_t::BufferPool_t* m_recvCachePool;
    SendBuffer_t m_sendBuffer;
    RecvBuffer_t m_recvBuffer;
};

DECL_NAMESPACE_MZ_NET_END

#endif // _MZ_NET_TCPSOCKETBUFFER_HPP_
