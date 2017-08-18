
#ifndef HEAP_PATH_INL_
#define HEAP_PATH_INL_

#include "path.h"

#define NS heap::Path

template<typename... Next>
std::string NS::join(Next... next)
{
    return normalize(joinRec(std::forward<Next>(next)...));
}


template<typename... Next>
std::string NS::joinRec(const std::string & str, Next... next)
{
    if(str == "")
        return joinRec(std::forward<Next>(next)...);

    return str + delimiter + join(std::forward<Next>(next)...);
}

#undef NS

#endif 