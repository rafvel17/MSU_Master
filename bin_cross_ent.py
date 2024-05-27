import sklearn
from sklearn.datasets import load_digits
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler




import numpy as np

np.random.seed(42)
# Функция подсчета градиента
def gradient(y_true: int, y_pred: float, x: np.array) -> np.array:
    """
    y_true - истинное значение ответа для объекта x
    y_pred - значение степени принадлежности объекта x классу 1, предсказанное нашей моделью
    x - вектор признакового описания данного объекта

    На выходе ожидается получить вектор частных производных H по параметрам модели, предсказавшей значение y_pred
    Обратите внимание, что размерность этого градиента должна получиться на единицу больше размерности x засчет своободного коэффициента a0
    """
    grad = (1/(1+np.exp(-y_pred)) - y_true) * np.concatenate( (x, np.array([1])) ) 
    #grad = np.concatenate( (grad, np.array( [1 / ( 1+np.exp(-y_pred) )  - y_true])) )
    return grad


# Функция обновления весов
def update(alpha: np.array, gradient: np.array, lr: float):
    """
    alpha: текущее приближения вектора параметров модели
    gradient: посчитанный градиент по параметрам модели
    lr: learning rate, множитель перед градиентом в формуле обновления параметров
    """
    alpha_new = alpha - lr*gradient
    return alpha_new


# функция тренировки модели
def train(
    alpha0: np.array, x_train: np.array, y_train: np.array, lr: float, num_epoch: int
):
    """
    alpha0 - начальное приближение параметров модели
    x_train - матрица объект-признак обучающей выборки
    y_train - верные ответы для обучающей выборки
    lr - learning rate, множитель перед градиентом в формуле обновления параметров
    num_epoch - количество эпох обучения, то есть полных 'проходов' через весь датасет
    """
    alpha = alpha0.copy()
    for epo in range(num_epoch):
        for i, x in enumerate(x_train):
            # TODO: write your code here
            alpha = update(alpha, gradient(y_train[i], np.sum(np.concatenate((x, np.array([1]))) * alpha, dtype = float), x), lr) 
    return alpha


mnist = load_digits()
X, y = load_digits(return_X_y=True)

# Разбиение на train и test
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1, shuffle=True )

# Предобработка
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# обучение модели
#clf = LogisticRegression()
#clf.fit(X_train, y_train)
#score = clf.score(X_test, y_test)


alpha = train(np.zeros(np.size(X_train[0])+1), X_train, y_train, 0.5, 30)
alpha_0 = np.zeros(np.size(X_train)
#score = np.linalg.norm(y_test - np.concatenate( (X_test, np.array([1]) ))   *   alpha) 
#print(score)