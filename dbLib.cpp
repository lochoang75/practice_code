/*
 * =========================================================================================
 * Name        : dbLib.cpp
 * Author      : Duc Dung Nguyen, Nguyen Hoang Minh
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Fall 2017
 *               This file implements functions used for database management
 * =========================================================================================
 */

#include "dbLib.h"

#include <time.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

using namespace std;

void    strPrintTime(char* des, time_t& t) {
    tm *pTime = gmtime(&t);
    strftime(des, 26, "%Y-%m-%d %H:%M:%S", pTime);
}

void loadNinjaDB(char* fName, L1List<NinjaInfo_t> &db) {
	ifstream inFile(fName);
        
    if (inFile) {
        string line;
        NinjaInfo_t ninja;
        int i=0;
        while (getline(inFile , line)) {
            if(i==0){
                cin.clear();
                i++;
            }
            else{
                // remove \r
                 if (line[line.length() - 1] == '\r')
                    line.erase(line.length() - 1);
                 if (line.length() > 0) {
                    if (parseNinjaInfo((char*)line.data(), ninja))
                             db.insertHead(ninja);
            }
            }
        }
        db.reverse();
        inFile.close();
    }
    else {
        cout << "The file is not found!";
    }
}

bool parseNinjaInfo(char* pBuf, NinjaInfo_t& nInfo) {
   char    subStr[64];
    int     i = 0, j = 0;
    int     counter = 0;
    while (pBuf[j]) {
        if (pBuf[j] == ',') {
            switch (counter) {
                case 2:
                    strncpy(nInfo.id, pBuf + i, j - i);
                    nInfo.id[j - i] = '\0';
                    break;
                case 1:
                {
                    int hh, mm, ss, dd, mth, yy;
                    strncpy(subStr, pBuf + i, j - i);
                    subStr[j - i] = '\0';
                    struct tm when = {0};
                    sscanf(subStr, "%d/%d/%d %d:%d:%d", &dd, &mth, & yy, &hh, &mm, &ss);
                    when.tm_mday = dd;
                    when.tm_mon = mth-1;
                    when.tm_year = yy-1900;
                    when.tm_hour = hh;
                    when.tm_min = mm;
                    when.tm_sec = ss;
                    time_t converted;
                    converted = mktime(&when);
                    nInfo.timestamp=converted;
                    break;
                }
                case 3:
                    strncpy(subStr, pBuf + i, j - i);
                    subStr[j - i] = '\0';
                    nInfo.longitude = atof(subStr);// longitude
                    break;
                case 4:
                    strncpy(subStr, pBuf + i, j - i);
                    subStr[j - i] = '\0';
                    nInfo.latitude = atof(subStr);// latitude
                    break;
            }
            counter++;
            i = j + 1;
        }
        j++;
    }
    return true;
}


void process(L1List<ninjaEvent_t>& eventList, L1List<NinjaInfo_t>& bList) {
    while (!eventList.isEmpty()) {
        if(!processEvent(eventList[0], bList))
            cout << eventList[0].code << " is an invalid event\n";
        eventList.removeHead();
    }
}

void printNinjaInfo(NinjaInfo_t& b) {
    printf("%s: (%0.5f, %0.5f), %s\n", b.id, b.longitude, b.latitude, ctime(&b.timestamp));
}

/// This function converts decimal degrees to radians
double deg2rad(double deg) {
    return (deg * pi / 180);
}

///  This function converts radians to decimal degrees
double rad2deg(double rad) {
    return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u = sin((lat2r - lat1r)/2);
    v = sin((lon2r - lon1r)/2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}