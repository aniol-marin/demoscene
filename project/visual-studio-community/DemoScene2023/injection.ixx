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
	std::map<uint8_t, std::unique_ptr<IFactory>> sharingFactories;
	std::map<uint8_t, std::unique_ptr<IFactory>> singletonFactories;

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
		const std::map < uint8_t, std::shared_ptr<T>> instances;//TODO make IDd instances
		const std::function<std::shared_ptr<T>()> functor;
	public:
		SharedFactory(std::function<std::shared_ptr<T>()> functor, uint8_t id = 0) :
			instances{ { id, functor() } },
			functor{ functor }, // shouldn't be necessary to keep it after use
			IFactory{} {}
		~SharedFactory() override {}

		std::shared_ptr<T> GetSharedObject(uint8_t id = 0) {
			return  std::make_shared(instances[id]);
		}
	};

	// Register one instances of an object (needs functor)
	template<typename TInterface>
	void BindShared(std::shared_ptr<TInterface> t) {
		sharingFactories[typeid(TInterface).hash_code()] = std::make_unique<SharedFactory<TInterface>>([=] {return t; });
	}

	// Register one instances of an object (needs functor)
	template<typename TInterface>
	void BindUnique(std::unique_ptr<TInterface> t) {
		sharingFactories[typeid(TInterface).hash_code()] = std::make_unique<UniqueFactory<TInterface>>([&] {return std::move(t); });
	}

	template<typename TInterface, typename ...TS>
	void RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)> functor) {
		sharingFactories[typeid(TInterface).hash_code()] = std::make_unique<SharedFactory<TInterface>>([=] {return functor(InjectShared<TS>()...); });
	}
	/*
	// Register one instances of an object (no functor)
	template<typename T>
	void Bind() {
		sharingFactories[typeid(T)] = std::make_shared<Factory<T>>([=] {return std::make_shared<T>(); });
	}

	// Supply a function pointer
	template<typename TInterface, typename ...TS>
	void RegisterFunctor(std::shared_ptr<TInterface>(*functor)(std::shared_ptr<TS> ...ts)) {
		RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)>(functor));
	}

	*/

public:
	// Returns a unique pointer to a new instances
	template<typename T>
	std::unique_ptr<T> InjectUnique() {
		auto factoryBase = sharingFactories[typeid(T).hash_code()];
		auto factory = std::static_pointer_cast<UniqueFactory<T>>(factoryBase);
		return factory->GetSharedObject();
	}

	// Returns a shared pointer to a unique instances
	template<typename T>
	std::shared_ptr<T> InjectShared() {
		auto factoryBase = sharingFactories[typeid(T).hash_code()];
		auto factory = std::static_pointer_cast<SharedFactory<T>>(factoryBase);
		return factory->GetSharedObject();
	}

	// A factory that will provide the same instances per each request
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindUniqueFactory() {
		RegisterFunctor(std::function<std::unique_ptr<TInterface>(std::unique_ptr<TArguments> ...ts)>(
			[](std::unique_ptr<TArguments>...arguments) -> std::unique_ptr<TInterface> {
				return std::make_unique<TConcrete>(std::forward<std::unique_ptr<TArguments>>(arguments)...);
			})
		);
	}

	// A factory that will call the constructor, per instances required
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindSharedFactory() {
		RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TArguments> ...ts)>(
			[](std::shared_ptr<TArguments>...arguments) -> std::shared_ptr<TInterface> {
				return std::make_shared<TConcrete>(std::forward<std::shared_ptr<TArguments>>(arguments)...);
			})
		);
	}

	// A factory that will return one unique instances for every request
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindUnique() {
		BindUnique<TInterface>(std::make_unique<TConcrete>(Inject<TArguments>()...));
	};

	// A factory that will return the same instances to every request
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindShared() {
		BindShared<TInterface>(std::make_shared<TConcrete>(Inject<TArguments>()...));
	};
};