#include <fstream>
#include <algorithm>
#include <set>
#include <math.h>
#include "text_processing.cpp"

using namespace std;
int COUNT = 0; // used to count how many pages I have read in "organize_text()"


void alphabetical_insert(PTT original, PTT* Titulos) {
	PTT to_insert = original;
	for (int i = 0; i < COUNT; i++)
	{
		if ( compare_string(to_insert.titulo, Titulos[i].titulo) )
		{
			for (int k = COUNT - 1; k >= i; k--)
			{
				Titulos[k + 1] = Titulos[k];
			}
			Titulos[i] = to_insert;
			return;
		}
	}
	Titulos[COUNT] = to_insert;
	return;
}


void organize_text(PTT* Titulos, const vector<string> files) {
	bool got_to_the_end = false;
	int i = 0;
	string title, line, text;
	PTT* new_title = new PTT();
	size_t title_begin, title_end; // 155
	for (string file : files)
	{
		ifstream File(file);
		if (File.is_open())
		{
			while (getline(File, line))
			{
				if (line == "ENDOFARTICLE." && !new_title->titulo.empty())
				{
					i = -1;
					new_title->texto = text;
					if (COUNT == 0) Titulos[0] = *new_title;
					else alphabetical_insert(*new_title, Titulos);
					text.clear();
					COUNT++;
					got_to_the_end = true;
				}
				else
				{
					i++;
					if (i < 2)
					{
						title_begin = line.find("title");
						if (title_begin != string::npos)
						{
							title_begin += 7;
							title_end = line.find(" non");
							title = line.substr(title_begin, title_end - title_begin - 1);
							new_title->titulo = title;
						}
					}
					else
					{
						text.append(line);
						text.append("物");
						got_to_the_end = false;
					}
				}
			}
			if (!got_to_the_end && !new_title->titulo.empty())
			{
				i = -1;
				new_title->texto = text;
				alphabetical_insert(*new_title, Titulos);
				text.clear();
				COUNT++;
				got_to_the_end = true;
			}
		}
	}
}
