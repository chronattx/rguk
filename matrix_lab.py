class Matrix:
    def __init__(self, s):
        self.s = s
        self.cols_n = len(s[0])
        self.rows_n = len(s)

    def __getitem__(self, key):
        return self.s[key]

    def __add__(self, other):
        if self.cols_n != other.cols_n or self.rows_n != other.rows_n:
            return None

        res = []
        for i in range(self.rows_n):
            res.append([self[i][j] + other[i][j] for j in range(self.cols_n)])

        return Matrix(res)

    def __setitem__(self, key, value):
        self.s[key] = value

    def __len__(self):
        return (self.rows_n, self.cols_n)
    
    def __repr__(self):
        res = ''
        for row in self.s:
            res += '\t'.join(str(x) for x in row) + '\n'
        return res

    def __neg__(self):
        res = []
        for row in self.s:
            res.append([-x for x in row])
        return Matrix(res)

    def __sub__(self, other):
        return self + (-other)
        
    def print_matrix(self):
        print(self)

    def __mul__(self, other):
        res = []
        if isinstance(other, int) or isinstance(other, float):
            for row in self.s:
                res.append([x * other for x in row])
            return Matrix(res)
        if isinstance(other, Matrix):
            if self.cols_n != other.rows_n:
                return 1
            res = Matrix([[0 for _ in range(other.cols_n)] for _ in range(self.rows_n)])
            for i in range(res.rows_n):
                for j in range(res.cols_n):
                    res[i][j] = sum(self[i][x] * other[x][j] for x in range(self.cols_n))
            return res
        return None

    def t(self):
        res = Matrix([[0 for _ in range(self.rows_n)] for _ in range(self.cols_n)])
        for i in range(self.rows_n):
            for j in range(self.cols_n):
                res[j][i] = self[i][j]
        return res

    def main_diagonal(self):
        if self.cols_n == self.rows_n: 
            return [self[i][i] for i in range(self.rows_n)]
        return None


    def secondary_diagonal(self):
        if self.cols_n == self.rows_n: 
            return [self[i][self.rows_n - 1 - i] for i in range(self.rows_n)]
        return None


    def trace(self):
        return sum(self.main_diagonal())

    def get_minor(self, i, j):
        if self.cols_n != self.rows_n:
            return None
        res = []
        for i1 in range(self.cols_n):
            if i1 == i:
                continue
            s = []
            for j1 in range(self.cols_n):
                if j1 == j:
                    continue
                s.append(self[i1][j1])
            res.append(s)
        return Matrix(res)
                
    def cofactor(self, i, j):
        return self.get_minor(i, j) * (-1) ** (i + j)
    
    def determinant(self):
        if self.cols_n != self.rows_n:
            return None
        if self.cols_n == 1:
            return self[0][0]
        res = 0
        for col_n in range(self.cols_n):
            res += (-1) ** col_n * self[0][col_n] * self.get_minor(0, col_n).determinant()
        return res

    def copy(self):
        res = Matrix([[x for x in row] for row in self])

    def is_identity(self, eps=1e-12):
        if self.cols_n != self.rows_n:
            return None

        e = identity(self.cols_n)
        for i in range(self.cols_n):
            for j in range(self.cols_n):
                if abs(self[i][j] - e[i][j]) > eps:
                    return False
        return True
        

    def inverse_matrix(self, eps=1e-12):
        if self.cols_n != self.rows_n:
            return None

        e = Matrix([[1 if i == j else 0 for j in range(self.cols_n)] for i in range(self.cols_n)])
        ae = Matrix([[0 for _ in range(self.cols_n * 2)] for _ in range(self.cols_n)])
        for i in range(ae.rows_n):
            for j in range(ae.cols_n):
                if j < self.cols_n:
                    ae[i][j] = self[i][j]
                else:
                    ae[i][j] = e[i][j - self.cols_n]

        for i in range(ae.rows_n):
            if abs(ae[i][i]) < eps:
                swap_row = -1
                for k in range(i + 1, ae.rows_n):
                    if abs(ae[k][i]) >= eps:
                        swap_row = k
                        break
                if swap_row == -1:
                    return None
                ae[i], ae[swap_row] = ae[swap_row], ae[i]

            divisor = ae[i][i]
            for j in range(ae.cols_n):
                ae[i][j] = ae[i][j] / divisor

            for i2 in range(ae.rows_n):
                if i == i2:
                    continue
                multiplier = ae[i2][i]
                for j2 in range(ae.cols_n):
                    ae[i2][j2] = ae[i2][j2] - ae[i][j2] * multiplier

        res = Matrix([[0 for x in row] for row in self])
        for i in range(res.rows_n):
            for j in range(res.cols_n):
                res[i][j] = ae[i][res.cols_n + j]
        return res

    def get_columns(self):
        res = []
        for j in range(self.rows_n):
            s = []
            for i in range(self.cols_n):
                s.append(self[i][j])
            res.append(s)
        return res

    def report(self):
        print(f"Размер: {self.rows_n} × {self.cols_n}")
        print(f"Минимальный элемент: {min(min(x) for x in self)}")
        print(f"Максимальный элемент: {max(max(x) for x in self)}")
        print(f"Сумма элементов: {sum(sum(x) for x in self)}")
        print(f"Среднее значение: {sum(sum(x) for x in self) / (self.cols_n * self.rows_n)}")
        print()
        print(f"Суммы строк: {', '.join(str(sum(x)) for x in self)}")
        print(f"Суммы столбцов: {', '.join(str(sum(x)) for x in self.get_columns())}")


class Calculator:
    def __init__(self):
        self.matrix_dict = dict()

    def get_matrix(self):
        while True:
            print("Укажите число строк и столбцов")
            answer = input().split()
            if len(answer) != 2 or not answer[0].isnumeric() or not answer[1].isnumeric():
                print("Введите 2 положительных числа")
            elif int(answer[0]) <= 0 or int(answer[1]) <= 0:
                print("Вводите положительные числа")
            else:
                break
        while True:
            res = input_matrix(int(answer[0]), int(answer[1]))
            if res == 1:
                print("Вводите числа")
            elif res == 2:
                print("Неверное количество столбцов")
            else:
                break
        self.add(Matrix(res), input("Введите имя матрицы: "))

    def add(self, matrix, name):
        self.matrix_dict[name] = matrix

    def print_list(self):
        for x in self.matrix_dict:
            print(x)

    def print_matrix(self):
        while True:
            answer = input("Введите имя матрицы для вывода: ")
            if answer not in self.matrix_dict:
                print("Такой матрицы нет")
            else:
                break
        self.matrix_dict[answer].print_matrix()

    def is_empty(self):
        return len(self.matrix_dict) == 0

    def get_names(self, n):
        s = ["Введите имя матрицы: ", "Введите имена 2 матриц: "]
        while True:
            answer = input(s[n - 1]).split()
            if len(answer) != n:
                print("Неверное количество имён")
            elif any(a not in self.matrix_dict for a in answer):
                print("Неверное/ые имя/имена")
            else:
                break
        return answer

    def summa(self, name1, name2):
        a = self.matrix_dict[name1]
        b = self.matrix_dict[name2]
        if a.cols_n != b.cols_n or a.rows_n != b.rows_n:
            print("Матрицы разных размеров не складываются")
        else:
            res = a + b
            print(res)
            self.add(res, input("Введите имя новой матрицы: "))

    def minus(self, name1, name2):
        a = self.matrix_dict[name1]
        b = self.matrix_dict[name2]
        if a.cols_n != b.cols_n or a.rows_n != b.rows_n:
            print("Матрицы разных размеров не вычитаются")
        else:
            res = a - b
            print(res)
            self.add(res, input("Введите имя новой матрицы: "))

    def multi_num(self, name1):
        while True:
            answer = input("Введите множитель: ")
            try:
                multiplier = float(answer)
            except ValueError:
                print("Введите число")
                continue
            break
        res = self.matrix_dict[name1] * float(multiplier)
        print(res)
        self.add(res, input("Введите имя новой матрицы: "))

    def multi_mat(self, name1, name2):
        a = self.matrix_dict[name1]
        b = self.matrix_dict[name2]
        if a.cols_n != b.rows_n:
            print("Кол-во столбцов первой должно быть ровно кол-ву строк второй")
        else:
            res = a * b
            print(res)
            self.add(res, input("Введите имя новой матрицы: "))

    def transp(self, name1):
        res = self.matrix_dict[name1].t()
        print(res)
        self.add(res, input("Введите имя новой матрицы: "))

    def deter(self, name1):
        a = self.matrix_dict[name1]
        if a.rows_n != a.cols_n:
            print("Определитель только для квадратных матриц")
            return 0
        print(a.determinant())

    def inver(self, name1):
        res = self.matrix_dict[name1].inverse_matrix()
        if res is None:
            print("Обратная не нашлась")
            return 0
        print(res)
        self.add(res, input("Введите имя новой матрицы: "))

    def repor(self, name1):
        self.matrix_dict[name1].report()

    def do_action(self, action):
        if action == 1:
            self.get_matrix()
        else:
            if self.is_empty():
                print("Записанных матриц нет")
                return 0
            self.print_list()
            if action == 2:
                self.print_matrix()
            if action == 3:
                names = self.get_names(2)
                self.summa(names[0], names[1])
            if action == 4:
                names = self.get_names(2)
                self.minus(names[0], names[1])
            if action == 5:
                names = self.get_names(1)
                self.multi_num(names[0])
            if action == 6:
                names = self.get_names(1)
                self.transp(names[0])
            if action == 7:
                names = self.get_names(2)
                self.multi_mat(names[0], names[1])
            if action == 8:
                names = self.get_names(1)
                self.deter(names[0])
            if action == 9:
                names = self.get_names(1)
                self.inver(names[0])
            if action == 10:
                names = self.get_names(1)
                self.repor(names[0])


def input_matrix(rows, cols):
    matrix = []
    for i in range(rows):
        row = []
        for x in input(f"Введите строку {i + 1}: ").split():
            try:
                x = float(x)
            except ValueError:
                return 1
            row.append(x)
            
        if len(row) != cols:
            return 2
        matrix.append(row)

    return matrix

def identity(n):
    return Matrix([[1 if i == j else 0 for j in range(n)] for i in range(n)])
   
def print_menu():
    print("""МАТРИЧНЫЙ КАЛЬКУЛЯТОР

1. Ввести матрицу
2. Вывести матрицу
3. Сложить две матрицы
4. Вычесть две матрицы
5. Умножить матрицу на число
6. Транспонировать матрицу
7. Умножить две матрицы
8. Найти определитель
9. Найти обратную матрицу
10. Вывести характеристики матрицы
0. Завершить программу""")

def task_1():
    m = int(input())
    n = int(input())
    if m < 1 or n < 1:
        print("not correct m or n")
        return 1
    
    print(f"Количество строк: {m}\nКоличество столбцов: {n}")

    m = input_matrix(m, n)
    if m == 1:
        print("not correct amount of cols")
        return 1

    matrix = Matrix(m)
    matrix.print_matrix()

def task_2():
    a = Matrix([[1, 2], [3, 4]])
    b = Matrix([[5, 6], [7, 8]])
    print('a + b')
    print(a + b)
    print('a - b')
    print(a - b)

def task_3():
    a = Matrix([[1, 2], [3, 4]])
    k = 3
    print('a * k')
    print(a * k)

def task_4():
    a = Matrix([[1, 2, 3], [4, 5, 6]])
    print('a^t')
    print(a.t())

def task_5():
    a = Matrix([[1, 2], [3, 4]])
    b = Matrix([[5, 6], [7, 8]])
    print('a * b')
    print(a * b)

def task_6():
    pass

def task_7():
    a = Matrix([[3, 5], [2, 4]])
    print("determinant")
    print(a.determinant())

def task_8():
    a = Matrix([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    print("cofactor 01")
    print(a.cofactor(0, 1))

def task_9():
    a = Matrix([[4, 7], [2, 6]])
    print("inverse")
    print(a.inverse_matrix())

def task_10():
    a = Matrix([[4, 7], [2, 6]])
    b = a.inverse_matrix()
    c = a * b
    print("is identity")
    print(c.is_identity())

def task_11():
    a = Matrix([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    a.report()
 
def main():
    # task_1()

    answers = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '0']
    calc = Calculator()

    calc.add(Matrix([[1, 2, 3], [4, 5, 6], [7, 8, 9]]), 'a')
    calc.add(Matrix([[6, 9, 3], [2, 7, 1], [9, 9, 5]]), 'b')

    while True:
        print_menu()
        answer = input()
        if answer not in answers:
            print("Введите число от 0 до 10")
            continue

        answer = int(answer)
        if answer == 0:
            print("До свидания")
            break
        calc.do_action(answer)
        
        # if answer == 1:
        #     while True:
        #         print("Укажите число строк и столбцов")
        #         answer = input().split()
        #         if len(answer) != 2 or not answer[0].isnumeric() or not answer[1].isnumeric():
        #             print("Введите 2 положительных числа")
        #         elif int(answer[0]) <= 0 or int(answer[1]) <= 0:
        #             print("Вводите положительные числа")
        #         else:
        #             break
        #     while True:
        #         res = input_matrix(int(answer[0]), int(answer[1]))
        #         if res == 1:
        #             print("Вводите числа")
        #         elif res == 2:
        #             print("Неверное количество столбцов")
        #         else:
        #             break
        #     calc.add(Matrix(res), input("Введите имя матрицы: "))

        # elif answer == 2:
        #     if len(calc.matrix_dict) == 0:
        #         print('Записанных матриц нет')
        #         continue
        #     calc.print_list()
        #     while True:
        #         answer = input("Введите имя матрицы для вывода: ")
        #         if answer not in calc.matrix_dict:
        #             print("Такой матрицы нет")
        #         else:
        #             break
        #     calc.print_matrix(answer)

        # elif answer == 3:
        #     if len(calc.matrix_dict) == 0:
        #         print('Записанных матриц нет')
        #         continue
        #     while True:
        #         calc.print_list()
        #         answer = input("Введите имена двух матриц для сложения: ").split()
        #         if len(answer) != 2 or answer[0] not in calc.matrix_dict or answer[1] not in calc.matrix_dict:
        #             print("Неверный ввод")
        #         else:
        #             break
            
        #     a = calc.matrix_dict[answer[0]]
        #     b = calc.matrix_dict[answer[1]]
        #     if a.cols_n != b.cols_n or a.rows_n != b.rows_n:
        #         print("Матрицы разных размеров не складываются")
        #     else:
        #         res = a + b
        #         print(res)
        #         calc.add(res, input("Введите имя матрицы: "))

        # elif answer == 4:
        #     if len(calc.matrix_dict) == 0:
        #         print('Записанных матриц нет')
        #         continue
        #     while True:
        #         calc.print_list()
        #         answer = input("Введите имена двух матриц для вычитания: ").split()
        #         if len(answer) != 2 or answer[0] not in calc.matrix_dict or answer[1] not in calc.matrix_dict:
        #             print("Неверный ввод")
        #         else:
        #             break
            
        #     a = calc.matrix_dict[answer[0]]
        #     b = calc.matrix_dict[answer[1]]
        #     if a.cols_n != b.cols_n or a.rows_n != b.rows_n:
        #         print("Матрицы разных размеров не вычитаются")
        #     else:
        #         res = a - b
        #         print(res)
        #         calc.add(res, input("Введите имя матрицы: "))

        # elif answer == 5:
        #     if len(calc.matrix_dict) == 0:
        #         print('Записанных матриц нет')
        #         continue

        #     while True:
        #         calc.print_list()
        #         answer = input("Введите имя матрицы для умножения: ")
        #         if answer not in calc.matrix_dict:
        #             print("Неверный ввод")
        #         else:
        #             break

        #     a = calc.matrix_dict[answer]
        #     while True:
        #         answer = input("Введите множитель: ")
        #         try:
        #             multiplier = float(answer)
        #         except ValueError:
        #             print("Введите число")
        #             continue
        #         break
        #     res = a * float(answer)
        #     print(res)
        #     calc.add(res, input("Введите имя матрицы: "))

        # elif answer == 6:
        #     if len(calc.matrix_dict) == 0:
        #         print('Записанных матриц нет')
        #         continue

        #     while True:
        #         calc.print_list()
        #         answer = input("Введите имя матрицы для транспонирования: ")
        #         if answer not in calc.matrix_dict:
        #             print("Неверный ввод")
        #         else:
        #             break
        #     res = calc.matrix_dict[answer].t()
        #     print(res)
        #     calc.add(res, input("Введите имя матрицы: "))

        # elif answer == 7:
        #     if len(calc.matrix_dict) == 0:
        #         print('Записанных матриц нет')
        #         continue
        #     while True:
        #         calc.print_list()
        #         answer = input("Введите имена двух матриц для умножения: ").split()
        #         if len(answer) != 2 or answer[0] not in calc.matrix_dict or answer[1] not in calc.matrix_dict:
        #             print("Неверный ввод")
        #         else:
        #             break
            
        #     a = calc.matrix_dict[answer[0]]
        #     b = calc.matrix_dict[answer[1]]
        #     if a.cols_n != b.rows_n:
        #         print("Кол-во столбцов первой должно быть ровно кол-ву строк второй")
        #     else:
        #         res = a * b
        #         print(res)
        #         calc.add(res, input("Введите имя матрицы: "))

        # elif answer == 8:
        #     if len(calc.matrix_dict) == 0:
        #         print('Записанных матриц нет')
        #         continue

        #     while True:
        #         calc.print_list()
        #         answer = input("Введите имя матрицы для нахождения определителя: ")
        #         if answer not in calc.matrix_dict:
        #             print("Неверный ввод")
        #         else:
        #             break
        #     a = calc.matrix_dict[answer]
        #     if a.rows_n != a.cols_n:
        #         print("Определитель только для квадратных матриц")
        #         continue
        #     print(a.determinant())

        # elif answer == 9:
        #     if len(calc.matrix_dict) == 0:
        #         print('Записанных матриц нет')
        #         continue

        #     while True:
        #         calc.print_list()
        #         answer = input("Введите имя матрицы для нахождения обратной: ")
        #         if answer not in calc.matrix_dict:
        #             print("Неверный ввод")
        #         else:
        #             break
        #     res = calc.matrix_dict[answer].inverse_matrix()
        #     if res is None:
        #         print("Обратная не нашлась")
        #         continue
        #     print(res)
        #     calc.add(res, input("Введите имя матрицы: "))

        # elif answer == 10:
        #     if len(calc.matrix_dict) == 0:
        #         print('Записанных матриц нет')
        #         continue

        #     calc.print_list()
        #     while True:
        #         answer = input("Введите имя матрицы для вывода характеристики: ")
        #         if answer not in calc.matrix_dict:
        #             print("Неверный ввод")
        #         else:
        #             break
        #     calc.matrix_dict[answer].report()


    return 0


main()