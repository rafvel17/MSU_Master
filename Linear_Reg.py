import numpy as np
from sklearn.model_selection import train_test_split

def r2(y_true, y_pred):
  return (1 - np.sum((y_pred - y_true)*(y_pred - y_true)) / np.sum((y_true - np.mean(y_true))*(y_true - np.mean(y_true))))

np.random.seed(42)

class LinearRegression:
    def __init__(self, **kwargs):
        self.coef_ = None

    def fit(self, x: np.array, y: np.array):
        add_ones = np.ones( (np.shape(x)[0], 1) )
        add_ones = add_ones.reshape( (-1,1) )
        x = np.concatenate ( (x, add_ones), axis = 1 )
        self.coef_ = (np.dot(np.dot(np.linalg.inv(np.dot(x.T, x)),x.T), y)).reshape(-1)
    def predict(self, x: np.array):
        add_ones = np.ones( (np.shape(x)[0], 1) )
        add_ones = add_ones.reshape( (-1,1) )
        x = np.concatenate ( (x, add_ones), axis = 1 )
        return (np.dot(x, self.coef_.T)).reshape(-1)

LinReg = LinearRegression()
    

filename_1 = '1.npy'
x_1 = np.load(filename_1).reshape(-1,2)
# X_train, x_test, y_train, y_test = train_test_split(x_1[:,0].reshape(-1,1), x_1[:,1], test_size=0.3, shuffle=True, random_state=42)
# print(X_train)
# add_ones = np.ones( (np.shape(X_train)[0], 1) )
# add_ones = add_ones.reshape( (-1,1) )
# print(add_ones)
# print(np.shape(add_ones), np.shape(X_train))
# print(np.concatenate ( (X_train, add_ones), axis = 1))

filename_2 = '2.npy'
x_2 = np.load(filename_2).reshape(-1,2)

filename_3 = '3.npy'
x_3 = np.load(filename_3).reshape(-1,2)

filename_4 = '4.npy'
x_4 = np.load(filename_4).reshape(-1,2)

filename_5 = '5.npy'
x_5 = np.load(filename_5).reshape(-1,2)

datasets = [x_1, x_2, x_3, x_4, x_5]
score_arr = []

for x in datasets:
    X_train, x_test, y_train, y_test = train_test_split(x[:,0], x[:,1], test_size=0.3, shuffle=True, random_state=42)
    LinReg.fit(X_train.reshape((-1,1)), y_train)
    pred = LinReg.predict(x_test.reshape((-1,1)))
    score_arr.append(r2(y_test, pred))
score_arr = np.array(score_arr)
print(np.argmax(score_arr), np.argmin(score_arr))
