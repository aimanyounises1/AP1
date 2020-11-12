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
	currnetI = -1;
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
		lines.insert(it + currentLine + 1, text);
		currentLine++;
		cout << "current addforward = " << currentLine << endl;
	}
	else
	{
		vector<string>::iterator it;
		it = lines.begin();
		lines.insert(it + currentLine, text);
		currentLine++;
		//currnetI++;
		cout << "currentline = " << currentLine << endl;
	}
}
void Document::e(string &txt)
{
	ifstream in;
	string name = txt.substr(2, txt.length());
	cout << "The string is = " << name << endl;
	in.open(name);
	string a;
	while (getline(in, a))
	{
		cout << a << endl;
		append(a);
	}
	in.close();
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
void Document::n()
{
	cout << currentLine << "	" << lines[currentLine - 1] << endl;
}

void Document::i()
{
	if (currentLine == 0)
	{
		currentLine = 0;
	}
	else
	{
		currentLine--;
	}

	addForward = false;
}
void Document::append(string &push)
{
	cout << currentLine << endl;
	lines.insert(lines.begin() + currentLine , push);
	currentLine++;
}
void Document::d()
{
	//currentLine--;
	cout << lines[currentLine] << endl;
	lines.erase(lines.begin() + currentLine);
	currentLine--;
}

void Document::c()
{
	d();
	a();
}
void Document::dollar()
{
	currentLine = lines.size() - 1;
	cout << "currenline is" << currentLine << endl;
}
void Document::a()
{
	
	addForward = true;
}

void Document::num(int number)
{
	if (lines.empty())
	{
		cout << "?" << endl;
	}
	else
	{
		currentLine = number - 1;
		cout << "CurrentLine is =" << currentLine << endl;
		while (currentLine > lines.size())
		{
			lines.push_back("");
		}

		cout << lines[currentLine] << endl;
	}
}
void Document::num2(int move)
{
	if (move > 0 && currentLine + move < lines.size())
	{

		currentLine += move;
	}

	if (move < 0 && currentLine + move < lines.size())
	{
		currentLine += move;
	}
	cout << "current line is = " << currentLine << endl;
	cout << lines[currentLine] << endl;
}

// look for the text
void Document::slesh_text(string text)
{

	bool ok = false;
	for (int i = currentLine; i <= lines.size(); i++)
	{
		size_t found = lines[i].find(text);
		if (found != string::npos)
		{
			currentLine = i;
			ok = true;
			break;
		}
	}
	if (!ok)
	{
		for (int i = 0; i <= currentLine; i++)
		{
			size_t found = lines[i].find(text);
			if (found != string::npos)
			{
				currentLine = i;
				ok = true;
			}
		}
	}
	if (ok)
	{
		cout << lines[currentLine] << endl;
	}
}

void Document::s_slech_old_new(string oldText, string newText)
{
	cout << "current line is" << currentLine << endl;
	replace(lines[currentLine], oldText, newText);
	cout << lines[currentLine] << endl;
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
// this function used to add new lines to editor from another file
void Document::j()
{
	if (currentLine >= 0)
	{
		string a = lines[currentLine] + " " + lines[currentLine + 1];
		cout << "The new string is " << a << endl;
		lines.erase(lines.begin() + currentLine + 1);
		currentLine = --currentLine;
		lines.erase(lines.begin() + currentLine + 1);
		lines.insert(lines.begin() + currentLine + 1, a);
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
