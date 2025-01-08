#pragma once

#include "../TezConfig.h"

namespace tezcat
{
    class TEZCAT_API ITezCloseable
    {
    public:
        virtual ~ITezCloseable() {};
        virtual void close() = 0;
    };

    class TEZCAT_API TezBaseObject : public ITezCloseable
    {
    public:
        TezBaseObject();
        virtual ~TezBaseObject();
    };
}
