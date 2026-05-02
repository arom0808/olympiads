def CesarShift(string: str, shift: int):
    alphabet = "абвгдежзийклмнопрстуфхцчшщъыьэюя"
    result = ""
    for char in string:
        if char in alphabet:
            result += alphabet[(alphabet.index(char) + shift + len(alphabet)) % len(alphabet)]
        else:
            result += char
    return result


def Encrypt_1(string: str):
    result = ""
    for i in range(0, len(string), 2):
        if i + 1 < len(string):
            result += string[i + 1] + string[i]
        else:
            result += string[i]
    return result


def Encrypt(string: str):
    result = CesarShift(Encrypt_1(string), 2)[::-1]
    return result


def Dencrypt(string: str):
    result = Encrypt_1(CesarShift(string[::-1], -2))
    return result


encrypted = "врпвл терпраиэ вйзгцфпз"
decrypted = Dencrypt(encrypted)
print(encrypted)
print(decrypted)
