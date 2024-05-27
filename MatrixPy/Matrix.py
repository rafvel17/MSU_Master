class Matrix:
    def __init__(self, matrix):
        self.matrix = matrix
        self.rows = len(matrix)
        self.cols = len(matrix[0])

    def reduce_to_row_echelon_form(self):
        lead = 0
        for r in range(self.rows):
            if lead >= self.cols:
                return
            i = r
            while self.matrix[i][lead] == 0:
                i += 1
                if i == self.rows:
                    i = r
                    lead += 1
                    if self.cols == lead:
                        return
            self.matrix[i], self.matrix[r] = self.matrix[r], self.matrix[i]
            lv = self.matrix[r][lead]
            self.matrix[r] = [mrx / float(lv) for mrx in self.matrix[r]]
            for i in range(self.rows):
                if i != r:
                    lv = self.matrix[i][lead]
                    self.matrix[i] = [v1 - v2 * lv for v1, v2 in zip(self.matrix[i], self.matrix[r])]
            lead += 1

    def rank(self):
        self.reduce_to_row_echelon_form()
        rank = 0
        for row in self.matrix:
            if any(row):
                rank += 1
        return rank

    def determinant(self):
        det = 0
        if self.rows == self.cols:
            if self.rows == 1:
                det = self.matrix[0][0]
            elif self.rows == 2:
                det = self.matrix[0][0] * self.matrix[1][1] - self.matrix[0][1] * self.matrix[1][0]
            else:
                for i, row in enumerate(self.matrix):
                    minor = [row[:i] + row[i+1:] for row in self.matrix[1:]]
                    det += ((-1) ** i) * row[i] * Matrix(minor).determinant()
        return det

    def inverse(self):
        if self.rows == self.cols:
            det = self.determinant()
            if det != 0:
                cofactors = [[((-1) ** (i + j)) * Matrix([row[:j] + row[j+1:] for k, row in enumerate(self.matrix) if k != i]).determinant() for j in range(self.cols)] for i in range(self.rows)]
                adjugate = Matrix(cofactors).transpose()
                inverse = [[elem / det for elem in row] for row in adjugate.matrix]
                return inverse
        return None

    def solve_linear_system(self, constants):
        if self.rows == self.cols:
            det = self.determinant()
            if det != 0:
                inverse_matrix = self.inverse()
                if inverse_matrix:
                    solutions = [sum(x * y for x, y in zip(row, constants)) for row in inverse_matrix]
                    return solutions
        return None

    def transpose(self):
        transposed = [[self.matrix[j][i] for j in range(self.rows)] for i in range(self.cols)]
        return Matrix(transposed)











# Создание матрицы
matrix = Matrix([[1, 2, 3], [4, 5, 6], [7, 8, 10]])

# Приведение матрицы к ступенчатому виду и вычисление ранга
matrix.reduce_to_row_echelon_form()
print(matrix.matrix)
print("Rank:", matrix.rank())

# Вычисление определителя
print("Determinant:", matrix.determinant())

# Вычисление обратной матрицы
inverse_matrix = matrix.inverse()
print("Inverse matrix:", inverse_matrix)

# Решение линейной системы
constants = [1, 2, 3]
solutions = matrix.solve_linear_system(constants)
print("Solution to linear system:", solutions)

# Транспонирование матрицы
transposed_matrix = matrix.transpose()
print("Transposed matrix:", transposed_matrix.matrix)