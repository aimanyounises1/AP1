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
void Document::init(ifstream &in)
{
	vector<string> v1;
	if (in.is_open())
	{
		string line;
		while (getline(in, line))
		{
		v1.push_back(line);
		}
		in.close();
	}
	for (string t : v1)
	{
		if (t == "q")
		{
			break;
		}
		cout << t << endl;
		handle(t);
	}
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

void Document::handle(string &line)
{
	//in case of 'a', 'i' or 'c', call "text" function, until '.' recived.
	static bool waitForDot = false;
	if (waitForDot)
	{
		text(line);
		if (!line.compare("."))
			waitForDot = false;
		return;
	}

	if (!line.compare("p"))
	{
		p();
		return;
	}
	if (!line.compare("n"))
	{
		n();
		return;
	}
	if (!line.compare("%p"))
	{
		prec_p();
		return;
	}
	if (!line.compare("a"))
	{
		waitForDot = true;
		a();
		return;
	}
	if (!line.compare("i"))
	{
		i();
		waitForDot = true;
		return;
	}
	if (!line.compare("c"))
	{
		waitForDot = true;
		c();
		return;
	}
	if (!line.compare("d"))
	{
		d();
		return;
	}
	if (line.at(0) == 'w' && line.at(1)==' ')
	{
		cout << "Hello i'm in" << endl;
		line = line.substr(2, line.length());
		w(line);
	}

	//check if the text is a number
	int num = 0;
	bool isAnumber;
	string s = line;
	try
	{
		num = stoi(s);
		isAnumber = true;
	}
	catch (std::invalid_argument const &e)
	{
		isAnumber = false;
	}
	catch (std::out_of_range const &e)
	{
		isAnumber = false;
	}
	if (isAnumber)
	{
		Document::num(num);
		return;
	}
	//empty text
	if (line.size() == 0)
	{
		text(line);
		return;
	}

	// '/text'
	if (line.at(0) == '/')
	{
		slesh_text(split(line, '/')[1]);
		return;
	}
	// 's/old/new/'
	if (line.at(0) == 's')
	{
		vector<string> arr = split(line, '/');
		if (arr.size() >= 3)
		{
			s_slech_old_new(arr[1], arr[2]);
			return;
		}
	}
}