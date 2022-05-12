/*
Author: Akanksha Pardeshi and Tanay Rajwal
Program Language: C++
Program Work: Dictionary implementation Using Tries

Advanced Data Structures: Course Project

*/


#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

//Structure declaring the basic things required for the tree
struct TrieNode
{
	TrieNode *edge[26];
	char meaning[50];
	bool End_word;
};

//Class consisting of all the functionality declarations required for the Dictionary
class Dictionary
{
public:
	TrieNode *root;
	void insert(string, char[]);
	bool search(string);
	bool search1(string);
	bool isLast(TrieNode*);
	void suggestions(TrieNode*, string, string);
	int Suggest(string query);
	void suggestions1(TrieNode*, string);
	int Suggest1(string query);
	TrieNode* remove(TrieNode*, string, int);
};

//Initializing count to 0
int count = 0;

//For creation of the new nodes/elements
TrieNode* create()
{
	TrieNode *node = new TrieNode; //Dynamic allocation of memory as required
	for (int i = 0; i < 26; i++)
		node->edge[i] = NULL;
	node->End_word = false;
	return node;
}

void Dictionary::insert(string key, char mean[50])
{
	TrieNode *node = root;
	int index;
	for (int i = 0; i < key.length(); i++)
	{
		index = key[i] - 'a';
		if (node->edge[index] == NULL)
			node->edge[index] = create();
		node = node->edge[index];
	}
	node->End_word = true;
	strcpy(node->meaning, mean);
}

//For searching of a word
bool Dictionary::search(string key)
{
	//Finding out the length of the word
	int length = key.length();
	TrieNode *node = root;
	for (int i = 0; i < length; i++)
	{
		int index = key[i] - 'a';
		if (!node->edge[index])
			return false;
		node = node->edge[index];
	}
	if (node != NULL && node->End_word)
		cout << "Meaning of word  " << key << " is " << node->meaning;
	return (node != NULL && node->End_word);
}

bool Dictionary::isLast(TrieNode* root)
{
	for (int i = 0; i < 26; i++)
		if (root->edge[i])
			return 0;
	return 1;
}

void Dictionary::suggestions(TrieNode* root, string current, string gen)
{
	if (root->End_word)
	{
		cout << gen;
		cout << endl;
	}
	if (isLast(root))
		return;
	string temp;
	for (int i = 0; i < 26; i++)
	{
		temp = gen;
		if (root->edge[i])
		{
			current.push_back(97 + i);
			gen.push_back(97 + i);
			suggestions(root->edge[i], current, gen);
		}
		gen = temp;
	}

}

int Dictionary::Suggest(string query)
{
	struct TrieNode* node = root;
	int i;
	int n = query.length();
	for (i = 0; i < n; i++)
	{
		int index = query[i] - 'a';
		if (!node->edge[index])
			return 0;
		node = node->edge[index];
	}
	bool isWord;
	if (node->End_word == true)
		isWord = node->End_word;
	bool isLast_word = isLast(node);
	if (isWord && (isLast_word == 1))
	{
		cout << query << endl;
		return -1;
	}

	if (isLast_word == 0)
	{
		string prefix = query;
		string gen = query;
		suggestions(node, prefix, gen);
	}

}

void Dictionary::suggestions1(TrieNode* root, string current)
{
	if (root->End_word)
		count++;

	if (isLast(root))
		return;
	for (int i = 0; i < 26; i++)
	{
		if (root->edge[i])
		{
			current.push_back(97 + i);
			suggestions1(root->edge[i], current);
		}
	}

}

int Dictionary::Suggest1(string query)
{
	TrieNode* node = root;
	int i;
	int n = query.length();
	for (i = 0; i < n; i++)
	{
		int index = query[i] - 'a';
		if (!node->edge[index])
			return 0;

		node = node->edge[index];
	}
	bool isWord = (node->End_word == true);
	bool isLast_word = isLast(node);
	if (isWord && isLast_word)
	{
		cout << query << endl;
		return -1;
	}

	if (!isLast_word)
	{
		string prefix = query;
		suggestions1(node, prefix);
	}

}

bool isEmpty(TrieNode* root)
{
	for (int i = 0; i < 26; i++)
		if (root->edge[i])
			return false;
	return true;
}

TrieNode* Dictionary::remove(TrieNode* root, string key, int depth = 0)
{
	if (root == NULL)
		return NULL;

	if (depth == key.size())
	{
		if (root->End_word)
			root->End_word = false;
		if (isEmpty(root))
		{
			delete (root);
			root = NULL;
		}
		return root;
	}
	int index = key[depth] - 'a';
	root->edge[index] = remove(root->edge[index], key, depth + 1);
	if (isEmpty(root) && root->End_word == false)
	{
		delete (root);
		root = NULL;
	}
	return root;
}

bool Dictionary::search1(string key)
{
	int length = key.length();
	TrieNode *node = root;
	for (int i = 0; i < length; i++)
	{
		int index = key[i] - 'a';
		if (!node->edge[index])
			return false;
		node = node->edge[index];
	}

	if (node != NULL && node->End_word)
		cout << key << endl;
	return (node != NULL && node->End_word);
}

int main()
{
	cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ADS COURSE PROJECT^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << "\n";
	cout << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~Dictionary Implementation using Trie~~~~~~~~~~~~~~~~~~~~~~" << "\n";
	Dictionary d;
	string gen;
	d.root = create();
	string word;
	char mean[50];

	//Inserting some default words into the Trie
	d.insert("band", "a group of people or animals");
	d.insert("bandage", "a covering that protects injury");
	d.insert("bang", "to hit");
	d.insert("bankrupt", "unable to pay debts");
	d.insert("barn", "storehouse on a field");
	d.insert("hault", "to stop");
	d.insert("dog", "an animal");
	d.insert("barber", "a person who cut hair");
	d.insert("balance", "stable");
	d.insert("hasten", "move fast");
	d.insert("havoc", "violent");
	d.insert("amiable", "diffusing warmth");
	d.insert("gallant", "brave");
	d.insert("gist", "summary");
	d.insert("saturate", "infuse");
	d.insert("sedentary", "little activity");
	d.insert("bbbe", "qwerty");
	d.insert("bbbb", "dasdfgh");
	d.insert("ba", "zxcvb");
	d.insert("bab", "qwe");
	d.insert("hopeful", "hopeful");
	d.insert("hope", "hope");
	d.insert("hop", "pwq");
    d.insert("ho","asd hgh");
	cout << endl;
	char ans = 'y';
	int ch = 1, choice, a; bool s; int c, len = 0, i;
	char mini[50];

	do
	{
		count = 0;
		cout << "1. Insert \n2. Search  \n3. AutoComplete  \n4. Total words stored starting from an alphabet  \n5. Remove " << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1: cout << "Enter word:  "; cin >> word;
			cout << "Enter meaning:  ";
			scanf(" %[^\n]s", mean);
			d.insert(word, mean);
			break;
		case 2: cout << "Enter word to be searched:"; cin >> word;
			s = d.search(word);
			if (s == false)
			{
				cout << "Are you searching from any of the following: " << endl;
				len = word.length();
				for (i = 0; i < len - 1; i++)
					mini[i] = word[i];
				mini[i] = '\0';
				// cout<<"mini= "<<mini<<endl;
				d.search1(mini);
				for (i = 0; i < len - 2; i++)
					mini[i] = word[i];
				mini[i] = '\0';
				//cout<<"mini= "<<mini<<endl;
				d.search1(mini);
				d.Suggest(word);
			}
			break;
		case 3: cout << "Enter incomplete word: ";
			cin >> word;
			cout << "Suggestions for auto complete: ";
			c = d.Suggest(word);
			if (c == 0 || c == -1)
				cout << "Sorry, no string found with this prefix" << endl;
			break;
		case 4: cout << "Enter an alphabet:  ";
			cin >> word;
			c = d.Suggest1(word);
			if (c == -1)
				cout << "No other strings found with this prefix\n";
			else if (c == 0)
				cout << "No string found with this prefix\n";
			else
				cout << "Total number: " << count << endl;
			break;
		case 5: cout << "Enter word to be remove" << endl;
			cin >> word;
			d.root = d.remove(d.root, word, 0);
			break;
		}
		cout << "\n Do u want to continue?(y/n)  ";
		cin >> ans;
		cout << endl;
	} while (ans == 'y');

	cout << "Thank You!\n Always remember struggle precedes success, even in the dictionary";

	return 0;
}
