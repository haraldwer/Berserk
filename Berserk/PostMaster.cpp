#include "PostMaster.h"
#include "pch.h"

std::vector<Post> PostMaster::postList;

PostMaster::PostMaster()
{
}

PostMaster::~PostMaster()
{
}

Post PostMaster::RequestMessage(enum TYPE aMessageType)
{
	for (int i = 0; i < postList.size(); i++)
	{
		if (postList[i].messageType == aMessageType)
		{
			Post p = postList[i];
			postList.erase(postList.begin() + i);
			return p;
		}
	}
}

bool PostMaster::PostMessage(enum TYPE aMessageType, std::string aMessage)
{
	Post p = Post();
	p.message = aMessageType;
	p.messageType = aMessageType;
	postList.push_back(p);
	return true;
}
