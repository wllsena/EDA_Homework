//Bruno
#include <fstream>
#include "text_processing.cpp"

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

void organize_text(const vector<string> files) {
	bool got_to_the_end = false;
	int i = 0, ns = 2, counter = 0;
	size_t title_begin, title_end;
	string title, line, text;
	ofstream pre_titles, pre_texts, pre_words_to_insert;
	vector< vector<int> > line_words;
	pre_titles.open("unsorted_titles.txt");
	pre_texts.open("unsorted_texts.txt");
	pre_words_to_insert.open("words_to_insert.txt"); // 155
	for (string file : files)
	{
		ifstream File(file);
		if (File.is_open())
		{
			while (getline(File, line))
			{
				if (line == "ENDOFARTICLE.")
				{
					ns = 2;
					i = -1;
					pre_texts << text;
					pre_texts << "\n";
					pre_words_to_insert << "\n";
					text.clear();
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
							pre_titles << title;
							pre_titles << "\n";
							title.clear();
						}
					}
					else
					{
						text.append(line);
						ns = (line != "" ? 0 : ns + 1);
						if (ns < 2)
							text.append("物");
						got_to_the_end = false;
						convert(line);
						line_words = word_breaker(line);
						for (auto it = line_words.begin(); it != line_words.end(); it++)
						{
							for (auto it2 = it->begin(); it2 != it->end(); it2++)
							{
								pre_words_to_insert << *it2;
								pre_words_to_insert << ".";
							}
							pre_words_to_insert << "*";
						}
					}
				}
			}
			if (!got_to_the_end && !text.empty())
			{
				ns = 2;
				i = -1;
				pre_texts << text;
				pre_texts << "\n";
				pre_words_to_insert << "\n";
				text.clear();
				got_to_the_end = true;
			}
		}
		counter++;
		cout << "Ja foi " + to_string(counter) + " !" << endl;
	}
	pre_titles.close();
	pre_texts.close();
	pre_words_to_insert.close();
}