# EDA Homework
## Library
- É necessários os seguindes modulos de C++(11):  boost/iostreams, iostream, fstream, vector, string e unordered_set.

## Pré-processamento
- Para obter o essencial para executar a engine extraia o conteúdo de https://gvmail-my.sharepoint.com/:u:/g/personal/b37411_fgv_edu_br/EYI-G33pmlZMsxOT0l_-bO4Bykq_QgJg5b1rR581nAJfiQ?e=pEbk2G para o repositório ou adicione a pasta "raw.en" (http://www.cs.upc.edu/~nlp/wikicorpus/raw.en.tgz) e execute o script Shell "pre_processing.sh".
- Todo a geração do pré-processamento utiliza os arquivos "files_names.txt", "generators.cpp", "organize_text.cpp", "pre_processing.sh", "sorting_data.py", "text_processing.cpp" e "trie.cpp"

## Search
- A engine Search necessita dos arquivos "search.cpp", "trie.cpp", "word_suggestor.cpp" e "text_processing.cpp".
- Compile “search.cpp” (g++ -o search -std=c++11 search.cpp -lboost_iostreams)
- Execute-o (./search)

## Integrantes
- William Sena - EMAp/FGV (https://github.com/wnsena)
- Bruno Almeida - EMAp/FGV (https://github.com/BrunodePauloAlmeida)
