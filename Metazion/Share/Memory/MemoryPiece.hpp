#ifndef _MZ_SHARE_MEMORYPIECE_HPP_
#define _MZ_SHARE_MEMORYPIECE_HPP_

#include "Metazion/Share/ShareInclude.hpp"

DECL_NAMESPACE_MZ_SHARE_BEGIN

template<int MAXSIZE
, int UNITLENGTH
>
class MemoryPiece {
    MZ_DISALLOW_COPY_AND_ASSIGN(MemoryPiece)

    typedef struct Node {
        Node* m_nextNode = nullptr;
    } Node_t;
    
    enum { 
        MINLENGTH = MZ_MAX(UNITLENGTH, sizeof(Node_t)),
        ALIGNLENGTH = MZ_ALIGN_LENGTH(MINLENGTH, MZ_DEFAULT_ALIGNMENT),
    };
    
    typedef struct Unit {
        char m_buffer[ALIGNLENGTH] = { 0 };
    } Unit_t;

private:
    Unit_t m_units[MAXSIZE];
    Node_t* m_freeList = nullptr;
    int m_count = 0;
    int m_freeCount = 0;

public:
    MemoryPiece() {}

    ~MemoryPiece() {}

public:
    void Reset() {
        m_freeList = nullptr;
        m_count = 0;
        m_freeCount = 0;
    }

    void* Obtain() {
        if (!IsNull(m_freeList)) {
            auto node = m_freeList;
            m_freeList = m_freeList->m_nextNode;
            --m_freeCount;
            return node;
        }

        if (m_count < MAXSIZE) {
            auto unit = &m_units[m_count];
            ++m_count;
            return unit;
        }

        return nullptr;
    }

    void Return(void* memory) {
        MZ_ASSERT_TRUE(IsResponsible(memory));

        auto node = static_cast<Node_t*>(memory);
        node->m_nextNode = m_freeList;
        m_freeList = node;
        ++m_freeCount;
    }

    bool IsResponsible(void* memory) const {
        return memory >= &m_units[0] && memory <= &m_units[m_count - 1];
    }

    bool IsAvaliable() const {
        return m_count < MAXSIZE || m_freeCount > 0;
    }

    bool IsEmpty() const {
        return m_freeCount == m_count;
    }

    int GetUnitLength() const {
        return ALIGNLENGTH;
    }
};

DECL_NAMESPACE_MZ_SHARE_END

#endif // _MZ_SHARE_MEMORYPIECE_HPP_
