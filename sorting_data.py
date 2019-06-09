#Bruno
titles =  open("unsorted_titles.txt","r")
texts = open("unsorted_texts.txt","r")
PTIs = []

titulo = titles.readline()
texto = texts.readline()

while titulo:
    PTIs.append((titulo,texto))
    titulo = titles.readline()
    texto = texts.readline()

titles.close()
texts.close()

PTIs.sort(key = lambda x: x[0])

for i in range(136):
    sorted_texts = open("sorted_texts/sorted_texts_{}".format(i),"w+")
    sorted_titles = open("sorted_titles/sorted_texts_{}".format(i),"w+")

    for t in PTIs[i*10000:i*10000 + 10000]:
        sorted_texts.write(t[1])
        sorted_titles.write(t[0])

    sorted_titles.close()
    sorted_texts.close()

del PTIs


titles =  open("unsorted_titles.txt","r")
words_to_insert = open("words_to_insert.txt","r")
PTWs = []

titulo = titles.readline()
words = words_to_insert.readline()

while titulo:
    PTWs.append((titulo,words))
    titulo = titles.readline()
    words = words_to_insert.readline()

titles.close()
words_to_insert.close()

PTWs.sort(key = lambda x: x[0])

sorted_words_to_insert = open("sorted_words_to_insert.txt","w+")

for t in PTWs:
    sorted_words_to_insert.write(t[1])

sorted_words_to_insert.close()

del PTWs
