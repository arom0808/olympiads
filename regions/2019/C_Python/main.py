def CalculatePositionForCard(card: int, cards_array: [int], products_types: [int], current_product_type_index: int):
    cards_indexes = [cards_array.index(product_card) for product_card in products_types[:current_product_type_index]]
    return 0


if __name__ == '__main__':
    n, m = [int(value) for value in input().split()]
    a = [int(value) - 1 for value in input().split()]
    b = [int(value) - 1 for value in input().split()]
    actions = []
    for currentProductTypeIndex in range(len(a)):
        while b[0] != a[currentProductTypeIndex]:
            card = b.pop(0)
            b.insert(CalculatePositionForCard(card, b, a, currentProductTypeIndex), card)
        actions.append(len(b))
