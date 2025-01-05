#include "../TezcatFramework/Utility/Debug.h"

using namespace tezcat;

int main()
{
    //Debug::log("er32", "asd");
    TEZ_LOG("Test{}{}{}", 1, "haha", 3.14);

    return 0;
}
