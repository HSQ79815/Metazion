#include "Metazion/Net/AppServerSocket.hpp"

#include "Metazion/Net/AppSocketServer.hpp"

DECL_NAMESPACE_MZ_NET_BEGIN

AppServerSocket::AppServerSocket()
    : m_packetCodec(*this) {}

AppServerSocket::~AppServerSocket() {}

void AppServerSocket::Dispatch() {
    auto& decodeBuffer = GetDecodeBuffer();

    while (true) {
        int command = 0;
        decodeBuffer.m_resultBuffer.Reset();
        const auto ret = m_packetCodec.Decode(command, decodeBuffer);
        if (ret == 0) {
            break;
        }
        else if (ret < 0) {
            OnInvalidPacket();
            break;
        }

        const auto pullBuffer = decodeBuffer.m_resultBuffer.GetPullBuffer();
        const auto pullLength = decodeBuffer.m_resultBuffer.GetPullLength();
        OnValidPacket(command, pullBuffer, pullLength);
    }
}

bool AppServerSocket::SendData(int command, const void* data, int length) {
    auto& encodeBuffer = GetEncodeBuffer();
    encodeBuffer.m_resultBuffer.Reset();

    const auto ret = m_packetCodec.Encode(command, data, length, encodeBuffer);
    if (ret <= 0) {
        return false;
    }

    const auto pullBuffer = encodeBuffer.m_resultBuffer.GetPullBuffer();
    const auto pullLength = encodeBuffer.m_resultBuffer.GetPullLength();
    return Send(pullBuffer, pullLength) == pullLength;
}

void AppServerSocket::PostData(int command, const void* data, int length) {
    OnValidPacket(command, data, length);
}

EncodeBuffer& AppServerSocket::GetEncodeBuffer() {
    auto server = GetSocketServer();
    auto appServer = static_cast<AppSocketServer*>(server);
    ASSERT_TRUE(!IsNull(appServer));
    return appServer->GetEncodeBuffer();
}

DecodeBuffer& AppServerSocket::GetDecodeBuffer() {
    auto server = GetSocketServer();
    auto appServer = static_cast<AppSocketServer*>(server);
    ASSERT_TRUE(!IsNull(appServer));
    return appServer->GetDecodeBuffer();
}

DECL_NAMESPACE_MZ_NET_END
