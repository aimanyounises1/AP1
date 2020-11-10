#include <string>
#include <iostream>
#include <vector>
#include "Document.h"
#include <fstream>
#include <iterator>
using namespace std;
Document::Document()
{
	currentLine = 0;
	addForward = false;
}
void Document::text(string text)
{
	if (!text.compare("."))
		return;
	//cout << "text!";
	if (addForward)
	{
		vector<string>::iterator it;
		it = lines.begin();
		lines.insert(it + currentLine, text);
		currentLine++;
	}
	else
	{
		vector<string>::iterator it;
		it = lines.begin();
		lines.insert(it + currentLine - 1, text);
	}
}
//prints tha last line in vector
void Document::p()
{
	cout << lines[currentLine - 1] << endl;
}

//print all lines in vector
void Document::prec_p()
{
	for (int i = 0; i < lines.size(); i++)
	{
		cout << lines[i] << endl;
	}
}
// a pinter to the last line in vector plus the line it self
void Document::n()
{
	cout << currentLine << "	" << lines[currentLine - 1] << endl;
}

void Document::i()
{
	addForward = false;
}

void Document::d()
{
	lines.erase(lines.begin() + currentLine - 1);
	currentLine--;
}

void Document::c()
{
	d();
	a();
}

void Document::a()
{
	addForward = true;
}

void Document::num(int number)
{
	currentLine = number;
	while (currentLine > lines.size())
	{
		lines.push_back("");
	}
	cout << lines[currentLine - 1] << endl;
}
// look for the text
void Document::slesh_text(string text)
{
	bool ok = false;
	for (int i = currentLine - 1; i < lines.size(); i++)
	{
		size_t found = lines[i].find(text);
		if (found != string::npos)
		{
			currentLine = i + 1;
			ok = true;
			break;
		}
	}
	if (!ok)
	{
		for (int i = 0; i < currentLine - 1; i++)
		{
			size_t found = lines[i].find(text);
			if (found != string::npos)
			{
				currentLine = i + 1;
				ok = true;
			}
		}
	}
	if (ok)
	{
		cout << lines[currentLine - 1] << endl;
	}
}

void Document::s_slech_old_new(string oldText, string newText)
{
	replace(lines[currentLine - 1], oldText, newText);
}

//replace 'from' in str into 'to'
bool Document::replace(string &str, const string &from, const string &to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}
void Document::j()
{
	if (currentLine > 1)
	{
		string a = lines[currentLine] + lines[currentLine + 1];
		lines.erase(lines.begin() + currentLine - 1);
		currentLine = --currentLine;
		lines.erase(lines.begin() + currentLine - 1);
		lines.insert(lines.begin() + currentLine - 1, a);
	}
}
void Document::w(string &out)
{
	ofstream output;
	output.open(out);
	ostream_iterator<string> output_file(output, "\n");
	vector<string>::iterator it;
	it = lines.begin();
	vector<string>::iterator it2;
	it2 = lines.end();
	copy(it, it2, output_file);
	output.close();
}
vector<string> split(string str, char splitBy)
{
	vector<string> words;
	string word = "";
	for (auto x : str)
	{
		if (x == splitBy)
		{
			words.push_back(word);
			word = "";
		}
		else
		{
			word = word + x;
		}
	}
	words.push_back(word);
	return words;
}
