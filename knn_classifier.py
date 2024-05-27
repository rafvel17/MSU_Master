import numpy as np
import sklearn
from sklearn.datasets import load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score


class KNN_classifier:
    def __init__(self, n_neighbors: int, **kwargs):
        self.K = n_neighbors

    def fit(self, x: np.array, y: np.array):
        # TODO: напишите метод .fit() класса KNN_classifier
        # Эта функция принимает на вход два массива:
        # - x (набор признаков, массив размерности n x m, n - число объектов, m - размерность признакового описания)
        # - y (метки для обучения, одномерный массив размерности n)
        # Эта функция ничего не возвращает, она должна настроить внутренние параметры модели для дальнейшего использования
        # Подумайте, в чем заключается процесс обучения именно этого алгоритма?
        # Что этот алгоритм делает в тот момент, когда он получил обучающую выборку?
        # Реализуйте эту логику в коде
        self.X_train = x
        self.Y_train = y

    def predict(self, x: np.array):
        predictions = []
        # TODO: напишите метод .predict(x) класса KNN_classifier
        # Этот метод принимает на вход один массив x. Массив x - это двумерный массив объектов, для которых требуется получить предсказание
        # На выходе этой функции мы хотим получить одномерный массив predictions, размерности x.shape[0] (то есть для каждогго объекта массива x мы сделали своё предсказание)
        # Вспомните, как алгоритм KNN делает предсказание?
        # Реализуйте эту логику в коде
        for line in x:
          distances = []
          for elem in self.X_train:
            distances.append(np.linalg.norm(line - elem))
          distances = np.array(distances)
          nearest_neighbor_ids = distances.argsort()[:self.K]
          nearest_classes = self.Y_train[nearest_neighbor_ids].tolist()
          nearest = max(set(nearest_classes), key = nearest_classes.count)
          predictions.append(nearest)
        predictions = np.array(predictions)
        return predictions


X, y = load_breast_cancer(return_X_y=True)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33, random_state=42)
knn = KNN_classifier(n_neighbors=3)
knn.fit(X_train, y_train)
pred_1 = knn.predict(X_test)
print(accuracy_score(y_test,pred_1))
clf = KNeighborsClassifier(n_neighbors=3)
clf.fit(X_train, y_train)
pred_2 = clf.predict(X_test)
print(accuracy_score(y_test, pred_2))


