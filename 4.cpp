#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Структура узла бинарного дерева
struct Node {
    int data;              // Данные узла
    struct Node* left;     // Указатель на левое поддерево
    struct Node* right;    // Указатель на правое поддерево
};

// Функция создания нового узла и добавления его в дерево
struct Node* CreateTree(struct Node* r, int data) {
    // Если дерево пусто, создаем новый узел
    if (r == NULL) {
        r = (struct Node*)malloc(sizeof(struct Node));  // Выделяем память под новый узел
        if (r == NULL) {
            printf("Ошибка выделения памяти\n");
            exit(0);  // Завершаем программу при ошибке выделения памяти
        }
        r->left = NULL;  // Левое поддерево пусто
        r->right = NULL; // Правое поддерево пусто
        r->data = data;  // Присваиваем значение новому узлу
        return r;        // Возвращаем указатель на новый узел
    }

    // Если значение больше текущего узла, идем в правое поддерево
    if (data > r->data) {
        r->right = CreateTree(r->right, data); // Рекурсивный вызов для правого поддерева
    }
    // Если значение меньше, идем в левое поддерево
    else if (data < r->data) {
        r->left = CreateTree(r->left, data);   // Рекурсивный вызов для левого поддерева
    }

    return r;  // Возвращаем корень дерева
}

// Функция вычисления высоты дерева (максимальная глубина дерева)
int tree_height(struct Node* root) {
    if (root == NULL)
        return 0;  // Высота пустого дерева равна 0

    // Рекурсивное вычисление высоты левого и правого поддерева
    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);

    // Возвращаем большую из двух высот, прибавив 1 (для текущего узла)
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

// Функция для вывода пробелов
void print_spaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");  // Выводим указанное количество пробелов
    }
}

// Функция печати узлов дерева на заданном уровне
void print_current_level(struct Node* root, int level, int indent_space, int node_space) {
    // Если узел пустой, печатаем пробелы вместо него
    if (root == NULL) {
        print_spaces(indent_space + node_space); // Печатаем пробелы для отсутствующего узла
        return;
    }

    // Если уровень равен 1, печатаем данные узла
    if (level == 1) {
        printf("%d", root->data);    // Печатаем значение узла
        print_spaces(node_space);    // Печатаем пробелы между узлами
    }
    // Иначе продолжаем рекурсивный вызов для левого и правого поддерева
    else if (level > 1) {
        print_current_level(root->left, level - 1, indent_space / 2, node_space);  // Левое поддерево
        print_current_level(root->right, level - 1, indent_space / 2, node_space); // Правое поддерево
    }
}

// Функция печати дерева уровнями с отступами для симметрии
void print_tree(struct Node* root) {
    int h = tree_height(root);  // Вычисляем высоту дерева
    int node_space;             // Переменная для хранения расстояния между узлами

    // Цикл по уровням дерева (от 1 до h)
    for (int i = 1; i <= h; i++) {
        // Задаем начальный отступ для корня (4 пробела) и для остальных уровней (0)
        int indent_space = (i == 1) ? 4 : 0;

        // Задаем расстояние между узлами для каждого уровня
        if (i == 1) {
            node_space = 0;  // Для корня пробелы не нужны
        }
        else if (i == 2) {
            node_space = 7;  // Для второго уровня расстояние между узлами 7 пробелов
        }
        else {
            node_space = 3;  // Для третьего уровня расстояние между узлами 3 пробела
        }

        // Печатаем отступы для текущего уровня
        print_spaces(indent_space);

        // Печатаем узлы текущего уровня
        print_current_level(root, i, indent_space, node_space);

        printf("\n");  // Переход на новую строку после печати уровня
    }
}

int main() {
    struct Node* root = NULL;  // Инициализация корня дерева
    int D, start = 1;          // Переменные для ввода данных

    // Ввод чисел для построения дерева
    printf("-1 - окончание построения дерева\n");
    while (start) {
        printf("Введите число: ");
        scanf("%d", &D);  // Чтение числа

        if (D == -1) {    // Если введено -1, завершить ввод
            printf("Построение дерева окончено\n\n");
            start = 0;    // Устанавливаем флаг завершения
        }
        else {
            root = CreateTree(root, D);  // Добавляем число в дерево
        }
    }

    // Печать дерева по уровням
    printf("Дерево:\n");
    print_tree(root);

    return 0;  // Завершение программы
}
