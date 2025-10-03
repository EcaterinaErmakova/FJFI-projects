ABC=['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
abc='abcdefghijklmnopqrstuvwxyz'
znaky={ ' ', ',', '.', '?', '!', ':', ';', '/', '%', '*', '(', ')', '1','2','3','4','5','6','7','8','9','0', '&' }


'''Words is list of words that contains the text (but some of them has some punctiation symbol)'''


def zashifr(k): 
    ''' This is dictionary ... {decoded letter(key): coded letter(item), ... }.
    We need it for coding words and texts.'''
    abc_klic=[]
    for i in range(26):
        abc_klic.append((abc[i], abc[(i+k)%26]))
    abc_klic=dict(abc_klic)
    return abc_klic

def deshifr(k): 
    ''' This is dictionary ... {coded letter(key): decoded letter(item), ... }.
    We need it for decoding words and texts.'''
    abc_klic=[]
    for i in range(26):
        abc_klic.append((abc[i], abc[(i-k)%26])) # (coded letter, decoded letter)
    abc_klic=dict(abc_klic)
    return abc_klic

def prepsani_slovo(slovo, abc_klic): 
    '''Decode 1 word'''
    nove_slovo=''
    for i in slovo:
        if i in znaky: break 
        else: nove_slovo+= abc_klic.get(i.lower())
    return nove_slovo

def proverka(slovo: str, slovnik: dict): # if the word is in english dictionary
    '''We check each letter with its order. The dictionary has construction of tree, so we are looking
    for needed word in next order:
    - Is first letter in dictionary?
    If it's not: stop controling and return False.
    If it is: 
        - Is next letter in first letters dictionary as a key?
            If it's not: stop controling and return False.
            If it is: Continue.
            ...
    If it has reached the last letter: 
        - Is there a key in its dictionary named '.' ? 
            If there is: this decoded word exists and return true.
            If there isn't: stop controling and return False.'''
    if len(slovo)==0:
        return slovnik.get('.', False)
    letter=slovo[0]
    if letter in slovnik:
        return proverka (slovo[1:], slovnik[letter])
    else:
        return False


def jestli_ONO (words: list, k: int, slovnik: dict, prover=0): # if this shift is the one that we need
    '''For this function we use: list of words, that text contains; dictonary of english words;
number of decoded words that exist in english dictionary (prover).
There has to be at least 5 decoded words in text, that exist in English languege.
If it's the end of text and number of existing decoded words is less than 5, it's not right shift. 
In other case we decode 1 word and control if it exists (if it does, we increase number of right words).
Then we recurse the function, but with updated number of existing words (prover) and list with 1 word less 
(the one we have been already controled). Dictionary is the same for any variables.'''
    if prover>=5: 
        return True
    elif len(words) == 0: 
        return False
    else: 
        slovo=prepsani_slovo(words[0], deshifr(k)) 
        if proverka(slovo, slovnik):
            prover+=1
        return jestli_ONO(words[1:], k, slovnik, prover)

def prepsani_textu(text, abc_klic): # decoding of current text (for that we use dictionary from def deshifr)
    '''For decoding of current text we use dictionary from def deshifr. 
    For decoding we use enumeration method.'''
    novy_text=''
    for i in text:
        if i in znaky: novy_text+=str(i) # if  symbol is not a letter, then we don't change it
        elif i in ABC: # if symbol is large letter, we make it small, decode the letter and make it large again
            new_letter=abc_klic.get(i.lower())
            novy_text+= new_letter.upper()
        elif i in abc: novy_text+= abc_klic.get(i) # if symbol is small letter, we decode it
    return novy_text



