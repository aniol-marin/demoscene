export module injection;

import <map>;
import <memory>;
import <functional>;


class IFactory
{
public:
	IFactory() {}
	virtual ~IFactory() {};
};

export 	class Container {
	std::map<int, std::unique_ptr<IFactory>> factories;
	std::map<int, std::unique_ptr<IFactory>> singletonFactories;

	template<typename T>
	class UniqueFactory : public IFactory {
		const std::function<std::unique_ptr<T>()> functor;
	public:
		UniqueFactory(std::function<std::unique_ptr<T>()> functor) :
			functor{ functor },
			IFactory{} {}
		~UniqueFactory() override {}

		std::unique_ptr<T> GetUniqueObject() {
			return functor();
		}
	};

	template<typename T>
	class SharedFactory : public IFactory {
	private:
		const std::unique_ptr<T> instance;
		const std::function<std::unique_ptr<T>()> functor;
	public:
		SharedFactory(std::function<std::shared_ptr<T>()> functor) :
			instance{ make_unique(functor()) },
			functor{ functor }, // shouldn't be necessary to keep it after use
			IFactory{} {}
		~SharedFactory() override {}

		std::shared_ptr<T> GetSharedObject() {
			return std::make_shared(instance);
		}
	};

	/*
	// Register one instance of an object (needs functor)
	template<typename TInterface>
	void Bind(std::shared_ptr<TInterface> t) {
		factories[typeid(TInterface)] = std::make_shared<Factory<TInterface>>([=] {return t; });
	}
	// Register one instance of an object (no functor)
	template<typename T>
	void Bind() {
		factories[typeid(T)] = std::make_shared<Factory<T>>([=] {return std::make_shared<T>(); });
	}

	// Supply a function pointer
	template<typename TInterface, typename ...TS>
	void RegisterFunctor(std::shared_ptr<TInterface>(*functor)(std::shared_ptr<TS> ...ts)) {
		RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)>(functor));
	}

	template<typename TInterface, typename ...TS>
	void RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)> functor) {
		factories[typeid(TInterface).name()] = std::make_shared<Factory<TInterface>>([=] {return functor(Inject<TS>()...); });
	}
	*/

public:
	// Returns a unique pointer to a new instance
	template<typename T>
	std::unique_ptr<T> InjectUnique() {
		auto factoryBase = factories[typeid(T)];
		auto factory = std::static_pointer_cast<Factory<T>>(factoryBase);
		return factory->GetSharedObject();
	}

	// Returns a shared pointer to a unique instance
	template<typename T>
	std::shared_ptr<T> InjectShared() {
		auto factoryBase = factories[typeid(T)];
		auto factory = std::static_pointer_cast<Factory<T>>(factoryBase);
		return factory->GetSharedObject();
	}

	// A factory that will provide the same instance per each request
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindUniqueFactory() {
		RegisterFunctor(std::function<std::unique_ptr<TInterface>(std::unique_ptr<TArguments> ...ts)>(
			[](std::unique_ptr<TArguments>...arguments) -> std::unique_ptr<TInterface> {
				return std::make_unique<TConcrete>(std::forward<std::unique_ptr<TArguments>>(arguments)...);
			})
		);
	}

	// A factory that will call the constructor, per instance required
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindSharedFactory() {
		RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TArguments> ...ts)>(
			[](std::shared_ptr<TArguments>...arguments) -> std::shared_ptr<TInterface> {
				return std::make_shared<TConcrete>(std::forward<std::shared_ptr<TArguments>>(arguments)...);
			})
		);
	}

	// A factory that will return one unique instance for every request
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindUnique() {
		Bind<TInterface>(std::make_unique<TConcrete>(Inject<TArguments>()...));
	};

	// A factory that will return the same instance to every request
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindShared() {
		Bind<TInterface>(std::make_shared<TConcrete>(Inject<TArguments>()...));
	};
};