
def add_word(slovnik: dict, word): 
    '''Do slovniku dosazujeme nove slovo ve tvaru dreva. 
    Pak overujeme, jestli je prvni pismeno v slovniku (pak jdeme do pristi pismena).
    Kdyz ne, tak dosazujeme pismeno jako key a jako jeho item vytvorime novy slovnik 
    (slovnik ve slovniku). Kdyz dosazujeme konec slova, zvyraznime posledni pismeno jako konec slova (.).'''
    letter=word[0] 
    if letter not in slovnik: 
        slovnik[letter]={}
    if len(word)==1: 
        posledni_pis(slovnik[letter])
        return 
    else:
        slovo=slovnik[letter]
        return add_word(slovo, word[1:])
    
def posledni_pis (slovnik: dict):
    slovnik['.']=True
    return
    
def make_dict(dictionary: dict, slovnik: dict):
    '''Vytvorime slovnik'''
    for line in dictionary:
        word=line.strip()
        add_word(slovnik, word)
    return slovnik

with open ('google-10000-english-no-swears.txt') as dictionary:
    slovnik=make_dict(dictionary, {})


        