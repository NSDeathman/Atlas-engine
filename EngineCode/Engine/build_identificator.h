////////////////////////////////////////////////////////////////////////////////
// Created: 14.01.2025
// Author: ChatGPT, NS_Deathman
// New Build Identification Code Generator
////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <string>
#include <random>
////////////////////////////////////////////////////////////////////////////////
// Constants for build identification
static const char* monthNames[12] = 
{
	"Jan", 
	"Feb", 
	"Mar", 
	"Apr", 
	"May", 
	"Jun",
	"Jul", 
	"Aug", 
	"Sep", 
	"Oct", 
	"Nov", 
	"Dec"
};

static const int daysInMonth[12] = 
{
	31, 
	28, 
	31, 
	30, 
	31, 
	30, 
	31, 
	31, 
	30, 
	31, 
	30, 
	31
};

// Starting point for the build ID computation
static const int startDay = 15;
static const int startMonth = 1;
static const int startYear = 2025;
////////////////////////////////////////////////////////////////////////////////
extern void PrintBuildData();
////////////////////////////////////////////////////////////////////////////////
