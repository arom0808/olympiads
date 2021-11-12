#include <iostream>
#include <vector>
#include <algorithm>

struct list {
    std::size_t field = 0;
    list *next = nullptr;
    list *prev = nullptr;
};

list *listInit(const std::size_t &a)  // а- значение первого узла
{
    list *lst;
    // выделение памяти под корень списка
    lst = new list;
    lst->field = a;
    lst->next = nullptr; // указа   тель на следующий узел
    lst->prev = nullptr; // указатель на предыдущий узел
    return (lst);
}

list *listAddBackElem(list *lst, const std::size_t &number) {
    list *temp, *p;
    temp = new list;
    p = lst->next; // сохранение указателя на следующий узел
    lst->next = temp; // предыдущий узел указывает на создаваемый
    temp->field = number; // сохранение поля данных добавляемого узла
    temp->next = p; // созданный узел указывает на следующий узел
    temp->prev = lst; // созданный узел указывает на предыдущий узел
    if (p != nullptr)
        p->prev = temp;
    return (temp);
}

list *listAddFrontElem(list *lst, const std::size_t &number) {
    list *temp, *p;
    temp = new list;
    p = lst->prev; // сохранение указателя на предыдущий узел
    lst->prev = temp; // предыдущий узел указывает на создаваемый
    temp->field = number; // сохранение поля данных добавляемого узла
    temp->prev = p; // созданный узел указывает на следующий узел
    temp->next = lst; // созданный узел указывает на предыдущий узел
    if (p != nullptr)
        p->next = temp;
    return (temp);
}

list *listDeleteElem(list *lst) {
    list *prev, *next;
    prev = lst->prev; // узел, предшествующий lst
    next = lst->next; // узел, следующий за lst
    if (prev != nullptr)
        prev->next = lst->next; // переставляем указатель
    if (next != nullptr)
        next->prev = lst->prev; // переставляем указатель
    delete lst; // освобождаем память удаляемого элемента
    return (prev);
}

list *listDeleteHead(list *root) {
    list *temp;
    temp = root->next;
    temp->prev = nullptr;
    delete root;   // освобождение памяти текущего корня
    return (temp); // новый корень списка
}

list *listSwapElem(list *lst1, list *lst2, list *head) {
    // Возвращает новый корень списка
    list *prev1, *prev2, *next1, *next2;
    prev1 = lst1->prev;  // узел предшествующий lst1
    prev2 = lst2->prev;  // узел предшествующий lst2
    next1 = lst1->next; // узел следующий за lst1
    next2 = lst2->next; // узел следующий за lst2
    if (lst2 == next1)  // обмениваются соседние узлы
    {
        lst2->next = lst1;
        lst2->prev = prev1;
        lst1->next = next2;
        lst1->prev = lst2;
        if (next2 != nullptr)
            next2->prev = lst1;
        if (lst1 != head)
            prev1->next = lst2;
    } else if (lst1 == next2)  // обмениваются соседние узлы
    {
        lst1->next = lst2;
        lst1->prev = prev2;
        lst2->next = next1;
        lst2->prev = lst1;
        if (next1 != nullptr)
            next1->prev = lst2;
        if (lst2 != head)
            prev2->next = lst1;
    } else  // обмениваются отстоящие узлы
    {
        if (lst1 != head)  // указатель prev можно установить только для элемента,
            prev1->next = lst2; // не являющегося корневым
        lst2->next = next1;
        if (lst2 != head)
            prev2->next = lst1;
        lst1->next = next2;
        lst2->prev = prev1;
        if (next2 != nullptr) // указатель next можно установить только для элемента,
            next2->prev = lst1; // не являющегося последним
        lst1->prev = prev2;
        if (next1 != nullptr)
            next1->prev = lst2;
    }
    if (lst1 == head)
        return (lst2);
    if (lst2 == head)
        return (lst1);
    return (head);
}

bool listIsEqual(list *lst1, list *lst2) {
    if (lst1 == lst2)
        return true;
    if (lst1 == nullptr || lst2 == nullptr)
        return false;
    if (lst1->field != lst2->field)
        return false;
    for (list *l1iter = lst1, *l2iter = lst2;
         l1iter != nullptr && l2iter != nullptr; l1iter = l1iter->next, l2iter = l2iter->next) {
        if (l1iter->next == nullptr && l2iter->next == nullptr)
            continue;
        if (l1iter->next == nullptr || l2iter->next == nullptr)
            return false;
        if (l1iter->next->field != l2iter->next->field)
            return false;
    }
    return true;
}

list *listCopy(list *root) {
    if (root == nullptr)
        return nullptr;
    list *p = root, *lst = new list;
    do {
        listAddBackElem(lst, p->field);
        p = p->next; // переход к следующему узлу
    } while (p != nullptr); // условие окончания обхода
    lst = lst->next;
    delete lst->prev;
    lst->prev = nullptr;
    return (lst);
}

std::string listPrint(list *lst) {
    std::string res("");
    list *p;
    p = lst;
    do {
        res += std::to_string(p->field) + " "; // вывод значения элемента p
        p = p->next; // переход к следующему узлу
    } while (p != nullptr); // условие окончания обхода
    return res;
}

int main() {
    std::uint32_t N, M;
    std::cin >> N >> M;
    list *cubes = listInit(0), *lastAdded = cubes, *tempReversedCubes = listInit(0), *frontAdded = tempReversedCubes;
    std::cin >> cubes->field;
    tempReversedCubes->field = cubes->field;
    for (std::size_t i = 1; i < N; ++i) {
        lastAdded = listAddBackElem(lastAdded, 0);
        std::cin >> lastAdded->field;
        frontAdded = listAddFrontElem(frontAdded, lastAdded->field);
    }
    list *init_cubes = listCopy(cubes);
    lastAdded->next = frontAdded;
    frontAdded->prev = lastAdded;
    list *before_mirror = cubes, *peta_pos = cubes;
    for (std::size_t i = 0; i < N - 1; ++i) {
        before_mirror = before_mirror->next;
    }
    peta_pos = before_mirror->next;
    std::vector<std::size_t> results;
    for (std::size_t i = N; i >= N / 2 + (N % 2 == 0 ? 0 : 1); --i) {
        bool is_last_cycle = (i - 1) < N / 2 + (N % 2 == 0 ? 0 : 1);
        if (listIsEqual(init_cubes, peta_pos))
            results.push_back(i);
        if (!is_last_cycle) {
            peta_pos = peta_pos->prev->prev;
            before_mirror = before_mirror->prev;
            before_mirror->next = before_mirror->next->next->next;
            before_mirror->next->prev = before_mirror;
        }
    }
    std::sort(results.begin(), results.end());
    for (std::size_t i = 0; i < results.size(); ++i)
        std::cout << results[i] << (i != results.size() - 1 ? " " : "");
    return 0;
}