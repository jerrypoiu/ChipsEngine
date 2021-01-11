#ifndef CHIPSSYSTEM_BASICFRAME_IENGINEFRAME_H
#define CHIPSSYSTEM_BASICFRAME_IENGINEFRAME_H

namespace ChipsEngine
{
	class Application;
	class Scene;
	class GameObject;
	class Sensor;

	/*
	������ �⺻ ���븦 �̷�� ���� ����  �������� Ŭ�����Դϴ�.
	����ڰ� ���� ������ ��Ȳ�� �����ϴ�.
	*/
	class IEngineFrame abstract
	{
		friend class Application;
		friend class Scene;
		friend class GameObject;
		friend class Sensor;
	private:
		// ������Ʈ�� �����ǰ�, �� �� �� ȣ��Ǵ� �Լ�
		virtual VOID _Awake_() abstract;
		// �� �����Ӹ��� �� ���� ȣ��Ǵ� �Լ�
		virtual VOID _Update_() abstract;
		// ���� ������ ������Ʈ �ֱ⸶�� �� ���� ȣ��Ǵ� �Լ�
		virtual VOID _FixedUpdate_() abstract;
		// �� �����Ӹ��� �� ���� ȣ��Ǵ� �Լ�, �������� ���� �ҷ�����, ���� ����ڰ� ���� �Լ��� Override�� ���� ����.
		virtual VOID _Render_() abstract;
		//��ü�� �Ҹ��� �� ȣ��Ǵ� �Լ�, ����� ���� �Ҹ��� �̸� ��������� �޸� ������ ���⼭ ó���ؾ� ��
		virtual VOID _Release_() abstract;
	private:
		//������ �浹�� ���� �� �� ȣ��Ǵ� �Լ�
		virtual VOID OnCollisionEnter(GameObject* _coll);
		//������ �浹�� ���� �� �� ȣ��Ǵ� �Լ�
		virtual VOID OnCollisionStay(GameObject* _coll);
		//������ �浹�� ���� �� ȣ��Ǵ� �Լ�
		virtual VOID OnCollisionExit(GameObject* _coll);
		//Ʈ���� �浹�� ���� �� �� ȣ��Ǵ� �Լ�
		virtual VOID OnTriggerEnter(GameObject* _coll);
		//Ʈ���� �浹�� ���� �� �� ȣ��Ǵ� �Լ�
		virtual VOID OnTriggerStay(GameObject* _coll);
		//Ʈ���� �浹�� ���� �� ȣ��Ǵ� �Լ�
		virtual VOID OnTriggerExit(GameObject* _coll);
	};
}

#endif //CHIPSSYSTEM_BASICFRAME_IENGINEFRAME_H
