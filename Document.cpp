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
		cout << "the line number is = " << currentLine << endl;
	}
	else
	{
		vector<string>::iterator it;
		it = lines.begin();
		lines.insert(it + currentLine, text);
		currentLine++;
		cout << "the line number is = " << currentLine << endl;
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
void Document::n()
{
	cout << currentLine << "	" << lines[currentLine - 1] << endl;
}

void Document::i()
{

	addForward = false;
}
void Document::append(string &push) {
	lines.insert(lines.begin()+ currentLine , push);
	currentLine++;
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
	cout<< "CurrentLine is =" <<currentLine<<endl;
	while (currentLine > lines.size())
	{
		lines.push_back("");
	}
	cout << lines[currentLine - 1] << endl;
}
void Document::num2(int move)
{
	if (currentLine + move < lines.size())
	{
		currentLine += move;
	}
	cout << "CurrentLine is = "<<currentLine <<endl;
}
// look for the text
void Document::slesh_text(string text)
{
	int current = currentLine;
	bool ok = false;
	for (int i = current - 1  ; i < lines.size(); i++)
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
		for (int i = 0; i <= current - 1; i++)
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
// this function used to add new lines to editor from another file
void Document::e(ifstream &in) {

}
void Document::j()
{
	if (currentLine > 1)
	{
		string a = lines[currentLine - 1] + lines[currentLine ];
		cout << "The new string is " <<a <<endl;
		lines.erase(lines.begin() + currentLine );
		currentLine = --currentLine;
		lines.erase(lines.begin() + currentLine );
		lines.insert(lines.begin() + currentLine , a);
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
