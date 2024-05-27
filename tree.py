import numpy as np
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.tree import DecisionTreeClassifier
from sklearn.tree import DecisionTreeRegressor
np.random.seed(42)

N_ESTIMATORS = 10
MAX_DEPTH = 12
SUBSPACE_DIM = 2


import numpy as np

class sample(object):
  def __init__(self, X, n_subspace):
    self.idx_subspace = self.random_subspace(X, n_subspace)

  def __call__(self, X, y):
    idx_obj = self.bootstrap_sample(X)
    X_sampled, y_sampled = self.get_subsample(X, y, self.idx_subspace, idx_obj)
    return X_sampled, y_sampled

  @staticmethod
  def bootstrap_sample(X, random_state=42):
    return np.unique(np.random.choice(np.shape(X)[0],np.shape(X)[0],replace = True))
  @staticmethod
  def random_subspace(X, n_subspace, random_state=42):
    return np.random.choice(np.shape(X)[1],n_subspace,replace = False)

  @staticmethod
  def get_subsample(X, y, idx_subspace, idx_obj):
    X_aux = X[:,idx_subspace]
    return X_aux[idx_obj], y[idx_obj]


class random_forest(object):
  def __init__(self, n_estimators: int, max_depth: int, subspaces_dim: int, random_state: int):
    self.n_estimators = n_estimators
    self.max_depth = max_depth
    self.subspaces_dim = subspaces_dim
    self.random_state = random_state

  def fit(self, X, y):
    self.models = []
    self.subspace_idx = np.zeros ( (self.n_estimators, self.subspaces_dim), dtype=int)
    for i in range(self.n_estimators):
        self.subspace_idx[i] = sample(X,self.subspaces_dim).idx_subspace
        self.models.append(DecisionTreeClassifier(max_depth=self.max_depth, random_state=self.random_state).fit(X[:,self.subspace_idx[i]],y))

  def predict(self, X):
    predictions = []
    for i in range(self.n_estimators):
        predictions.append(self.models[i].predict(X[:,self.subspace_idx[i]]))
    preds = np.array(predictions)
    return np.round(np.mean(preds, axis = 0))


X, y = load_iris(return_X_y=True)

X_train, x_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42, shuffle=True)



rf = random_forest(N_ESTIMATORS, MAX_DEPTH, SUBSPACE_DIM, 42)
rf.fit(X_train, y_train)
preds = rf.predict(x_test)
acc = accuracy_score(y_test, preds)
print(acc)