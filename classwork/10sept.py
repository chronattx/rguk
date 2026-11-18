def bubble(mat):
    i = len(mat)
    for x in range(i - 1):
        for y in range(i - x - 1):
            if mat[y] > mat[y + 1]:
                mat[y], mat[y + 1] = mat[y + 1], mat[y]
    return mat


mat = [7, 9, 5, 2, 4, 1]
mat2 = mat.copy()
print(bubble(mat))