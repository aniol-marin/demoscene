module;

#include <map>
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <any>

export module injection;

/*
import <map>;
import <memory>;
import <functional>;
*/

namespace MoleDemo {

	// TO DO delete unnecessary wrapper
	template<typename T>
	struct AnyWrapper
	{
		T& value;

		AnyWrapper(T& any) :
			value { any }
		{
		}
	};

	struct Factory
	{
		virtual ~Factory() {};

		virtual std::any GetValue(uint8_t id = 0) = 0;
	};

	template<typename T>
	class UniqueFactory : public Factory {
		const std::function<T()> functor;
	public:
		UniqueFactory(std::function<T()> instancer) :
			functor{ instancer },
			Factory{} {}
		~UniqueFactory() override {}

		std::unique_ptr<T> GetUniqueObject() {
			return std::make_unique(functor());
		}
	};

	template<typename T>
	class SharingFactory :
		public Factory
	{
		std::map<uint8_t, std::unique_ptr<T>> instances;
		const std::function<std::unique_ptr<T>()> functor;

	public:
		SharingFactory(std::function<std::unique_ptr<T>()> functor) :
			instances{},
			functor{ functor },
			Factory{}
		{
		}

		~SharingFactory() override {}

		std::any GetValue(uint8_t id = 0) override
		{
			if (!instances.count(id)){
				instances.emplace(id, functor());
			}

			return std::any{ AnyWrapper{*instances[id].get()} };
		}
	};

	struct dummy{};
	template<typename T>
	class MockFactory :
		public Factory
	{
		public:
		MockFactory() :
			Factory{}
		{
		}

		~MockFactory() override {}

		std::any GetValue(uint8_t id = 0) override
		{
			return std::make_any<dummy>( dummy{} );
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
			std::cout << "[MOCK] Binding unique instances of type " << typeid(TInterface).name() << std::endl;
			size_t id { typeid(TInterface).hash_code() };
			//factories[id] = { std::make_unique<UniqueFactory<TInterface>>()
		}

		template<typename TInterface, typename TConcrete, typename ...TArguments>
		void BindShared()
		{
			std::cout << "[MOCK] Binding shared instances of type " << typeid(TInterface).name() << std::endl;
			size_t id { typeid(TInterface).hash_code() };
			factories[id] = {
				std::make_unique<MockFactory<TInterface>>()
			};
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
			Factory* factoryBase { factories[typeid(T).hash_code()].get() };
			auto* factory { dynamic_cast<SharingFactory<T>*>(factoryBase) };
			std::any value{ factory->GetValue(id) };

			auto wrapper = std::any_cast<AnyWrapper<T>>(&value);
			return wrapper->value;
		}
	};

}

/*
*/

/*
template<typename Interface>
class MoleDemo::TestSharingFactory : public Factory {
	std::map<uint8_t, std::unique_ptr<Interface>> instances;
	const std::function< std::unique_ptr<Interface>()> functor;
public:
	TestSharingFactory(std::function< std::unique_ptr<Interface>()> functor, uint8_t id = 0) :
		instances{},
		functor{ functor },
		Factory{} {}
	~TestSharingFactory() override {
	}

	Interface* GetSharedObject(uint8_t id = 0) {
		if (!instances.contains(id)) {
			instances[id] = std::move(functor());
		}
		Interface* instance = instances[id].get();
		return instance;
	}
};

template<typename Interface>
class MoleDemo::MockupSharingFactory : public Factory {
	std::vector<std::unique_ptr<Interface>> ownerships;
	Interface* instance;
public:
	MockupSharingFactory() :
		ownerships{},
		Factory{} {}
	~MockupSharingFactory() override {
	}

	void PushInstance(std::unique_ptr<Interface>&& instance, uint8_t id = 0) {

		this->instance = instance.get();
		ownerships.push_back(std::move(instance));
	}
	Interface* GetSharedObject(uint8_t id = 0) {
		return instance;
	}
};

template<typename Interface>
class MoleDemo::TestInstanceFactory : public Factory {
private:
	std::vector<std::unique_ptr<Interface>> instances;
	const std::function<std::unique_ptr<Interface>()> functor;
public:
	TestInstanceFactory(std::function<std::unique_ptr<Interface>()> functor, uint8_t id = 0) :
		functor{ functor },
		Factory{} {}
	~TestInstanceFactory() override {
	}

	Interface* GetObject(uint8_t _ = 0) {
		std::unique_ptr<Interface> instance = functor();
		instances.push_back(std::move(instance));
		return instance.get();
	}
};


class MoleDemo::Container {

*/
	/*
	std::map<uint8_t, std::unique_ptr<Factory>> newInstanceFactories; // UniqueFactories
	std::map<uint8_t, std::unique_ptr<Factory>> sharedInstancesFactories; // SharingFactories
	*/
/*
	std::map<size_t, std::unique_ptr<Factory>> testFactories;
	std::vector<std::unique_ptr<Factory>> mockOwnerships;
	std::map<size_t, Factory*> mockFactories;

*/
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

/*
public:
	/*
	// Returns a unique pointer to a new instance
	template<typename T>
	std::unique_ptr<T> InjectNewInstance() {
		Factory* base{ newInstanceFactories[typeid(T).hash_code()].get() };
		UniqueFactory<T>* factory{ static_cast<UniqueFactory<T>*>(base) };
		std::unique_ptr<T> instance{ factory->GetUniqueObject() };
		return std::move(instance);
	};
	*/

/*
	// Returns a shared pointer to a unique instances
	template<typename T>
	T* Inject(uint8_t id = 0) {
		Factory* factoryBase = testFactories[typeid(T).hash_code()].get();
		T* instance;

		TestSharingFactory<T>* factory = dynamic_cast<TestSharingFactory<T>*>(factoryBase);
		if (factory) {
			instance = factory->GetSharedObject(id);
		}
		else {

			if (mockOwnerships.size() > 0) {

				MockupSharingFactory<T>* mock = dynamic_cast<MockupSharingFactory<T>*>(mockFactories[typeid(T).hash_code()]);
				if (mock) {

					instance = mock->GetSharedObject(id);
				}
				else {

					TestInstanceFactory<T>* newFactory = static_cast<TestInstanceFactory<T>*>(factoryBase);
					instance = newFactory->GetObject(id);
				}
			}
			else {

				TestInstanceFactory<T>* newFactory = static_cast<TestInstanceFactory<T>*>(factoryBase);
				instance = newFactory->GetObject(id);
			}
		}

		return instance;
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
/*
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindSharingFactory() {}

	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindUniqueFactory() {}

	// A factory that will return the same instances to every request
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindShared() {

		size_t id = typeid(TInterface).hash_code();

		std::unique_ptr<Factory> factory =
			std::make_unique<TestSharingFactory<TInterface>>(
				[] {
					return std::move(
						std::make_unique<TConcrete>()
					);
				}
		);

		testFactories[id] = std::move(factory);
		//BindShared<TInterface>(std::make_shared<TConcrete>(InjectSharedInstance<TArguments>()...));
	};

	// A factory that will return the same instances to every request
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindSharedMockup() {

		size_t id = typeid(TInterface).hash_code();

		std::unique_ptr<Factory> factory =
			std::make_unique<MockupSharingFactory<TInterface>>(
				[] {
					throw;
				}
		);

		testFactories[id] = std::move(factory);
		//BindShared<TInterface>(std::make_shared<TConcrete>(InjectSharedInstance<TArguments>()...));
	};

	// A factory that will call the constructor, per instances required
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindUnique() {

		size_t id = typeid(TInterface).hash_code();

		std::unique_ptr<Factory> factory =
			std::make_unique<TestInstanceFactory<TInterface>>(
				[] {
					return std::move(
						std::make_unique<TConcrete>()
					);
				}
		);

		testFactories[id] = std::move(factory);
	};


	// Temporary dummy factory
	template<typename TInterface, typename TConcrete, typename ...TArguments>
	void BindSharedWithoutDefaultMockup() {

		size_t id = typeid(TInterface).hash_code();
		std::unique_ptr<Factory> factory = std::make_unique<MockupSharingFactory<TInterface>>();

		mockFactories[typeid(TInterface).hash_code()] = factory.get();
		mockOwnerships.push_back(std::move(factory));
	};


	// Temporarily hardcoding of dummy factory instances
	template<typename IInstance>
	void PushInstance(std::unique_ptr<IInstance>&& instance, uint8_t id = 0) {

		Factory* base = mockFactories[typeid(IInstance).hash_code()];

		MockupSharingFactory<IInstance>* factory = static_cast<MockupSharingFactory<IInstance>*>(base);
		factory->PushInstance(std::move(instance));
	}
};
*/
