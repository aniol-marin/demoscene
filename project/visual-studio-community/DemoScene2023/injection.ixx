export module injection;

import <map>;
import <memory>;
import <functional>;

class Factory
{
public:
	virtual ~Factory() {};
};
/*
template<typename T>
class UniqueFactory : public Factory {
	const std::function<std::unique_ptr<T>()> functor;
public:
	UniqueFactory(std::function<std::unique_ptr<T>()> instancer) :
		functor{ instancer },
		Factory{} {}
	~UniqueFactory() override {}

	std::unique_ptr<T> GetUniqueObject() {
		return functor();
	}
};

template<typename T>
class SharingFactory : public Factory {
private:
	const std::map < uint8_t, std::shared_ptr<T>> instances;//TODO make IDd instances
	const std::function<std::shared_ptr<T>()> functor;
public:
	SharingFactory(std::function<std::shared_ptr<T>()> functor, uint8_t id = 0) :
		instances{},
		functor{ functor },
		Factory{} {}
	~SharingFactory() override {}

	std::shared_ptr<T> GetSharedObject(uint8_t id = 0) {
		instances.insert({ id, functor() });
		return  std::make_shared(instances[id]);
	}
};
*/

template<typename Interface>
class TestSharingFactory : public Factory {
private:
	std::map<uint8_t, Interface*> instances;
	const std::function<Interface* ()> functor;
public:
	TestSharingFactory(std::function<Interface* () > functor, uint8_t id = 0) :
		instances{},
		functor{ functor },
		Factory{} {}
	~TestSharingFactory() override {
		for (const std::pair<uint8_t, Interface*>& pair : instances) {
			delete pair.second;
		}
	}

	Interface* GetSharedObject(uint8_t id = 0) {
		if (!instances.contains(id)) {
			instances[id] = functor();
		}
		Interface* instance = instances[id];
		return instance;
	}
};


export class Container {

	/*
	std::map<uint8_t, std::unique_ptr<Factory>> newInstanceFactories; // UniqueFactories
	std::map<uint8_t, std::unique_ptr<Factory>> sharedInstancesFactories; // SharingFactories
	*/
	std::map<uint8_t, Factory*> test; // SharingFactories

	/*
	// Register one instances of an object (needs instancer)
	template<typename TInterface>
	void BindShared(std::shared_ptr<TInterface> t) {
		sharedInstancesFactories[typeid(TInterface).hash_code()] = std::make_unique<SharingFactory<TInterface>>([&t] {return std::move(t); });
	}

	// Register one instances of an object (needs instancer)
	template<typename TInterface>
	void BindUnique(std::unique_ptr<TInterface> t) {
		newInstanceFactories[typeid(TInterface).hash_code()] = std::make_unique<UniqueFactory<TInterface>>([&] {return std::move(t); });
	}

	template<typename TInterface, typename ...TS>
	void RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)> functor) {
		newInstanceFactories[typeid(TInterface).hash_code()] = std::make_unique<SharingFactory<TInterface>>([=] {return functor(InjectSharedInstance<TS>()...); });
	}
	// Register one instances of an object (no instancer)
	template<typename T>
	void Bind() {
		newInstanceFactories[typeid(T)] = std::make_shared<Factory<T>>([=] {return std::make_shared<T>(); });
	}

	// Supply a function pointer
	template<typename TInterface, typename ...TS>
	void RegisterFunctor(std::shared_ptr<TInterface>(*instancer)(std::shared_ptr<TS> ...ts)) {
		RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TS> ...ts)>(instancer));
	}

	*/

public:
	/*
	// Returns a unique pointer to a new instances
	template<typename T>
	std::unique_ptr<T> InjectNewInstance() {
		Factory* base{ newInstanceFactories[typeid(T).hash_code()].get() };
		UniqueFactory<T>* factory{ static_cast<UniqueFactory<T>*>(base) };
		std::unique_ptr<T> instance{ factory->GetUniqueObject() };
		return std::move(instance);
	};
	*/

	// Returns a shared pointer to a unique instances
	template<typename T>
	T* InjectShared(uint8_t id = 0) {
		Factory* factoryBase = test[typeid(T).hash_code()];
		TestSharingFactory<T>* factory = static_cast<TestSharingFactory<T>*>(factoryBase);
		auto instance = factory->GetSharedObject(id);
		return static_cast<T*>(instance);
	};

	/*
	// Returns a shared pointer to a unique instances
	template<typename T>
	std::shared_ptr<T> InjectSharedInstance(uint8_t id = 0) {
		auto factoryBase = sharedInstancesFactories[typeid(T).hash_code()].get();
		auto factory = static_cast<SharingFactory<T>>(factoryBase);
		return factory->GetSharedObject();
	};
	// A factory that will provide the same instances per each request
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindNewInstancesFactory() {
		RegisterFunctor(std::function<std::unique_ptr<TInterface>(std::unique_ptr<TArguments> ...ts)>(
			[](std::unique_ptr<TArguments>...arguments) -> std::unique_ptr<TInterface> {
				return std::make_unique<TConcrete>(std::forward<std::unique_ptr<TArguments>>(arguments)...);
			})
		);
	}

	// A factory that will call the constructor, per instances required
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindSharingFactory() {
		RegisterFunctor(std::function<std::shared_ptr<TInterface>(std::shared_ptr<TArguments> ...ts)>(
			[](std::shared_ptr<TArguments>...arguments) -> std::shared_ptr<TInterface> {
				return std::make_shared<TConcrete>(std::forward<std::shared_ptr<TArguments>>(arguments)...);
			})
		);
	}

	// A factory that will return one unique instances for every request
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindUnique() {
		BindUnique<TInterface>(std::make_unique<TConcrete>(InjectSharedInstance<TArguments>()...));
	};
	*/

	// A factory that will return the same instances to every request
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindShared() {
		uint8_t id = typeid(TInterface).hash_code();
		Factory* factory = new TestSharingFactory<TInterface>([] {return new TConcrete{}; });
		test[id] = factory;
		//BindShared<TInterface>(std::make_shared<TConcrete>(InjectSharedInstance<TArguments>()...));
	};
};;