#include "Memory.h"
#include <cstdlib>
#include <new>

#ifndef TEZCAT_RELEASE

void* operator new(std::size_t size)
{
    int try_count = 2;
    while (try_count-- > 0)
    {
        void* p = std::malloc(size);
        if (p)
        {
            return p;
        }
        else
        {
            auto handler = std::get_new_handler();
            if (handler)
            {
                handler();
            }
        }
    }

    throw new std::bad_alloc();
}

void operator delete(void* memory, std::size_t size) noexcept
{
    std::free(memory);
}

void* operator new[](std::size_t size)
{
    int try_count = 2;
    while (try_count-- > 0)
    {
        void* p = std::malloc(size);
        if (p)
        {
            return p;
        }
        else
        {
            auto handler = std::get_new_handler();
            if (handler)
            {
                handler();
            }
        }
    }

    throw new std::bad_alloc();
}

void operator delete[](void* memory, std::size_t size) noexcept
{
    std::free(memory);
}
#endif

