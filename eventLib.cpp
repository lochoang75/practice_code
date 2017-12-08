/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "eventLib.h"

/// NOTE: each event will be separated by spaces, or endline character
void loadEvents(char* fName, L1List<ninjaEvent_t> &eList) {
	 ifstream inFile(fName);

    if (inFile) {
        string line;
        while (getline(inFile , line)) {
            /// On Windows, lines on file ends with \r\n. So you have to remove \r
            if (line[line.length() - 1] == '\r')
                line.erase(line.length() - 1);
						if (line[line.length() - 1] == ';'&&line.length()==1){
								ninjaEvent_t e;
								e.code[0]='\0';
								eList.insertHead(e);
						}
						if (line[line.length() - 1] == ';')
		            line.erase(line.length() - 1);
            if (line == "") continue;
            istringstream iss(line);
            while (iss) {
                string sub;
                iss >> sub;
								if(sub[sub.length()-1]==';'){
									sub[sub.length()-1]='\0';
								}
                if (sub.length()) {
                    ninjaEvent_t __e(sub);
                    eList.insertHead(__e);
                }
            }
						if(line[line.length()-1]==' '){
							ninjaEvent_t e;
							e.code[0]='\0';
							eList.insertHead(e);
						}
        }
        eList.reverse();
        inFile.close();
    }
    else {
        cout << "The file is not found!";
    }
}
