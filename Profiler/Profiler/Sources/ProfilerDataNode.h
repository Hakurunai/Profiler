#ifndef PROFILERDATANODE__H
#define PROFILERDATANODE__H

#include <vector>
#include "TimerEntry.h"

#include "Definitions.h"

struct SProfilerDataNode
{
	static SProfilerDataNode* CreateFirstNode(const char* name)  
	{
		auto node = new SProfilerDataNode(name);
		return node;
	};
	
	SProfilerDataNode(SProfilerDataNode* const parent, const char* name) : SProfilerDataNode(name) { mParent = parent; }
	~SProfilerDataNode() = default;

	FORCEINLINE SProfilerDataNode* const GetParent() const { return mParent; }
	FORCEINLINE const char* const GetName() const { return mName; }

	SProfilerDataNode* AddChildNode(const char* name)
	{
		//if exist, update call entry
		for (auto& childNode : mChildNodes)
		{
			// TODO : comparing two string is not really efficient, we could hash it to improve that part
			if (strcmp(childNode.GetName(), name) == 0)
			{
				childNode.mTimerData.AddCount();
				return &childNode;
			}
		}
		//if not, create a new child node
		mChildNodes.emplace_back(this, name);
		return &(mChildNodes.back());
	}


	void PrintData(const int nbTab = 0) const
	{
		//creation of tabulation
		int tab = nbTab;
		std::string tabText;
		while (tab > 0)
		{
			tabText.append("\t");
			--tab;
		}

		std::cout << tabText << mName << " " << mTimerData.GetData();
		for (const auto& data : mChildNodes)
		{
			data.PrintData(nbTab + 1);
		}
	}

	STimerEntry mTimerData;

private :
	SProfilerDataNode(const char* name)
	{
		//currently we need to copy the content of the char* inside our char* 
		// -> when initial pointer is destroyed (out of scope) our local data remain valid
		mName = new char[strlen(name)+1];
		strcpy_s(mName, strlen(name) +1, name);
	}

	std::vector<SProfilerDataNode> mChildNodes;
	SProfilerDataNode* mParent{ nullptr };
	char* mName;
};

#endif // PROFILERDATANODE__H