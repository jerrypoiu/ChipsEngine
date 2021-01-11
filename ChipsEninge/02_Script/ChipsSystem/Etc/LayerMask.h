#ifndef CHIPSSYSTEM_ETC_LAYERMASK_H
#define CHIPSSYSTEM_ETC_LAYERMASK_H

namespace ChipsEngine
{
	/*
	���ο� ���̾� ����, ���̾� �̸��� ��Ʈ �÷��� ��ȯ ��� (���̾�� ��Ʈ �÷��׷�
	�����Ǿ� �ֽ��ϴ�.) �浹 ���̾ �����Ͽ�, ���̾�� �浹 ���� ���θ� ������ �� �ִ�.
	*/
	class LayerMask final
	{
	private:
		static map<string, PxU32> m_layerMask;
		static map<PxU32, PxU32> m_collisionLayerSetting;
	private:
		LayerMask() = delete;
		~LayerMask() = delete;
	public:
		static VOID SetCollisionLayer(string _name1, string _name2, bool _canCollision)
		{
			int layer1 = NameToLayer(_name1);
			int layer2 = NameToLayer(_name2);

			//���� Layer�� ����
			if (layer1 == 0|| layer2 == 0)
				return;

			if (_canCollision)
			{
				m_collisionLayerSetting[layer1] |= layer2;
				m_collisionLayerSetting[layer2] |= layer1;
			}
			else
			{
				m_collisionLayerSetting[layer1] &= ~layer2;
				m_collisionLayerSetting[layer2] &= ~layer1;
			}
		}

		static int IsCanCollision(PxU32 _layer1, PxU32 _layer2)
		{
			//���� Layer�� ����
			if (_layer1 == 0 || _layer2 == 0)
				return false;

			return (m_collisionLayerSetting[_layer1] & _layer2) || (m_collisionLayerSetting[_layer2] & _layer1);
		}

		static VOID CreateNewLayer(string _name)
		{
			if (m_layerMask.find(_name) != m_layerMask.end() || m_layerMask.size() >= 32)
				return;

			m_layerMask[_name] = 1 << m_layerMask.size();
			m_collisionLayerSetting[m_layerMask[_name]] = ~0;
		}

		static PxU32 NameToLayer(string _name)
		{
			if (m_layerMask.find(_name) == m_layerMask.end())
				return 0;

			return m_layerMask[_name];
		}

		static string LayerToName(PxU32 _layer)
		{
			for (auto it = m_layerMask.begin(); it != m_layerMask.end(); it++)
			{
				if (it->second == _layer)
				{
					return it->first;
				}
			}

			return "";
		}

		static vector<string> GetLayerNames()
		{
			vector<string> layers(m_layerMask.size());
			
			for (auto it = m_layerMask.begin(); it != m_layerMask.end(); it++)
			{
				layers.emplace_back(it->first);
			}

			return layers;
		}
	};
}

#endif//CHIPSSYSTEM_ETC_LAYERMASK_H