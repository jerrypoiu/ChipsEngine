#ifndef CHIPSSYSTEM_ETC_SINGLETON_H
#define CHIPSSYSTEM_ETC_SINGLETON_H

namespace ChipsEngine
{
	/*
	Template Singleton �� ���� ���� �� �ֵ��� �⺻ Ŭ������ �����Ѵ�.
	*/
	template <typename T>
	class Singletone abstract
	{
	private:
		static T* m_instance;
	private:
		Singletone(const Singletone&) = delete;
		void operator=(Singletone&) = delete;
		Singletone(const Singletone&&) = delete;
		void operator=(Singletone&&) = delete;
	protected:
		Singletone() = default;
		virtual ~Singletone();
	public:
		static T* const GetInstance()
		{
			if (m_instance == nullptr)
			{
				m_instance = new T();
			}
			return m_instance;
		}
		static void Release()
		{
			if (m_instance != nullptr)
			{
				delete m_instance;
				m_instance = nullptr;
			}
		}
	};

	template <typename T>
	T* Singletone<T>::m_instance = nullptr;

	template<typename T>
	Singletone<T>::~Singletone()
	{}
}

#endif //CHIPSSYSTEM_ETC_SINGLETON_H