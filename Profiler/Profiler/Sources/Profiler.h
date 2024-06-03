#ifndef PROFILER__H
#define PROFILER__H

#include "Timer.h"
#include <map>
#include <string>
#include "TimerEntry.h"
#include "ProfilerDataNode.h"

class Profiler
{
public:

	Profiler(const Profiler& other) = delete;
	Profiler& operator=(const Profiler& other) = delete;

	static Profiler& Instance()
	{
		static Profiler instance;
		return instance;
	}

	std::unique_ptr<Timer> StartTimer(const char* name) 
	{
		if (mHeadNode == nullptr) [[unlikely]]
		{
				mHeadNode = SProfilerDataNode::CreateFirstNode(name);
				mCurrentNode = mHeadNode;
		}
		else
		{
			mCurrentNode = mCurrentNode->AddChildNode(name);
		}		
		mNodesCallStack.push_back(mCurrentNode);
		return std::make_unique<Timer>(*mCurrentNode); 
	}
	
	void TimerEndDelegate()
	{
		//a timer can still exist after StopFrame is called, so we avoid an error (he can still access his node)
		if (mNodesCallStack.size() <= 1) return;
		mNodesCallStack.pop_back();
		mCurrentNode = mCurrentNode->GetParent();
	};

	void StopFrame()
	{
		++mFrameNumber;

		//TODO : we store datas from one frame then we start another tree node -> we could potentially write our data on a file and clear it
		mFrameData.push_back(mHeadNode);
		mHeadNode = nullptr;
		mCurrentNode = nullptr;
		mNodesCallStack.clear();
	}

private :

	//assuming 120 fps : max(size_t) / (120 fps * 60 s/min * 60 min/h * 24 h/day * 365 day/year) = 4.8 * 10^9 years to be at max value and wrap around self
	size_t mFrameNumber{ 1 };

	SProfilerDataNode* mHeadNode{ nullptr };
	SProfilerDataNode* mCurrentNode{ nullptr };
	std::vector<SProfilerDataNode*> mNodesCallStack;
	std::vector<SProfilerDataNode*> mFrameData;

	void ComputeTotalFrameTime()
	{
	}

	Profiler() 
	{
		mNodesCallStack.reserve(8);
		mFrameData.reserve(1000);
	};

	~Profiler() 
	{
		PrintData();
		int index = mFrameData.size() - 1;
		while (index > 0)
		{
			delete mFrameData[index];
			--index;
		}
		mFrameData.clear();

		index = mNodesCallStack.size() - 1;
		while (index > 0)
		{
			delete mNodesCallStack[index];
			--index;
		}
		mNodesCallStack.clear();
	};

	void PrintData() const
	{
		if (mFrameData.size() <= 0) return;

		std::cout << "Frame number : " << mFrameNumber - 1 << "\n";
		for (const auto& data : mFrameData)
		{
			data->PrintData();
			std::cout << std::endl;
		}
	}
};

/*
Enregistrer les données dans un fichier plutôt que dans un vector -> éviter de surcharger la ram
Créer un outil pour visualiser les données sous forme de flame graph
Ajouter un graphique ayant la durée des frames sur le temps de l'application (visualiser les pics de performances)

SHA256 pour encoder les noms des fonctions, histoire d'avoir des identifiants plus rapide à comparer (pour compter le nombre d'appel de chaque fonctions)?
Ajouter une mesure de la mémoire utilisée pour les fonctions
*/

#endif // PROFILER__H