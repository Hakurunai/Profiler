#ifndef PROFILERDATANODE__H
#define PROFILERDATANODE__H

#include <vector>
#include <string>
#include "TimerEntry.h"

#include "Definitions.h"

struct SProfilerDataNode
{
	static SProfilerDataNode* CreateFirstNode(const std::string name)  
	{
		auto node = new SProfilerDataNode(name);
		node->mTimerData.AddCount();
		return node;
	};

	
	SProfilerDataNode(SProfilerDataNode* const parent, const std::string name) : mParent(parent), mName(name) {}
	~SProfilerDataNode() = default;


	FORCEINLINE SProfilerDataNode* const GetParent() const { return mParent; }
	FORCEINLINE std::string const GetName() const { return mName; }

	SProfilerDataNode* AddChildNode(std::string name)
	{
		//if exist, update call entry
		for (auto& childNode : mChildNodes)
		{
			// TODO : comparing two string is not really efficient, we could hash it to improve that part
			if (childNode.GetName().compare(name) == 0)
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
	SProfilerDataNode(const std::string name) : mName(name) {}

	std::vector<SProfilerDataNode> mChildNodes;
	SProfilerDataNode* mParent{ nullptr };
	const std::string mName;
};

#endif // PROFILERDATANODE__H