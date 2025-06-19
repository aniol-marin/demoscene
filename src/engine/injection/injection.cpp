export module injection;

import std.compat;

namespace MoleDemo
{
	export class Container;
	struct Factory;
}

namespace MoleDemo
{
	using id_capacity = uint_fast8_t;
	using id_t = std::size_t;

	struct Factory
	{
		Factory() = default;
		virtual ~Factory() {};

		virtual std::any GetAnyToInstance(id_capacity id = 0) = 0;
	};

	template<typename I, typename T, typename ...TArguments>
	requires std::convertible_to<T, I>
	class UniqueFactory : public Factory
	{
		std::vector<std::unique_ptr<T>> instances;
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

		std::any GetAnyToInstance(id_capacity id = 0) override
		{
			return std::make_any<I*>(instances.emplace_back(std::make_unique<T>(functor())).get());
		}
	};

	template<typename I, typename T>
	class SharingFactory : public Factory
	{
		std::map<id_capacity, std::unique_ptr<T>> instances {};
		const std::function<T()> functor;
	public:
		SharingFactory() :
			SharingFactory { []{ return T{}; } }
		{
		}
		SharingFactory(std::function<T()>&& instancer) :
			functor{ std::move(instancer) }
		{
		}
		~SharingFactory() override {}


		std::any GetAnyToInstance(id_capacity id = 0) override
		{
			if (!instances.count(id))
			{
				instances.emplace(id, std::make_unique<T>(functor()));
			}

			return std::make_any<I*>( instances.at(id).get() );
		}
	};

	class Container
	{
		std::map<id_t, std::unique_ptr<Factory>> factories {};

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
		requires std::convertible_to<TConcrete, TInterface>
		void BindUnique()
		{
			id_t id { typeid(TInterface).hash_code() };
			factories[id] = { std::make_unique<UniqueFactory<TInterface, TConcrete>>() };
		}
		
		template<typename TInterface, typename TConcrete, typename ...TArguments>
		requires std::convertible_to<TConcrete, TInterface>
		void BindUnique(std::function<TConcrete()>&& functor)
		{
			id_t id { typeid(TInterface).hash_code() };
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
		requires std::convertible_to<TConcrete, TInterface>
		void BindShared()
		{
			id_t id { typeid(TInterface).hash_code() };
			factories[id] = { std::make_unique<SharingFactory<TInterface, TConcrete>>() };
		}

		template<typename TInterface, typename TConcrete, typename ...TArguments>
		requires std::convertible_to<TConcrete, TInterface>
		void BindShared(std::function<TConcrete()>&& functor)
		{
			id_t id { typeid(TInterface).hash_code() };
			factories[id] = { std::make_unique<SharingFactory<TInterface, TConcrete>>(std::move(functor)) };
		}

		template<typename T, typename ... TArguments>
		T& Inject(id_t id = 0)
		{
			auto it { factories.find(typeid(T).hash_code())}; 

			if (it == factories.end())
			{
				throw std::exception{};
			}

			std::any value { it->second->GetAnyToInstance() };
			auto* instance { std::any_cast<T*>(value) };

			return *instance;
		}
	};
}

