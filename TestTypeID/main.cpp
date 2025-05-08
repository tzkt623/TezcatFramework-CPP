#include "../TezcatFramework/include/TezcatFramework.h"

using namespace::tezcat;

struct Owner1
{

};

template<class T>
using MyTypeInfo = TezTypeInfo<Owner1, T>;


struct MyType1
{

};

struct MyType2 : MyType1
{

};

struct MyType3 : MyType2
{

};

struct MyType4 : MyType3
{

};


struct Component
{
    virtual uint64 getTypeIndex() = 0;
    virtual uint64 getTypeCategory() = 0;
    virtual uint64 getTypeUID() = 0;
    virtual std::string_view getTypeName() = 0;
};

template<class Com>
struct ComponentT : Component
{
    uint64 getTypeIndex() override final { return TezTypeInfo<Component, Com>::getTypeIndex(); }
    uint64 getTypeCategory() override final { return TezTypeInfo<Component, Com>::getTypeCategory(); }
    uint64 getTypeUID() override final { return TezTypeInfo<Component, Com>::getTypeUID(); }
    std::string_view getTypeName() override final { return TezTypeInfo<Component, Com>::Name; }

    static uint64 staticGetTypeIndex() { return TezTypeInfo<Component, Com>::getTypeIndex(); }
    static uint64 staticGetTypeCategory() { return TezTypeInfo<Component, Com>::getTypeCategory(); }
    static uint64 staticGetTypeUID() { return TezTypeInfo<Component, Com>::getTypeUID(); }
    static std::string_view staticGetTypeName() { return TezTypeInfo<Component, Com>::Name; }
};

struct Camera : ComponentT<Camera>
{

};

struct Transform : ComponentT<Transform>
{

};

struct Renderer : ComponentT<Renderer>
{

};

int main()
{


    TEZ_LOG("name:{} category:{} index:{} uid:{}", MyTypeInfo<MyType1>::Name, MyTypeInfo<MyType1>::getTypeCategory(), MyTypeInfo<MyType1>::getTypeIndex(), MyTypeInfo<MyType1>::getTypeUID());
    TEZ_LOG("name:{} category:{} index:{} uid:{}", MyTypeInfo<MyType2>::Name, MyTypeInfo<MyType2>::getTypeCategory(), MyTypeInfo<MyType2>::getTypeIndex(), MyTypeInfo<MyType2>::getTypeUID());
    TEZ_LOG("name:{} category:{} index:{} uid:{}", MyTypeInfo<MyType3>::Name, MyTypeInfo<MyType3>::getTypeCategory(), MyTypeInfo<MyType3>::getTypeIndex(), MyTypeInfo<MyType3>::getTypeUID());
    TEZ_LOG("name:{} category:{} index:{} uid:{}", MyTypeInfo<MyType4>::Name, MyTypeInfo<MyType4>::getTypeCategory(), MyTypeInfo<MyType4>::getTypeIndex(), MyTypeInfo<MyType4>::getTypeUID());

    Camera t1;
    TEZ_LOG("name:{} category:{} index:{} uid:{}", t1.getTypeName(), t1.getTypeCategory(), t1.getTypeIndex(), t1.getTypeUID());
    TEZ_LOG("name:{} category:{} index:{} uid:{}", Camera::staticGetTypeName(), Camera::staticGetTypeCategory(), Camera::staticGetTypeIndex(), Camera::staticGetTypeUID());
    Transform t2;
    TEZ_LOG("name:{} category:{} index:{} uid:{}", t2.getTypeName(), t2.getTypeCategory(), t2.getTypeIndex(), t2.getTypeUID());
    TEZ_LOG("name:{} category:{} index:{} uid:{}", Transform::staticGetTypeName(), Transform::staticGetTypeCategory(), Transform::staticGetTypeIndex(), Transform::staticGetTypeUID());
    Renderer t3;
    TEZ_LOG("name:{} category:{} index:{} uid:{}", t3.getTypeName(), t3.getTypeCategory(), t3.getTypeIndex(), t3.getTypeUID());
    TEZ_LOG("name:{} category:{} index:{} uid:{}", Renderer::staticGetTypeName(), Renderer::staticGetTypeCategory(), Renderer::staticGetTypeIndex(), Renderer::staticGetTypeUID());

    TEZ_LOG("size:{}", TezTypeManager::getInfoMap<Component>().size());

    for (auto& pair : TezTypeManager::getInfoMap<Component>())
    {
        TEZ_LOG("name: {} hash: {}", pair.first.name(), pair.first.hash_code());
    }

    TEZ_LOG("equal:{}", MyTypeInfo<MyType1>::TypeID == MyTypeInfo<MyType2>::TypeID);

    TEZ_PAUSE;

    return 0;
}
