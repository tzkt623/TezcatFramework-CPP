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
    virtual TezTypeUID getTypeUID() = 0;
    virtual std::string_view getTypeName() = 0;
};

template<class Com>
struct ComponentT : Component
{
    TezTypeUID getTypeUID() override final { return TezTypeInfo<Component, Com>::UID;}
    std::string_view getTypeName() override final { return TezTypeInfo<Component, Com>::Name; }

    static TezTypeUID staticGetTypeUID() { return TezTypeInfo<Component, Com>::UID; }
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
    TEZ_LOG("name:{} id:{}", MyTypeInfo<MyType1>::Name, MyTypeInfo<MyType1>::UID);
    TEZ_LOG("name:{} id:{}", MyTypeInfo<MyType2>::Name, MyTypeInfo<MyType2>::UID);
    TEZ_LOG("name:{} id:{}", MyTypeInfo<MyType3>::Name, MyTypeInfo<MyType3>::UID);
    TEZ_LOG("name:{} id:{}", MyTypeInfo<MyType4>::Name, MyTypeInfo<MyType4>::UID);

    Camera t1;
    TEZ_LOG("name:{} id:{}", t1.getTypeName(), t1.getTypeUID());
    TEZ_LOG("name:{} id:{}", Camera::staticGetTypeName(), Camera::staticGetTypeUID());
    Transform t2;
    TEZ_LOG("name:{} id:{}", t2.getTypeName(), t2.getTypeUID());
    TEZ_LOG("name:{} id:{}", Transform::staticGetTypeName(), Transform::staticGetTypeUID());
    Renderer t3;
    TEZ_LOG("name:{} id:{}", t3.getTypeName(), t3.getTypeUID());
    TEZ_LOG("name:{} id:{}", Renderer::staticGetTypeName(), Renderer::staticGetTypeUID());

    TEZ_LOG("size:{}", TezTypeManager::getInfoMap<Component>().size());

    for (auto& pair : TezTypeManager::getInfoMap<Component>())
    {
        TEZ_LOG("name: {} hash: {}", pair.first.name(), pair.first.hash_code());
    }

    TEZ_PAUSE;

    return 0;
}
