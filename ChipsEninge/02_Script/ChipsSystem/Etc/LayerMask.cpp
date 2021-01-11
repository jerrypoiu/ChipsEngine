#include "ChipsSystem/Etc/LayerMask.h"

namespace ChipsEngine
{
	map<string, PxU32> LayerMask::m_layerMask;
	map<PxU32, PxU32>  LayerMask::m_collisionLayerSetting;
}