#ifndef _MZ_SHARE_HEAPALLOCATOR_HPP_
#define _MZ_SHARE_HEAPALLOCATOR_HPP_

#include "Metazion/Share/ShareInclude.hpp"

DECL_NAMESPACE_MZ_SHARE_BEGIN

template<int UNITLENGTH = MZ_DEFAULT_ALIGNMENT>
class HeapAllocator {
    MZ_DISALLOW_COPY_AND_ASSIGN(HeapAllocator)

    enum { ALIGNLENGTH = MZ_ALIGN_LENGTH(UNITLENGTH, MZ_DEFAULT_ALIGNMENT) };

public:
    template<int OTHERLENGTH>
    using Rebind = HeapAllocator<OTHERLENGTH>;

public:
    HeapAllocator() {}

    ~HeapAllocator() {}

public:
    void* Alloc() {
        return malloc(ALIGNLENGTH);
    }

    void Free(void* memory) {
        free(memory);
    }
};

DECL_NAMESPACE_MZ_SHARE_END

#endif // _MZ_SHARE_HEAPALLOCATOR_HPP_
