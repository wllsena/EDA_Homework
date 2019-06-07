//Bruno
#include <fstream>
#include "text_processing.cpp"

vector<string> file_names() {
  vector<string> files;
  string file;
  ifstream File("files_names.txt");
  if (File.is_open()) {
    while (getline(File, file))
      files.push_back("raw.en/" + file);
  };
  return files;
};

int main () {
  const vector<string> files = file_names();
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
            pre_words_to_insert << line;
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
	}
	pre_titles.close();
	pre_texts.close();
	pre_words_to_insert.close();
}
