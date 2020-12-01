#include"stdafx.h"
#include<iostream>
#include<fstream>
#include <sstream>
#include <iomanip>
#include"Lt.h"
#include"It.h"
#define MFST_TRACE_START std::cout<<std::setw(4)<<std::left<<"Шаг"<<":"\
<<std::setw(20)<<std::left<<"Правило"\
<<std::setw(30)<<std::left<<"Входная лента"\
<<std::setw(20)<<std::left<<"Стек"\
<<std::endl;
LT::LexTable lextab = LT::Create(LT_MAXSIZE - 1);
IT::IdTable idtab = IT::Create(TI_MAXSIZE - 1);
namespace Check
{
	bool testik(char* m, FST::FST fst)
	{
		fst.string = m;
		return FST::execute(fst);
	}


	void insert(int line, char m)
	{
		LT::Entry entry;
		entry.sn = line;
		memset(entry.lexema, '\0', strlen(entry.lexema) - 1);
		
			entry.lexema[0] = m;
		
		LT::add(lextab, entry);
	}
	void Analiz(Parm::PARM parm, In::IN in)
	{
		char word[255] = "";
		char word2[255] = "";
		int m = 0;
		int line = 1;
		bool test = false;		
		bool povt_id = false;
		char ch;
		bool flag_s = false;
		bool flag_i = false;
		bool pflag = false;		
		bool id = false;
		char lit = '0';
		bool flag_lit = false;
		int n = 0;
		IT::Entry entr;
		short one_kov = 0;			
		bool povt_lit = false;
		int flag_func = true;
		for (int i = 0; i < in.size; i++)
		{
			ch = in.text[i];
			test = false;
			if (ch == IN_CODE_ENDL)
			{
				line++;
				//insert(line, ' \n');
				continue;
			}
			if (ch == '\'')
			{
				one_kov++;
				if (one_kov == 2)
					one_kov = 0;
			}
			if (one_kov == 1)
			{
				word[m] = ch;
				m++;
				continue;
			}


			if (ch != ' ' && ch != ';' && ch != '-' && ch != '+' && ch != '/' && ch != '*' && ch != '\''
				&& ch != ',' && ch != ')' && ch != '(' && ch != '}' && ch != '{' && ch != IN_CODE_ENDL && ch != '=')
			{
				
				word[m] = ch;
				m++;
				continue;
			}

			else
			{

				word[m] = '\0';
				m = 0;

				if (ch == IN_CODE_ENDL)
				{
					line++;
					continue;
				}
				FST::FST* typestring=new FST::FST((char*)"", 7,
					FST::NODE(1, FST::RELATION('s', 1)),
					FST::NODE(1, FST::RELATION('t', 2)),
					FST::NODE(1, FST::RELATION('r', 3)),
					FST::NODE(1, FST::RELATION('i', 4)),
					FST::NODE(1, FST::RELATION('n', 5)),
					FST::NODE(1, FST::RELATION('g', 6)),
					FST::NODE()
				);
				test = testik(word, *typestring);	
				if (test)
				{
					insert(line, LEX_STRING);
					flag_s = true;
				}
				delete typestring;
				if (!test)
				{
					FST::FST* typeint = new FST::FST((char*)"", 8,
						FST::NODE(1, FST::RELATION('i', 1)),
						FST::NODE(1, FST::RELATION('n', 2)),
						FST::NODE(1, FST::RELATION('t', 3)),
						FST::NODE(1, FST::RELATION('e', 4)),
						FST::NODE(1, FST::RELATION('g', 5)),
						FST::NODE(1, FST::RELATION('e', 6)),
						FST::NODE(1, FST::RELATION('r', 7)),
						FST::NODE());
					test = testik(word, *typeint);
					if (test)
					{
						flag_i = true;
						insert(line, LEX_INTEGER);
					}
					delete typeint;
				}
				if (!test)
				{
					FST::FST* typefunction=new FST::FST((char*)"", 9,
						FST::NODE(1, FST::RELATION('f', 1)),
						FST::NODE(1, FST::RELATION('u', 2)),
						FST::NODE(1, FST::RELATION('n', 3)),
						FST::NODE(1, FST::RELATION('c', 4)),
						FST::NODE(1, FST::RELATION('t', 5)),
						FST::NODE(1, FST::RELATION('i', 6)),
						FST::NODE(1, FST::RELATION('o', 7)),
						FST::NODE(1, FST::RELATION('n', 8)),
						FST::NODE()
					);
					test = testik(word, *typefunction);
					if (test)
					{
						insert(line, LEX_FUNCTION);
					}
					delete typefunction;
				}
				if (!test)
				{
					FST::FST* strdeclare=new FST::FST((char*)"", 8,
						FST::NODE(1, FST::RELATION('d', 1)),
						FST::NODE(1, FST::RELATION('e', 2)),
						FST::NODE(1, FST::RELATION('c', 3)),
						FST::NODE(1, FST::RELATION('l', 4)),
						FST::NODE(1, FST::RELATION('a', 5)),
						FST::NODE(1, FST::RELATION('r', 6)),
						FST::NODE(1, FST::RELATION('e', 7)),
						FST::NODE()
					);
					test = testik(word, *strdeclare);	
					if (test)
					{
						insert(line, LEX_DECLARE);
					}
					delete strdeclare;
				}
				if (!test)
				{
					FST::FST* streturn=new FST::FST((char*)"", 7,
						FST::NODE(1, FST::RELATION('r', 1)),
						FST::NODE(1, FST::RELATION('e', 2)),
						FST::NODE(1, FST::RELATION('t', 3)),
						FST::NODE(1, FST::RELATION('u', 4)),
						FST::NODE(1, FST::RELATION('r', 5)),
						FST::NODE(1, FST::RELATION('n', 6)),
						FST::NODE()
					);
					test = testik(word, *streturn);	
					if (test)
					{
						insert(line, LEX_RETURN);
					}
					delete streturn;
				}
				if (!test)
				{
					FST::FST* strmain=new FST::FST((char*)"", 5,
						FST::NODE(1, FST::RELATION('m', 1)),
						FST::NODE(1, FST::RELATION('a', 2)),
						FST::NODE(1, FST::RELATION('i', 3)),
						FST::NODE(1, FST::RELATION('n', 4)),
						FST::NODE()
					);
					test = testik(word, *strmain);	
					if (test)
					{
						insert(line, LEX_MAIN);

					}
					delete strmain;
				}
				
				if (!test)
				{
					FST::FST* strprint=new FST::FST((char*)"", 6,
						FST::NODE(1, FST::RELATION('p', 1)),
						FST::NODE(1, FST::RELATION('r', 2)),
						FST::NODE(1, FST::RELATION('i', 3)),
						FST::NODE(1, FST::RELATION('n', 4)),
						FST::NODE(1, FST::RELATION('t', 5)),
						FST::NODE()
					);

					test = testik(word, *strprint);	
					if (test)
					{
						insert(line, LEX_PRINT);
					}
					delete strprint;
				}
				
				if (word[0] == '\'')
				{
					insert(line, LEX_LITERAL);
					for (int i = 0; i < strlen(word); i++)
						word2[i] = word[i + 1];	
					word2[strlen(word)] = '\0';
					test = true;					
					flag_lit = true;
					flag_s = true;
				}

				
				
				if (!test)
				{
					FST::FST* Literal=new FST::FST((char*)"", 2,
						FST::NODE(20,
							FST::RELATION('0', 0), FST::RELATION('1', 0), FST::RELATION('2', 0),
							FST::RELATION('3', 0), FST::RELATION('4', 0), FST::RELATION('5', 0),
							FST::RELATION('6', 0), FST::RELATION('7', 0), FST::RELATION('8', 0),
							FST::RELATION('9', 0), FST::RELATION('0', 1), FST::RELATION('1', 1),
							FST::RELATION('2', 1), FST::RELATION('3', 1), FST::RELATION('4', 1),
							FST::RELATION('5', 1), FST::RELATION('6', 1), FST::RELATION('7', 1),
							FST::RELATION('8', 1), FST::RELATION('9', 1)),
						FST::NODE()
					);

					test = testik(word, *Literal);
					if (test)
					{
						insert(line, LEX_LITERAL);
						flag_lit = true;
						flag_i = true;
					}
					delete Literal;

			    }

				if (flag_lit && test)
				{
					
					entr.idxfirstLE = line;		
					entr.idtype = IT::L;
					if (idtab.size > 0) 
					{
						
						for (int u = 0; u < idtab.size && test; u++)
						{
							if (idtab.table[u].idtype == 4)	
							{
								if (flag_i == true)
								{
									if (atoi(word) == idtab.table[u].value.vint)
									{
										lextab.table[lextab.size - 1].idxTI = u;
										test = false;
										povt_lit = true;
										flag_lit = false;
										flag_i = false;
									}
								}
								if (flag_s == true)
								{
									if (strcmp(word2, idtab.table[u].value.vstr.str) == 0)
									{
										lextab.table[lextab.size].idxTI = u;
										test = false;
										povt_lit = true;
										flag_lit = false;
										flag_s = false;
									}
								}
							}
						}
					}
					
					if (!povt_lit)
					{
						entr.id[0] = 'L';
						entr.id[1] = lit + 1;
						lit++;
						entr.id[2] = '\0';
						flag_lit = false;	

						if (flag_s)
						{
							entr.iddatatype = IT::STR;				
							strcpy_s(entr.value.vstr.str, word2);		
							entr.value.vstr.len = strlen(word2);	
							flag_s = false;							
						}
						if (flag_i)
						{
							entr.iddatatype = IT::INT;
							entr.value.vint = atoi(word);
							flag_i = false;
						}
						lextab.table[lextab.size - 1].idxTI = idtab.size;
						IT::Add(idtab, entr);
					}
					else
						povt_lit = false;
				}

			
				if ((ch == ' ' && word[0] == '\0'))
				{
					memset(word, '\0', strlen(word));
					continue;
				}

				
				if (word[0] == '\0')
					test = true;

				
				if (!test)
				{
					FST::FST* fstidenf = new FST::FST((char*)"", 2,
						FST::NODE(54,
							FST::RELATION('a', 1), FST::RELATION('a', 0), FST::RELATION('b', 1), FST::RELATION('b', 0),
							FST::RELATION('c', 1), FST::RELATION('c', 0), FST::RELATION('d', 1), FST::RELATION('d', 0), FST::RELATION('e', 1), FST::RELATION('e', 0),
							FST::RELATION('f', 1), FST::RELATION('f', 0), FST::RELATION('g', 1), FST::RELATION('g', 0), FST::RELATION('h', 0), FST::RELATION('h', 1), FST::RELATION('i', 0), FST::RELATION('i', 1),
							FST::RELATION('j', 0), FST::RELATION('j', 1), FST::RELATION('k', 0), FST::RELATION('k', 1), FST::RELATION('l', 0), FST::RELATION('l', 1),
							FST::RELATION('m', 0), FST::RELATION('m', 1), FST::RELATION('n', 0), FST::RELATION('n', 1), FST::RELATION('o', 0), FST::RELATION('o', 1),
							FST::RELATION('p', 0), FST::RELATION('p', 1), FST::RELATION('q', 0), FST::RELATION('q', 1), FST::RELATION('r', 0), FST::RELATION('r', 1),
							FST::RELATION('s', 0), FST::RELATION('s', 1), FST::RELATION('t', 0), FST::RELATION('t', 1), FST::RELATION('u', 0), FST::RELATION('u', 1),
							FST::RELATION('v', 0), FST::RELATION('v', 1), FST::RELATION('w', 0), FST::RELATION('w', 1), FST::RELATION('x', 0), FST::RELATION('x', 1),
							FST::RELATION('y', 0), FST::RELATION('y', 1), FST::RELATION('z', 0), FST::RELATION('z', 1)),
						FST::NODE()
					);
					test = testik(word, *fstidenf);	
					if (test)
					{
						
						id = true;
					}
					delete fstidenf;
					
				}
				
				if (test && id)
				{
					test = false;
					id = false;
					insert(line, LEX_ID);
					lextab.table[lextab.size].idxTI = idtab.size;

					if (lextab.table[lextab.size - 2].lexema[0] != 'f')
					{
						if (strlen(word) < ID_MAXSIZE)
							strcpy_s(entr.id, word);
						else if(strcmp(word,"strlen")==0|| strcmp(word, "substr") == 0)
						{
							for (int i = 0; i < 6; i++)
							{
								entr.id[i] = word[i];
							}
							entr.id[6] = '\0';
						}
						else
						{
							throw ERROR_THROW_IN(117,line-1,-1)
						}
						entr.idxfirstLE = line;	
					}
					else
					{
						
						strcpy_s(entr.functionname, word);
						strcpy_s(entr.id, "null");
						entr.idxfirstLE = line;
					}

					
					if (idtab.size > 0)
						for (int u = 0; u < idtab.size && !test; u++)
						{
							
								if (strcmp(idtab.table[u].id, "null") == 0 && 
									strcmp(idtab.table[u].functionname, word) == 0)
								{
									lextab.table[lextab.size - 1].idxTI = u;

									if (idtab.table[u].iddatatype == IT::INT)
									{
										flag_i = false;
									}
									if (idtab.table[u].iddatatype == IT::STR)
									{
										flag_s = false;
									}
									test = false;
									povt_id = true;
								}
								if (strcmp(entr.id, idtab.table[u].id) == 0 &&	
									strcmp(idtab.table[u].id, "null") != 0)
								{
									lextab.table[lextab.size - 1].idxTI = u;
									if (idtab.table[u].iddatatype == IT::INT)
									{
										flag_i = false;
									}
									if (idtab.table[u].iddatatype == IT::STR)
									{
										flag_s = false;
									}
									test = false;
									povt_id = true;
								}
							
						}
					
					if (!povt_id)
					{
						entr.idtype = IT::V;

						if (lextab.table[lextab.size - 2].lexema[0] == 'f')
						{
							entr.idtype = IT::F;
							flag_func = false;

						}

						if ((lextab.table[lextab.size-3].lexema[0] == '(' && lextab.table[lextab.size - 4].lexema[0] != 'v') ||pflag|| lextab.table[lextab.size - 3].lexema[0] == ','&&flag_func)
						{
							entr.idtype = IT::P;
							pflag = true;
						}

						if (!test)
						{
							if (flag_s)
							{
								entr.iddatatype = IT::STR;			
								strcpy_s(entr.value.vstr.str, "");	
								entr.value.vstr.len = 0;			
								flag_s = false;	
								
							}

							if (flag_i)
							{
								entr.iddatatype = IT::INT;
								entr.value.vint = 0;
								flag_i = false;
							}
						}
						IT::Add(idtab, entr);
					}
					else
						povt_id = false;
					test = false;
					flag_func = true;
				}
			}
			

			
			if ((ch == ' ' && word[0] == '\0'))
			{
				memset(word, '\0', strlen(word));
				continue;
			}

			
			if (word[0] == '\0')
				test = true;

			
			
			
				if (ch == '+' || ch == '*' || ch == '-' || ch == '/' || ch == '=')
				{
					char word2[5];
					test = false;
					word2[0] = ch;
					word2[1] = '\0';
					FST::FST* umn=new FST::FST((char*)"", 2,
						FST::NODE(1, FST::RELATION('*', 1)),
						FST::NODE());
					test = testik(word2, *umn);
					if (test)
					{
						insert(line, LEX_STAR);
					}
					delete umn;
					if (!test)
					{
						FST::FST* ravno=new FST::FST((char*)"", 2,
							FST::NODE(1, FST::RELATION('=', 1)),
							FST::NODE());
						test = testik(word2, *ravno);
						if (test)
						{
							insert(line, LEX_R);
						}
						delete ravno;
					}
					if (!test)
					{
						FST::FST* minus=new FST::FST((char*)"", 2,
							FST::NODE(1, FST::RELATION('-', 1)),
							FST::NODE());

						test = testik(word2, *minus);
						if (test)
						{
							insert(line, LEX_MINUS);
						}
						delete minus;
					}
					if (!test)
					{
						FST::FST* plus=new FST::FST((char*)"", 2,
							FST::NODE(1, FST::RELATION('+', 1)),
							FST::NODE());

						test = testik(word2, *plus);
						if (test)
						{
							insert(line, LEX_PLUS);
						}
						delete plus;
					}
					if (!test)
					{
						FST::FST* del=new FST::FST((char*)"", 2,
							FST::NODE(1, FST::RELATION('/', 1)),
							FST::NODE());
						test = testik(word2, *del);
						if (test)
						{
							insert(line, LEX_DIRSLASH);
						}
						delete del;
					}


				}

				
				if (ch == LEX_SEMICOLON || ch == LEX_LEFTHESIS ||
					ch == LEX_RIGHTHESIS || ch == LEX_LEFTBRACE ||
					ch == LEX_BRACELET || ch == LEX_COMMA)
				{
					test = false;
					memset(word, '\0', strlen(word));
					word[0] = in.text[i];
					word[1] = '\0';
					FST::FST* semicolon=new FST::FST((char*)"", 2,
						FST::NODE(1, FST::RELATION(';', 1)),
						FST::NODE()
					);
					test = testik(word, *semicolon);
					if (test)
					{
						insert(line, LEX_SEMICOLON);
					}
					delete semicolon;
					if (!test)
					{
						FST::FST*leftbrace=new FST::FST((char*)"", 2,
							FST::NODE(1, FST::RELATION('{', 1)),
							FST::NODE()
						);
						test = testik(word, *leftbrace);
						if (test)
						{
							n = 1;
							insert(line, LEX_LEFTBRACE);

						}
						delete leftbrace;
					}
					if (!test)
					{
						FST::FST*rightbrace=new FST::FST((char*)"", 2,
							FST::NODE(1, FST::RELATION('}', 1)),
							FST::NODE()
						);
						test = testik(word, *rightbrace);
						if (test)
						{
							insert(line, LEX_BRACELET);
						}
						delete rightbrace;
					}
					if (!test)
					{
						FST::FST* comma=new FST::FST((char*)"", 2,
							FST::NODE(1, FST::RELATION(',', 1)),
							FST::NODE()
						);
						test = testik(word, *comma);
						if (test)
						{
							insert(line, LEX_COMMA);
						}
						delete comma;
					}
					if (!test)
					{
						FST::FST* leftthesis=new FST::FST((char*)"", 2,
							FST::NODE(1, FST::RELATION('(', 1)),
							FST::NODE()
						);
						test = testik(word, *leftthesis);
						if (test)
						{
							insert(line, LEX_LEFTHESIS);

						}
						delete leftthesis;
					}
					if (!test)
					{
						FST::FST* rightthesis=new FST::FST((char*)"", 2,
							FST::NODE(1, FST::RELATION(')', 1)),
							FST::NODE()
						);
						test = testik(word, *rightthesis);
						if (test)
						{
							insert(line, LEX_RIGHTHESIS);
							pflag = false;
						}
						delete rightthesis;
					}
				}
				
			
			memset(word, '\0', strlen(word));

		}

		std::fstream file;
		file.open(parm.log,std::ios::app);
		if (file.fail())
		{
			throw ERROR_THROW(112);	
		}
		file << '\n';
		file << lextab.table[0].sn << ' ';
		int l = 2;

		for (int i = 0; i < lextab.size; i++)
		{
			if (lextab.table[i].lexema[0] != '\0')
			{
				if (i != 0)
				{
					if (lextab.table[i - 1].sn != lextab.table[i].sn)
					{
						file << '\n';	
						file << l<<' ';
						l++;
					}
				}
				file << lextab.table[i].lexema[0];
			}
		}
		file << '\n';
		file << std::setw(15) << "|Имя" << std::setw(2) << '|';
		file << std::setw(15) << "|Общий тип" << std::setw(2) << '|';
		file << std::setw(8) << "|Тип" << std::setw(2) << '|';
		file << std::setw(25) << "|Первое вхождение" << std::setw(2) << '|';
		file << std::setw(15) << "|Значение" << std::setw(2) << '|';
		file << '\n';
		for (int i = 0; i < idtab.size; i++)
		{
			if (strcmp(idtab.table[i].id, "null"))
				file << std::setw(15) << idtab.table[i].id << std::setw(2);
			else {
				file << std::setw(15) << idtab.table[i].functionname << std::setw(2);
			}
			if (idtab.table[i].iddatatype == IT::INT)
			{

				file << std::setw(15) << "integer" << std::setw(2);
			}
			if (idtab.table[i].iddatatype == IT::STR)
			{
				file << std::setw(15) << "string" << std::setw(2);
			}
			if (idtab.table[i].idtype == IT::F)
			{
				file << std::setw(15) << "функция" << std::setw(2);
			}

			if (idtab.table[i].idtype == IT::P)
			{
				file << std::setw(15) << "параметр" << std::setw(2);
			}
			if (idtab.table[i].idtype == IT::L)
			{
				file << std::setw(15) << "литерал" << std::setw(2);
			}
			if (idtab.table[i].idtype == IT::V)
			{
				file << std::setw(15) << "переменная" << std::setw(2);
			}
			file << std::setw(15) << idtab.table[i].idxfirstLE << std::setw(2);

			if (idtab.table[i].iddatatype == IT::INT&& idtab.table[i].idtype != IT::F)
			{
				file << std::setw(25) << idtab.table[i].value.vint << std::setw(2) << std::setw(15) << " " << std::setw(2);
			}
			else
			{


				if (idtab.table[i].value.vstr.len == '\0' && idtab.table[i].idtype != IT::F)
				{
					file << std::setw(25) << "null" << std::setw(2);
				}
				else if(idtab.table[i].value.vstr.len != '\0' && idtab.table[i].idtype != IT::F)
				{
					file << std::setw(28) << idtab.table[i].value.vstr.str<<"(длина= "<< (int)idtab.table[i].value.vstr.len<<')' << std::setw(2);
					

				}
				else if (idtab.table[i].value.vstr.len == '\0' && idtab.table[i].idtype == IT::F)
				{
					file << std::setw(25) << "-1" << std::setw(2);
				}
				

			}
			
			file << '\n';
		}
		
		file.close();
		MFST_TRACE_START
			MFST::Mfst mfst(lextab, GRB::getGreibach());
		mfst.start();
		mfst.savededucation();
		mfst.printrules();
	}

}