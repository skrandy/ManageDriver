#pragma once
#define SER_NAME "TestDriver"
#define SER_POSITION "C:\\Users\\test\\Desktop\\TestDriver.sys"
#include<iostream>
#include<string>
#include<stdio.h>
#include<Windows.h>
bool CreateServe();
bool StartServe();
bool StopServe();
bool DeleteServe();
using namespace std;
SC_HANDLE hSCM = NULL;
SC_HANDLE hSer = NULL;