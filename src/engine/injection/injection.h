#ifndef MOLE_INJECTION_H
#define MOLE_INJECTION_H

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <typeinfo>

namespace MoleDemo
{
    typedef unsigned char id_capacity;
    typedef size_t id_t;
    typedef void* (*instancer_f)();

    template<typename T>
    int type_id_f(const std::type_info& ti)
    {
        // duff-device version of gawk's sdbm algorithm
        std::string name(ti.name());
        size_t hash = 0;
        char* pos(&*name.begin());
        while (pos != &*name.end())
        {
            hash = *pos + (hash << 6) + (hash << 16) - hash;
            ++pos;
        }
        return hash;
    }

    template<typename T>
    void* default_instancer()
    {
        return reinterpret_cast<void*>(new T());
    }

    struct Factory
    {
        virtual ~Factory() {};

        virtual void* GetAnyToInstance(id_capacity id = 0) = 0;
    };

    template<typename I, typename T>
    class UniqueFactory : public Factory
    {
        std::vector<T*> instances;
        const instancer_f functor;

    public:
        UniqueFactory() : functor(default_instancer<T>) {}
        UniqueFactory(instancer_f instancer) : functor(instancer) {}
        ~UniqueFactory()
        {
            if (!instances.empty())
            {
                for (T* iter = instances.begin()->second; iter != instances.rbegin()->second + 1; ++iter)
                {
                    delete (iter);
                }
            }
        }

        void* GetAnyToInstance(id_capacity id = 0) { return static_cast<void*>(instances.emplace_back(functor())); }
    };

    template<typename I, typename T>
    class SharingFactory : public Factory
    {
        std::map<id_capacity, T*> instances;
        const instancer_f functor;

    public:
        SharingFactory() : functor(default_instancer<T>) {}
        SharingFactory(instancer_f instancer) : functor(instancer) {}
        ~SharingFactory()
        {
            if (!instances.empty())
            {
                for (T* iter = instances.begin()->second; iter != instances.rbegin()->second + 1; ++iter)
                {
                    delete (iter);
                }
            }
        }

        void* GetAnyToInstance(id_capacity id = 0)
        {
            if (!instances.count(id))
            {
                instances.insert(std::make_pair(id, reinterpret_cast<T*>(functor())));
            }

            return static_cast<void*>(instances.at(id));
        }
    };

    class Container
    {
        std::map<id_t, Factory*> factories;

    public:
        Container() {}
        ~Container()
        {
            if (!factories.empty())
            {
                for (Factory* f = factories.begin()->second; f < factories.rbegin()->second + 1; ++f)
                {
                    delete (f);
                }
            }
        }

        template<typename T>
        void BindUnique()
        {
            BindUnique<T, T>();
        }

        template<typename T>
        void BindUnique(instancer_f functor)
        {
            BindUnique<T, T>(functor);
        }

        template<typename TInterface, typename TConcrete>
        void BindUnique()
        {
            id_t id(type_id_f<TInterface>(typeid(TInterface)));
            factories[id] = new UniqueFactory<TInterface, TConcrete>(default_instancer<TConcrete>());
        }

        template<typename TInterface, typename TConcrete>
        void BindUnique(instancer_f functor)
        {
            id_t id(type_id_f<TInterface>(typeid(TInterface)));
            factories[id] = new UniqueFactory<TInterface, TConcrete>(functor);
        }

        template<typename T>
        void BindShared()
        {
            BindShared<T, T>();
        }

        template<typename T>
        void BindShared(instancer_f functor)
        {
            BindShared<T, T>(functor);
        }

        template<typename TInterface, typename TConcrete>
        void BindShared()
        {
            id_t id(type_id_f<TInterface>(typeid(TInterface)));
            factories[id] = new SharingFactory<TInterface, TConcrete>(default_instancer<TConcrete>);
        }

        template<typename TInterface, typename TConcrete>
        void BindShared(instancer_f functor)
        {
            id_t id(type_id_f<TInterface>(typeid(TInterface)));
            factories[id] = new SharingFactory<TInterface, TConcrete>(functor);
        }

        template<typename T>
        T& Inject(id_t id = 0)
        {
            if (factories.find(type_id_f<T>(typeid(T))) == factories.end())
            {
                throw std::exception();
            }

            Factory* it(factories.find(type_id_f<T>(typeid(T)))->second);

            void* value(it->GetAnyToInstance());
            T* instance(reinterpret_cast<T*>(value));

            return *instance;
        }
    };
}
#endif //! MOLE_INJECTION_H
