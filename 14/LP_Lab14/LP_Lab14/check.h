#pragma once
#include "stdafx.h"
#include "IT.h"
#include "LT.h"


namespace Check
{
	struct obl
	{
		char function[5];
		LT::LexTable lextab;
		IT::IdTable idtab;
	};
	bool testik(char* m, FST::FST fst);
	void insert(int line, char m);
	void Analiz(Parm::PARM parm, In::IN in);
};