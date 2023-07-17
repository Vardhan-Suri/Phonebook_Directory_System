#include <bits/stdc++.h>
using namespace std;

class TrieNode
{
    public:
	unordered_map<char,TrieNode*> child;

	bool isLast;

	TrieNode()
	{
		for (char i = 'a'; i <= 'z'; i++)
			child[i] = NULL;

		isLast = false;
	}
};

TrieNode *root = new TrieNode();

void insert(string s)
{
	int len = s.length();

	TrieNode *itr = root;
	for (int i = 0; i < len; i++)
	{
		TrieNode *nextNode = itr->child[s[i]];
		if (nextNode == NULL)
		{
			nextNode = new TrieNode();
			itr->child[s[i]] = nextNode;
		}

		itr = nextNode;

		if (i == len - 1)
			itr->isLast = true;
	}
}

void displayContactsUtil(TrieNode *curNode, string prefix)
{
	if (curNode->isLast)
		cout << prefix << endl;

	for (char i = 'a'; i <= 'z'; i++)
	{
		TrieNode *nextNode = curNode->child[i];
		if (nextNode != NULL)
			displayContactsUtil(nextNode, prefix + (char)i);
	}
}

void displayContacts(string str)
{
	TrieNode *prevNode = root;

	string prefix = "";
	int len = str.length();

	int i;
	for (i=0; i<len; i++)
	{
		prefix += (char)str[i];

		char lastChar = prefix[i];

		TrieNode *curNode = prevNode->child[lastChar];

		if (curNode == NULL)
		{
			cout << "No Results Found for"<< prefix
				<<endl;
			i++;
			break;
		}

		cout<<endl<<"Suggestions based on "<< prefix
			<<" are"<<endl;
		displayContactsUtil(curNode, prefix);

		prevNode = curNode;
	}

	for (; i<len; i++)
	{
		prefix += (char)str[i];
		cout << "No Results Found for "<< prefix
			<<endl;
	}
}

void insertIntoTrie(string contacts[],int n)
{
	root = new TrieNode();

	for (int i = 0; i < n; i++)
		insert(contacts[i]);
}

int main()
{
	string contacts[] = {"pranav" , "pranavkumar", "pranavkumarparihar", "preeti"};

	int n = sizeof(contacts)/sizeof(string);

	insertIntoTrie(contacts, n);

	string query = "pra";

	displayContacts(query);

	return 0;
}

