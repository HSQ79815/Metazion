#ifndef _MZ_SHARE_ARRAYLIST_HPP_
#define _MZ_SHARE_ARRAYLIST_HPP_

#include "Metazion/Share/ShareInclude.hpp"

#include "Metazion/Share/Collection/SelfArrayList.hpp"
#include "Metazion/Share/Memory/HeapAllocator.hpp"

DECL_NAMESPACE_MZ_SHARE_BEGIN

template<typename ValueType
, int INITSIZE
, typename CompareType = LessCompare<ValueType>
, typename AllocatorFamily = HeapAllocator<>
>
class ArrayList {
    using Value_t = ValueType;
    using Compare_t = CompareType;
    using Node_t = SelfArrayListNode<Value_t>;
    using List_t = SelfArrayList<Node_t, INITSIZE>;
    using Allocator_t = typename AllocatorFamily::template Rebind<sizeof(Node_t)>;

    class Iterator {
        friend class ArrayList;

    private:
        ArrayList* m_owner = nullptr;
        Node_t* m_node = nullptr;

    public:
        Iterator() {}

        Iterator(const Iterator& other)
            : m_owner(other.m_owner)
            , m_node(other.m_node) {}

        Iterator(ArrayList* owner, Node_t* node)
            : m_owner(owner)
            , m_node(node) {}

        ~Iterator() {}

        Iterator& operator =(const Iterator& other) {
            if (&other != this) {
                m_owner = other.m_owner;
                m_node = other.m_node;
            }
            return *this;
        }

        auto& operator *() {
            return m_node->m_value;
        }

        auto* operator ->() {
            return &m_node->m_value;
        }

        Iterator& operator ++() {
            m_node = m_owner->Forward(m_node);
            return *this;
        }

        Iterator operator ++(int) {
            auto temp = *this;
            m_node = m_owner->Forward(m_node);
            return temp;
        }

        bool operator ==(const Iterator& other) const {
            return m_node == other.m_node;
        }

        bool operator !=(const Iterator& other) const {
            return !operator ==(other);
        }
    };

    class ConstIterator {
        friend class ArrayList;

    private:
        const ArrayList* m_owner = nullptr;
        const Node_t* m_node = nullptr;

    public:
        ConstIterator() {}

        ConstIterator(const ConstIterator& other)
            : m_owner(other.m_owner)
            , m_node(other.m_node) {}

        ConstIterator(const ArrayList* owner, const Node_t* node)
            : m_owner(owner)
            , m_node(node) {}

        ~ConstIterator() {}

        ConstIterator& operator =(const ConstIterator& other) {
            if (&other != this) {
                m_owner = other.m_owner;
                m_node = other.m_node;
            }
            return *this;
        }

        const auto& operator *() {
            return m_node->m_value;
        }

        const auto* operator ->() {
            return &m_node->m_value;
        }

        ConstIterator& operator ++() {
            m_node = m_owner->Forward(m_node);
            return *this;
        }

        ConstIterator operator ++(int) {
            const auto temp = *this;
            m_node = m_owner->Forward(m_node);
            return temp;
        }

        bool operator ==(const ConstIterator& other) const {
            return m_node == other.m_node;
        }

        bool operator !=(const ConstIterator& other) const {
            return !operator ==(other);
        }
    };

public:
    using Iterator_t = Iterator;
    using ConstIterator_t = ConstIterator;

private:
    Compare_t m_compare;
    Allocator_t m_allocator;
    List_t m_list;

public:
    ArrayList() {}

    ~ArrayList() {}

    ArrayList(const ArrayList& other) {
        *this = other;
    }

    ArrayList& operator =(const ArrayList& other) {
        if (&other != this) {
            Clear();
            for (const auto& value : other) {
                PushBack(value);
            }
        }
        return *this;
    }

    ArrayList(ArrayList&& other) {
        *this = std::move(other);
    }

    ArrayList& operator =(ArrayList&& other) {
        *this = other;
        return *this;
    }

public:
    void Clear() {
        while (!IsEmpty()) {
            PopFront();
        }
    }

    bool IsEmpty() const {
        return m_list.IsEmpty();
    }

    int GetSize() const {
        return m_list.GetSize();
    }

    Node_t* Backward(Node_t* node) {
        return m_list.Backward(node);
    }

    const Node_t* Backward(const Node_t* node) const {
        return m_list.Backward(node);
    }

    Node_t* Forward(Node_t* node) {
        return m_list.Forward(node);
    }

    const Node_t* Forward(const Node_t* node) const {
        return m_list.Forward(node);
    }

public:
    MZ_ADAPT_FOR_RANGE_TRAVERSAL()

    Iterator_t Begin() {
        auto node = m_list.Front();
        return Iterator_t(this, node);
    }

    ConstIterator_t Begin() const {
        const auto node = m_list.Front();
        return ConstIterator_t(this, node);
    }

    Iterator_t End() {
        return Iterator_t();
    }

    ConstIterator_t End() const {
        return ConstIterator_t();
    }

    Iterator_t Front() {
        auto node = m_list.Front();
        return Iterator_t(this, node);
    }

    Iterator_t Back() {
        auto node = m_list.Back();
        return Iterator_t(this, node);
    }

    Iterator_t PushFront(const Value_t& value) {
        auto node = CreateNode();
        MZ_ASSERT_TRUE(!IsNull(node));
        node->m_value = value;
        node = m_list.PushFront(node);
        return Iterator_t(this, node);
    }

    Iterator_t PushBack(const Value_t& value) {
        auto node = CreateNode();
        MZ_ASSERT_TRUE(!IsNull(node));
        node->m_value = value;
        node = m_list.PushBack(node);
        return Iterator_t(this, node);
    }

    Iterator_t PopFront() {
        auto node = m_list.PopFront();
        if (!IsNull(node)) {
            DestoryNode(node);
        }

        return Iterator_t(this, node);
    }

    Iterator_t PopBack() {
        auto node = m_list.PopBack();
        if (!IsNull(node)) {
            DestoryNode(node);
        }

        return Iterator_t(this, node);
    }

    Iterator_t InsertBefore(Iterator_t iter, const Value_t& value) {
        auto node = CreateNode();
        MZ_ASSERT_TRUE(!IsNull(node));
        node->m_value = value;
        m_list.InsertBefore(iter.m_node, node);
        return Iterator_t(this, node);
    }

    Iterator_t InsertAfter(Iterator_t iter, const Value_t& value) {
        auto node = CreateNode();
        MZ_ASSERT_TRUE(!IsNull(node));
        node->m_value = value;
        m_list.InsertAfter(iter.m_node, node);
        return Iterator_t(this, node);
    }

    Iterator_t Erase(Iterator_t iter) {
        auto nextNode = m_list.Remove(iter.m_node);
        DestoryNode(iter.m_node);
        return Iterator_t(this, nextNode);
    }

    Iterator_t Find(const Value_t& value) {
        for (Iterator_t iter = Begin(); iter != End(); ++iter) {
            if (m_compare(value, *iter) == 0) {
                return iter;
            }
        }

        return End();
    }

private:
    Node_t* CreateNode() {
        auto memory = m_allocator.Alloc();
        auto node = new(memory) Node_t();
        return node;
    }

    void DestoryNode(Node_t* node) {
        node->~Node_t();
        m_allocator.Free(node);
    }
};

DECL_NAMESPACE_MZ_SHARE_END

#endif // _MZ_SHARE_ARRAYLIST_HPP_
