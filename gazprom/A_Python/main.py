encrypted_phrases = ["Шцлиц эцадгнюизх 15 гдхчжх ю шыжгйзт 13 ъыацчжх",
                     "101 идгг ъдчсидя гыкию ъцбю -40 еждмыгидш уккыаиюшгдзию ацеюицбдшбдьыгюя",
                     "Эцъцяиы задждзит шжцпыгюх адбыгнцидщд шцбц ш 124 ежю йщбы -63"]
big_symbols = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
small_symbols = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя"

"Задайте скорость вращения коленчатого вала в 124 при угле -63"

def DecryptPhrase(encrypted_string: str, shift_size: int):
    result = ""
    for encrypted_char in encrypted_string:
        if encrypted_char in big_symbols:
            result += big_symbols[(big_symbols.index(encrypted_char) + shift_size) % len(big_symbols)]
        elif encrypted_char in small_symbols:
            result += small_symbols[(small_symbols.index(encrypted_char) + shift_size) % len(small_symbols)]
        else:
            result += encrypted_char
    return result


def DecryptPhrases(shift_size):
    for encrypted_phrase in encrypted_phrases:
        print(DecryptPhrase(encrypted_phrase, shift_size))


for shift_s in range(0, 33):
    print(str(shift_s) + ":")
    DecryptPhrases(shift_s)
    print()
