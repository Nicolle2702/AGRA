"""
NICOLLE RUIZ QUINTERO
8974036

DECIDI USAR EL REDONDEO HALF UP PORQUE VI QUE A UNOS COMPAÑEROS ALGUNAS CIFRAS NO LES DABA Y YO PENSE QUE ERA EL REDONDEO DE PYTHON QUE NO
FUNCIONABA BIEN ENTONCES INVESTIGUE Y ENCONTRE EN UN FORO ESTE TIPO DE REDONDEO ADJUNTO LINK:
  https://es.stackoverflow.com/questions/317012/por-qué-en-python-3-round-redondea-3-5-a-4-pero-2-5-a-2

"""


import math
from decimal import Decimal, ROUND_HALF_UP
from collections import Counter

def operacionmatematica(palabras):
    total_palabras = len(palabras)
    conteo_palabras = Counter(palabras)
    frecuencia = calcularFrecuencia(total_palabras, conteo_palabras)
    
    eT = calcularET(frecuencia)
    eMax = math.log10(total_palabras)
    eRel = (eT / eMax) * 100
    
    eT_decimal = Decimal(eT).quantize(Decimal('1.0'), rounding=ROUND_HALF_UP)
    
    return total_palabras, eT_decimal, round(eRel)

def calcularFrecuencia(total, conteo_palabras):
    frecuencia = {}
    for palabra, conteo in conteo_palabras.items():
        frecuencia[palabra] = conteo / total
    return frecuencia

def calcularET(frecuencia):
    eT = 0
    for p in frecuencia.values():
        if p > 0:
            eT -= p * math.log10(p)
    return eT

def quitarPuntos(texto):

    texto = texto.lower()
    for char in [",", ".", ":", ";", "!", "?", "(", ")",'"']:
        texto = texto.replace(char, " ")

    palabras = texto.split()
    palabras_limpias = []

    for palabra in palabras:
        if palabra:  
            palabras_limpias.append(palabra)
    return palabras

def main():
    texto = input()
    textoCum = []
    
    while texto != '****END_OF_INPUT****':
        if texto == '****END_OF_TEXT****':
            palabras = quitarPuntos(' '.join(textoCum))
            total, eT, eRel = operacionmatematica(palabras)
            print(total,eT,eRel)
            textoCum = []
        else:
            textoCum.append(texto)
        
        texto = input()
main()

