module;

#include <cstdint>
#include <map>
#include <memory>
#include <functional>
#include <exception>
#include <any>
#include <concepts>

export module injection;

/*
 import <map>;
 import <memory>;
 import <functional>;
 */

namespace MoleDemo
{

	using id_capacity = uint8_t;

	struct Factory
	{
		Factory() = default;
		virtual ~Factory() {};

		virtual std::any GetPointerToInstance(id_capacity id = 0) = 0;
	};

	template<typename I, typename T, typename ...TArguments>
	requires std::convertible_to<T, I>
	class UniqueFactory : public Factory
	{
		std::vector<std::unique_ptr<I>> instances;
		const std::function<I()> functor;
	public:
		UniqueFactory() :
			UniqueFactory { []{ return T{}; } }
		{
		}
		UniqueFactory(std::function<I()>&& instancer) :
			functor{ std::move(instancer) }
		{
		}
		~UniqueFactory() override = default;

		std::any GetPointerToInstance(id_capacity id = 0) override
		{
			return std::make_any<I*>(instances.emplace_back(std::make_unique<I>(functor())).get());
		}
	};

	template<typename T>
	class SharingFactory : public Factory
	{
		std::map<id_capacity, T> instances {};
		const std::function<T()> functor;
	public:
		SharingFactory() :
			SharingFactory { []{ return T{}; } }
		{
		}
		SharingFactory(std::function<T()> functor) :
			functor{ functor }
		{
		}
		~SharingFactory() override {}


		std::any GetPointerToInstance(id_capacity id = 0) override
		{
			if (!instances.count(id))
			{
				instances.emplace(id, functor());
			}

			return std::make_any<T*>( &instances[id] );
		}
	};

	export class Container
	{
		std::map<size_t, std::unique_ptr<Factory>> factories {};

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
		void BindUnique(std::function<T()>&& functor)
		{
			BindUnique<T, T>(std::move(functor));
		}

		template<typename TInterface, typename TConcrete, typename ...TArguments>
		void BindUnique()
		{
			size_t id { typeid(TInterface).hash_code() };
			factories[id] = { std::make_unique<UniqueFactory<TInterface, TConcrete>>() };
		}
		
		template<typename TInterface, typename TConcrete, typename ...TArguments>
		void BindUnique(std::function<TInterface()>&& functor)
		{
			size_t id { typeid(TInterface).hash_code() };
			factories[id] = { std::make_unique<UniqueFactory<TInterface, TConcrete>>(std::move(functor)) };
		}

		template<typename T>
		void BindShared()
		{
			BindShared<T,T>();
		}

		template<typename T>
		void BindShared(std::function<T()>&& functor)
		{
			BindShared<T,T>(std::move(functor));
		}

		template<typename TInterface, typename TConcrete, typename ...TArguments>
		void BindShared()
		{
			size_t id { typeid(TInterface).hash_code() };
			factories[id] = { std::make_unique<SharingFactory<TInterface>>() };
		}

		template<typename TInterface, typename TConcrete, typename ...TArguments>
		void BindShared(std::function<TInterface()>&& functor)
		{
			size_t id { typeid(TInterface).hash_code() };
			factories[id] = { std::make_unique<SharingFactory<TInterface>>(std::move(functor)) };
		}

		template<typename T, typename ... TArguments>
		T& Inject(size_t id = 0)
		{
			auto it { factories.find(typeid(T).hash_code())}; 

			if (it == factories.end())
			{
				throw std::exception{};
			}

			auto value { it->second->GetPointerToInstance() };
			auto* instance { std::any_cast<T*>(value) };

			return *instance;
		}
	};
}

