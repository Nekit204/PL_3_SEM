#include"It.h"
#include"stdafx.h"
#include"Lt.h"
#include "check.h"
namespace IT
{
	IdTable Create(int size)				
	{
		IdTable* tabl = new IdTable;
		if (size > TI_MAXSIZE)
		{
			throw ERROR_THROW(115);		
		}
		tabl->maxsize = size;
		tabl->size = 0;
		tabl->table = new Entry[size];	
		return*tabl;
	}

	void Add(IdTable& idtable, Entry entry)	
	{
		if (idtable.size + 1 > idtable.maxsize)
		{
			throw ERROR_THROW(116);		
		}

		idtable.table[idtable.size] = entry;
		idtable.size += 1;
	}
	
	Entry GetEntry(IdTable& idtable, int n)	
	{
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE])	
	{
		int n = 0;
		bool flag_s = false;
		while (n < idtable.size - 1)
		{
			if (idtable.table[n].id == id)	
			{
				flag_s = true;
				break;
			}
			n += 1;
		}
		if (flag_s)
		{
			return n + 1;		
		}
		else
		{
			return TI_NULLIDX;	
		}
	}

	void Delete(IdTable& idtable)	
	{
		delete[] idtable.table;
		delete &idtable;
	}
}