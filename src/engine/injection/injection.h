#ifndef MOLE_INJECTION_H
#define MOLE_INJECTION_H

#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <typeinfo>

namespace MoleDemo
{
    using id_capacity = uint_fast8_t;
    using id_t = std::size_t;

    struct Factory
    {
        Factory() = default;
        virtual ~Factory() {};

        virtual void* GetAnyToInstance(id_capacity id = 0) = 0;
    };

    template<typename I, typename T, typename... TArguments>
    class UniqueFactory : public Factory
    {
        std::vector<std::unique_ptr<T>> instances;
        const std::function<T*()> functor;

    public:
        UniqueFactory() : UniqueFactory{ [] { return T{}; } } {}
        UniqueFactory(std::function<T*()>&& instancer) : functor{ std::move(instancer) } {}
        ~UniqueFactory() override = default;

        void* GetAnyToInstance(id_capacity id = 0) override
        {
            return static_cast<void*>(instances.emplace_back(std::unique_ptr<T>(functor())).get());
        }
    };

    template<typename I, typename T>
    class SharingFactory : public Factory
    {
        std::map<id_capacity, std::unique_ptr<T>> instances{};
        const std::function<T*()> functor;

    public:
        SharingFactory() : SharingFactory{ [] { return new T{}; } } {}
        SharingFactory(std::function<T*()>&& instancer) : functor{ std::move(instancer) } {}
        ~SharingFactory() override {}

        void* GetAnyToInstance(id_capacity id = 0) override
        {
            if (!instances.count(id))
            {
                instances.emplace(id, std::unique_ptr<T>(functor()));
            }

            return static_cast<void*>(instances.at(id).get());
        }
    };

    class Container
    {
        std::map<id_t, Factory*> factories{};

    public:
        Container() = default;
        ~Container() = default;
        Container(const Container&) = delete;
        Container(Container&&) = delete;

        template<typename T>
        void BindUnique()
        {
            BindUnique<T, T>();
        }

        template<typename T>
        void BindUnique(std::function<T*()>&& functor)
        {
            BindUnique<T, T>(std::move(functor));
        }

        template<typename TInterface, typename TConcrete, typename... TArguments>
        void BindUnique()
        {
            id_t id{ typeid(TInterface).hash_code() };
            factories[id] = std::unique_ptr<Factory>{ new UniqueFactory<TInterface, TConcrete>{} };
        }

        template<typename TInterface, typename TConcrete, typename... TArguments>
        void BindUnique(std::function<TConcrete*()>&& functor)
        {
            id_t id{ typeid(TInterface).hash_code() };
            factories[id] = std::unique_ptr<Factory>{ new UniqueFactory<TInterface, TConcrete>{ std::move(functor) } };
        }

        template<typename T>
        void BindShared()
        {
            BindShared<T, T>();
        }

        template<typename T>
        void BindShared(std::function<T*()>&& functor)
        {
            BindShared<T, T>(std::move(functor));
        }

        template<typename TInterface, typename TConcrete, typename... TArguments>
        void BindShared()
        {
            id_t id{ typeid(TInterface).hash_code() };
            factories[id] = std::unique_ptr<Factory>{ new SharingFactory<TInterface, TConcrete>{} };
        }

        template<typename TInterface, typename TConcrete, typename... TArguments>
        void BindShared(std::function<TConcrete*()>&& functor)
        {
            id_t id{ typeid(TInterface).hash_code() };
            factories[id] = std::unique_ptr<Factory>(new SharingFactory<TInterface, TConcrete>{ std::move(functor) });
        }

        template<typename T, typename... TArguments>
        T& Inject(id_t id = 0)
        {

            if (factories.find(typeid(T).hash_code()) == factories.end())
            {
                throw std::exception();
            }

            Factory* it( factories.find(typeid(T).hash_code())->second );

            void* value( it->GetAnyToInstance() );
            T* instance( reinterpret_cast<T*>(value) );

            return *instance;
        }
    };
}
#endif //! MOLE_INJECTION_H
