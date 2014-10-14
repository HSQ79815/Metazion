#ifndef _MZ_SHARE_UDSELFLIST_HPP_
#define _MZ_SHARE_UDSELFLIST_HPP_

#include "Metazion/Share/ShareInclude.hpp"

DECL_NAMESPACE_MZ_SHARE_BEGIN

template<typename ValueType>
struct UDSelfListNode {
    using Value_t = ValueType;

    Value_t m_value;
    UDSelfListNode* m_nextNode = nullptr;
};

template<>
struct UDSelfListNode<void> {
    UDSelfListNode* m_nextNode = nullptr;
};

template<typename NodeType>
class UDSelfList {
    DISALLOW_COPY_AND_ASSIGN(UDSelfList)

    using Node_t = NodeType;

public:
    UDSelfList()
        : m_headNode(nullptr)
        , m_tailNode(nullptr)
        , m_size(0) {}

    ~UDSelfList() {}

public:
    void Clear() {
        while (!IsEmpty()) {
            PopFront();
        }
    }

    bool IsEmpty() const {
        return nullptr == m_headNode;
    }

    int GetSize() const {
        return m_size;
    }

    const Node_t* Front() const {
        return m_headNode;
    }

    Node_t* Front() {
        return m_headNode;
    }

    const Node_t* Back() const {
        return m_tailNode;
    }

    Node_t* Back() {
        return m_tailNode;
    }

    void PopFront() {
        if (IsNull(m_headNode)) {
            ASSERT_TRUE(false);
            return;
        }

        auto node = m_headNode;
        m_headNode = m_headNode->m_nextNode;
        if (IsNull(m_headNode)) {
            m_tailNode = nullptr;
        }
        node->m_nextNode = nullptr;
        --m_size;
    }

    void PushFront(Node_t* node) {
        ASSERT_TRUE(!IsNull(node));

        node->m_nextNode = nullptr;
        if (IsNull(m_headNode)) {
            m_headNode = node;
            m_tailNode = node;
        }
        else {
            node->m_nextNode = m_headNode;
            m_headNode = node;
        }
        ++m_size;
    }

    void PushBack(Node_t* node) {
        ASSERT_TRUE(!IsNull(node));

        node->m_nextNode = nullptr;
        if (IsNull(m_tailNode)) {
            m_headNode = node;
            m_tailNode = node;
        }
        else {
            m_tailNode->m_nextNode = node;
            m_tailNode = node;
        }
        ++m_size;
    }

    void InsertAfter(Node_t* location, Node_t* node) {
        ASSERT_TRUE(!IsNull(location));
        ASSERT_TRUE(!IsNull(node));
        ASSERT_TRUE(IsContain(location));
        ASSERT_TRUE(!IsContain(node));

        auto nextNode = location->m_nextNode;
        if (IsNull(nextNode)) {
            m_tailNode = node;
        }
        location->m_nextNode = node;
        node->m_nextNode = nextNode;
        ++m_size;
    }

    Node_t* Remove(Node_t* node) {
        ASSERT_TRUE(!IsNull(node));
        ASSERT_TRUE(IsContain(node));

        Node_t* prevNode = nullptr;
        auto curNode = m_headNode;
        while (!IsNull(curNode)) {
            auto nextNode = curNode->m_nextNode;
            if (node != curNode) {
                prevNode = curNode;
                curNode = nextNode;
                continue;
            }

            if (IsNull(prevNode)) {
                m_headNode = nextNode;
                if (IsNull(nextNode)) {
                    m_tailNode = nullptr;
                }
            }
            else {
                prevNode->m_nextNode = nextNode;
                if (IsNull(nextNode)) {
                    m_tailNode = prevNode;
                }
            }
          
            node->m_nextNode = nullptr;
            --m_size;
            return nextNode;
        }

        ASSERT_TRUE(false);
        return nullptr;
    }

    const Node_t* Forward(const Node_t* node) const {
        ASSERT_TRUE(!IsNull(node));

        return node->m_nextNode;
    }

    Node_t* Forward(Node_t* node) {
        ASSERT_TRUE(!IsNull(node));

        return node->m_nextNode;
    }

    bool IsContain(Node_t* node) const {
        ASSERT_TRUE(!IsNull(node));

        auto cursor = Front();
        while (!IsNull(cursor)) {
            if (node == cursor) {
                return true;
            }
            cursor = Forward(cursor);
        }
        return false;
    }

private:
    Node_t* m_headNode;
    Node_t* m_tailNode;
    int m_size;
};

DECL_NAMESPACE_MZ_SHARE_END

#endif // _MZ_SHARE_UDSELFLIST_HPP_
