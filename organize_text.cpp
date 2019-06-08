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
#include <iostream>
int main () {
  const vector<string> files = file_names();
  bool had_title;
	int ns = 2;
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
          had_title = false;
          while (getline(File, line))
            {
              if ((line == "ENDOFARTICLE." or line == "</doc>") and had_title)
                {
                  ns = 2;
                  pre_texts << text;
                  pre_texts << "\n";
                  convert(text);
                  pre_words_to_insert << text;
                  pre_words_to_insert << "\n";
                  text.clear();
                  had_title = false;
                }
              else if (line.find("<doc id=\"") != string::npos)
                {
                  title_begin = line.find("title") + 7;
                  title_end = line.find(" non");
                  title = line.substr(title_begin, title_end - title_begin - 1);
                  pre_titles << title;
                  pre_titles << "\n";
                  title.clear();
                  had_title = true;
                }
              else
                {
                  text.append(line);
                  ns = (line != "" ? 0 : ns + 1);
                  if (ns < 2)
                    text.append("物");
                }
            }
          if (had_title)
            {
              ns = 2;
              pre_texts << text;
              pre_texts << "\n";
              convert(text);
              pre_words_to_insert << text;
              pre_words_to_insert << "\n";
              text.clear();
              had_title = false;
            }
        }
    }
  pre_titles.close();
  pre_texts.close();
  pre_words_to_insert.close();
}
