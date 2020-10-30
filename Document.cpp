#include <string>
#include <iostream>
#include <vector>
#include "Document.h"
using namespace std;
Document::Document(){
	currentLine = 0;
	addForward = false;
}

void Document::text(string text){
	if(!text.compare("."))
		return;
	//cout << "text!";
	if(addForward){
		vector<string>::iterator it;
		it = lines.begin();
		lines.insert (it+currentLine,text);
		currentLine++;
		
	}
	else{
		vector<string>::iterator it;
		it = lines.begin();
		lines.insert (it+currentLine-1,text);
		
	}
}

void Document::p(){
	cout << lines[currentLine-1] << endl;
}

void Document::prec_p(){
	for(int i =0; i< lines.size(); i++){
		cout << lines[i] << endl;
	}		
}

void Document::n(){
	cout << currentLine << "	" << lines[currentLine-1] << endl;
}


void Document::i(){
	addForward = false;
}

void Document::d(){
	lines.erase(lines.begin() + currentLine-1);
	currentLine--;
}

void Document::c(){
	d();
	a();
}


void Document::a(){
	addForward = true;
}

void Document::num(int number){
	currentLine = number;
	while(currentLine > lines.size()){
		lines.push_back("");
	}
	cout << lines[currentLine-1] << endl;
}


void Document::slesh_text(string text){
	bool ok = false;
	
	for(int i = currentLine-1; i< lines.size(); i++){
		size_t found = lines[i].find(text);
		if(found !=  string::npos){
			currentLine = i+1;
			ok = true;
			break;
		}
	}
	if(!ok){
		for(int i= 0; i< currentLine-1; i++){
			size_t found = lines[i].find(text);
			if(found !=  string::npos){
				currentLine = i+1;
				ok = true;
			}
		}	
	}
	if(ok){
		cout << lines[currentLine-1] << endl;
	}
}

void Document::s_slech_old_new(string oldText, string newText){
	replace(lines[currentLine-1], oldText, newText);
}

//replace 'from' in str into 'to'
bool Document::replace(string& str, const string& from, const string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}
