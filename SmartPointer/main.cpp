#include "main.h"

template<typename T>
using TinyRef = std::shared_ptr<T>;

template<typename T>
using TinyURef = std::unique_ptr<T>;

template<typename T>
using TinyWRef = std::weak_ptr<T>;

template<typename T, typename... Args>
constexpr std::shared_ptr<T> TinyShared(Args&& ... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template<typename T, typename... Args>
constexpr std::unique_ptr<T> TinyUnique(Args&& ... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T1, typename T2>
constexpr std::shared_ptr<T1> TinyStaticCast(const T2& pointer)
{
	return std::static_pointer_cast<T1>(pointer);
}

template<typename T1, typename T2>
constexpr std::shared_ptr<T1> TinyDynamicCast(const T2& pointer)
{
	return std::dynamic_pointer_cast<T1>(pointer);
}


#define TinyMove(x) std::move(x)

struct NodeList
{
	struct Node
	{
		~Node()
		{
			std::cout << index << "~Node" << std::endl;
		}

		int index;
		Node* preData;
		TinyURef<Node> nextData;
		NodeList* list;

		void removeSelf()
		{
			if (this->nextData)
			{
				this->nextData->preData = this->preData;
			}

			if (this->preData)
			{
				this->preData->nextData = TinyMove(this->nextData);
			}
			else
			{
				list->mRoot = TinyMove(this->nextData);
			}
		}
	};

	~NodeList()
	{
		while (mRoot)
		{
			auto next = TinyMove(mRoot->nextData);
			mRoot = TinyMove(next);
		}
	}

	void push(TinyURef<Node>& listener)
	{
		listener->list = this;
		if (mRoot)
		{
			mRoot->preData = listener.get();
			listener->nextData = TinyMove(mRoot);
			mRoot = TinyMove(listener);
		}
		else
		{
			mRoot = TinyMove(listener);
		}


		//std::cout << mRoot.use_count() << "|" << mBack.use_count() << std::endl;
	}

	TinyURef<Node> mRoot;
};


struct TestShared : std::enable_shared_from_this<TestShared>
{
	inline TinyRef<TestShared> getThis()
	{
		return this->shared_from_this();
	}
};



void test(const TinyRef<Test2>& ref)
{
	TinyWRef w(ref);
	if (auto p = w.lock())
	{
		p->show();
	}
}


struct Countor
{
	int x = 0;
};


int main()
{
	{
		std::unordered_map<std::string, Countor*> umap =
		{
			{"1", new Countor{1}},
			{"2", new Countor{2}},
			{"3", new Countor{3}},
			{"4", new Countor{4}}
		};

		auto temp = new Countor{ 6 };
		auto pair = umap.try_emplace("2", temp);
		std::cout << pair.first->second->x << std::endl;

	}

	{
		std::vector<int>m(10, 0);
		m[0] = 2;

		TinyURef<std::vector<TinyRef<TestShared>>> ooo = TinyUnique<std::vector<TinyRef<TestShared>>>();

		auto i2 = TinyShared<TestShared>();
		auto& test = ooo;

		test->push_back(TinyShared<TestShared>());
		test->push_back(i2);
		test->push_back(TinyShared<TestShared>());
		test->push_back(TinyShared<TestShared>());

		auto ithis = i2->getThis();
	}

	{
		NodeList list;

		NodeList::Node* m[3];

		for (int i = 0; i < 3; i++)
		{
			auto temp = TinyUnique<NodeList::Node>();
			temp->index = i;
			m[i] = temp.get();
			list.push(temp);
		}

		m[0]->removeSelf();

	}


	std::shared_ptr<Test2> s2 = TinyShared<Test2>();
	std::shared_ptr<Test1> s1 = s2;
	std::shared_ptr<ITest> is = s2;

	TinyWRef<Test2> pp;
	test(s2);

	pp = s2;

	is->show();
	s1->test();

	std::weak_ptr<Test2> ws = TinyStaticCast<Test2>(s1);
	std::weak_ptr<ITest> iws = TinyDynamicCast<ITest>(s1);

	if (auto p = iws.lock())
	{
		p->show();
	}


	std::unique_ptr<Test2> u2 = TinyUnique<Test2>();
	std::unique_ptr<Test2> u12 = TinyMove(u2);
	std::unique_ptr<Test1> u1 = TinyMove(u12);

	return 0;
}