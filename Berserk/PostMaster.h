#ifndef POST_MASTER
#define POST_MASTER

#include <string>
#include <vector>

struct Post
{
	enum TYPE messageType;
	std::string message;
};

class PostMaster
{
public:
	PostMaster();
	~PostMaster();
	static Post RequestMessage(enum TYPE aMessageType);
	static bool PostMessage(enum TYPE aMessageType, std::string aMessage);
	static enum messageTypes{ /* Add types here */ };
	
private:
	static std::vector<Post> postList;
};
#endif // !POST_MASTER
