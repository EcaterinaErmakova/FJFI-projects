import JakyShifr
import Slovnik

ABC=['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
abc=list('abcdefghijklmnopqrstuvwxyz')
zanky={ ' ', ',', '.', '?', '!', ':', ';', '/', '%', '*', '(', ')', '1','2','3','4','5','6','7','8','9','0', '&' }

promo='''
Vyberte akce (cislo):
1. Zasifrovat
2. Desifrovat

'''

opcia=int(input(promo))


def zasifrovni():
    shift=int(input('Zadejte cislo posunuti od 1 do 26: ' ))
    if shift<1 or shift>26:
        print('Takove posunuti nema smysl!')
        return zasifrovni()
    else:
        text=str(input('Zadejte text pro sifrovani (pro anglictinu): '))
        return JakyShifr.prepsani_textu(text, JakyShifr.zashifr(shift))

def desifrovni():
    text=str(input('Zadejte text pro desifrovani (pro anglictinu): '))
    words=list(text.split()) 
    if len(words)<5:
                print('Text neni vhodny pro desifrovani: je priliis kratky!')
                return desifrovni()
    for shift in range (1,26): 
        if JakyShifr.jestli_ONO(words, shift, Slovnik.slovnik, 0):
            return JakyShifr.prepsani_textu(text, JakyShifr.deshifr(shift))
    return 'Takovy text nelze desifrovat s zadnym posunutim!'
    
if opcia==1:
    print(zasifrovni())
elif opcia==2:
    print(desifrovni())
