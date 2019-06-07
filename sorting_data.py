#Bruno
titles =  open("unsorted_titles.txt","r")
texts = open("unsorted_texts.txt","r")
PTIs = []

titulo = titles.readline()
texto = texts.readline()
print("COMECANDO A CRIAR")
while titulo:
    PTIs.append((titulo,texto))
    titulo = titles.readline()
    texto = texts.readline()
titles.close()
texts.close()

print("COMECAR AGORA SO")
PTIs.sort(key = lambda x: x[0])
print("TERMINEI")

sorted_texts = open("sorted_texts.txt","w+")
sorted_titles = open("sorted_titles.txt","w+")

for t in PTIs:
    sorted_texts.write(t[1])
    sorted_titles.write(t[0])

sorted_titles.close()
sorted_texts.close()

del PTIs



titles =  open("unsorted_titles.txt","r")
words_to_insert = open("words_to_insert.txt","r")
PTWs = []

titulo = titles.readline()
words = texts.readline()
print("COMECANDO A CRIAR")
while titulo:
    PTWs.append((titulo,words))
    titulo = titles.readline()
    words = words_to_insert.readline()
titles.close()
words_to_insert.close()

print("COMECAR AGORA SO")
PTWs.sort(key = lambda x: x[0])
print("TERMINEI")

sorted_words_to_insert = open("sorted_words_to_insert","w+")

for t in PTWs:
    sorted_texts.write(t[1])

sorted_words_to_insert.close()

del PTWs
