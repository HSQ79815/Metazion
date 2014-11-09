#ifndef _MZ_NET_PACKETDEFINE_HPP_
#define _MZ_NET_PACKETDEFINE_HPP_

#include "Metazion/Net/NetInclude.hpp"

#include <Metazion/Share/Collection/StaticArray.hpp>
#include <Metazion/Share/Memory/ObjectPool.hpp>
#include <Metazion/Share/Memory/StepBuffer.hpp>

DECL_NAMESPACE_MZ_NET_BEGIN

struct PacketHeader {
    int16_t m_command = 0;
    int16_t m_length = 0;
};

enum PacketValue {
    MAXNETDATALENGTH = 1024,
    MAXNETPACKETLENGTH = MAXNETDATALENGTH + sizeof(PacketHeader),
    
    MAXAPPDATALENGTH = 16 * 1024,
    MAXAPPPACKETLENGTH = MAXAPPDATALENGTH + sizeof(PacketHeader),
};

struct EncodeBuffer {
    enum { LENGTH = MAXAPPPACKETLENGTH };

    using Buffer_t = NS_SHARE::PieceBuffer<LENGTH>;
    
    Buffer_t m_resultBuffer;
};

struct DecodeBuffer {
    enum { LENGTH = MAXAPPPACKETLENGTH };

    using Buffer_t = NS_SHARE::PieceBuffer<LENGTH>;

    Buffer_t m_resultBuffer;
};

using PacketCache_t = NS_SHARE::StepBuffer<1024 * 4, 1024 * 256>;

using PacketArray_t = NS_SHARE::StaticArray<void*>;

DECL_NAMESPACE_MZ_NET_END

#endif // _MZ_NET_PACKETDEFINE_HPP_
