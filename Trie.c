#include<string>
#include<unordered_map>

class Trie {
private:
	struct node {
		bool isWord;
		std::unordered_map<char, struct node*> next;
		node(bool flag) : isWord(flag) {}
		node() : isWord(false) {}
	};

	struct node* root;
	size_t size;
	
public:
	Trie() : root(new node), size(0) {}

	void add(std::string word) {
		struct node* cur = this->root;
		for (int i = 0; i < word.size(); ++i) {
			char c = word[i];
			if (cur->next.find(c) == cur->next.end()) 
				cur->next[c] = new node;
			cur = cur->next[c];
		}
		if (!cur->isWord) {
			cur->isWord = true;
			++ this->size;
		}
	}

	bool contains(std::string word) {
		struct node* cur = this->root;
		for (int i = 0; i < word.size(); ++i) {
			char c = word[i];
			if (cur->next.find(c) == cur->next.end())
				return false;
			cur = cur->next[c];
		}
		return cur->isWord;
	}

	bool prefix(std::string word) {
		struct node* cur = this->root;
		for (int i = 0; i < word.size(); ++i) {
			char c = word[i];
			if (cur->next.find(c) == cur->next.end())
				return false;
			cur = cur->next[c];
		}
		return true;
	}
};
