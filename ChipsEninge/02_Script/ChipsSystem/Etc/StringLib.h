#ifndef CHIPSSYSTEM_ETC_STRINGLIB_H
#define CHIPSSYSTEM_ETC_STRINGLIB_H

#include <sstream>

namespace ChipsEngine
{
	/*
	Split 기능을 제공한다.
	*/
	class StringLib final
	{
	private:
		StringLib() = delete;
		~StringLib() = delete;
	public:
		static vector<string> Split(string _fullString, char _pattern = ',')
		{
			string attributeFullString = _fullString;
			string attributeString;
			vector<string> attributeStringVector;
	
			std::istringstream ss(_fullString);
			string stringBuffer;
			while (getline(ss, stringBuffer, _pattern))
			{
				attributeStringVector.push_back(stringBuffer);
			}

			return attributeStringVector;
		}
	};
}

#endif //CHIPSSYSTEM_ETC_STRINGLIB_H