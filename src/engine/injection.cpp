module;

#include <cstdint>
#include <map>
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <exception>
#include <any>

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

		virtual std::any& GetValue(id_capacity id = 0) = 0;
	};

	template<typename T, typename ...TArguments>
	class UniqueFactory : public Factory
	{
		std::vector<std::any> instances;
		const std::function<T()> functor;
	public:
		UniqueFactory() :
			UniqueFactory { []{ return T{}; } }
		{
		}
		UniqueFactory(std::function<T()>&& instancer) :
			functor{ std::move(instancer) }
		{
		}
		~UniqueFactory() override = default;

		std::any& GetValue(id_capacity id = 0) override
		{
			return instances.emplace_back(std::make_any<T>(functor()));
		}
	};

	template<typename T>
	class SharingFactory : public Factory
	{
		std::map<id_capacity, T> instances;
		const std::function<T()> functor;
	public:
		SharingFactory(std::function<T()> functor) :
			instances{},
			functor{ functor },
			Factory{}
		{
		}

		~SharingFactory() override {}

		std::any GetValue(id_capacity id = 0) override
		{
			if (!instances.count(id))
			{
				instances.emplace(id, functor());
			}

			return std::any{ *instances[id] };
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

		template<typename TInterface, typename TConcrete, typename ...TArguments>
		void BindUnique()
		{
			size_t id { typeid(TInterface).hash_code() };
			factories[id] = { std::make_unique<UniqueFactory<TInterface>>() };
		}
		
		template<typename TInterface, typename TConcrete, typename ...TArguments>
		void BindUnique(std::function<TInterface()>&& functor)
		{
			size_t id { typeid(TInterface).hash_code() };
			factories[id] = { std::make_unique<UniqueFactory<TInterface>>(std::move(functor)) };
		}

		template<typename TInterface, typename TConcrete, typename ...TArguments>
		void BindShared()
		{
			size_t id { typeid(TInterface).hash_code() };
			factories[id] = { std::make_unique<SharingFactory<TInterface>>() };
			/*
			   BindShared<TInterface>(std::make_shared<TConcrete>(InjectSharedInstance<TArguments>()...));


			   factories[id] = {
			   std::make_unique<SharingFactory<TInterface>>( [] { return std::move( std::make_unique<TConcrete>()); })
			   };
			   */

		}

		template<typename T, typename ... TArguments>
		T& Inject(size_t id = 0)
		{
			Factory& factory{ *factories[typeid(T).hash_code()].get() };

			std::any& value{ factory.GetValue() };

			return std::any_cast<T&>(value);
		}
	};
}

