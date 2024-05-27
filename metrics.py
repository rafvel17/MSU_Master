import numpy as np
from sklearn.datasets import fetch_openml
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import roc_auc_score
from sklearn.metrics import precision_recall_curve, auc

scaler = StandardScaler()

np.random.seed(42)

data = fetch_openml(data_id=42608)
X, y = data['data'].drop(columns='Outcome').values, data['data']['Outcome'].astype(int).values


X_train, x_test, y_train, y_test = train_test_split(
    X, y, test_size=0.3, random_state=42
)
X_train = scaler.fit_transform(X_train)
x_test = scaler.transform(x_test)

tree = DecisionTreeClassifier(random_state = 42)
lr = LogisticRegression(random_state = 42)
knn = KNeighborsClassifier(n_neighbors = 5)
svm = SVC(probability=True)

tree = tree.fit(X_train, y_train)
lr = lr.fit(X_train, y_train)
knn = knn.fit(X_train, y_train)
svm = svm.fit(X_train, y_train)

predictions = [tree.predict_proba(x_test)[:,1], lr.predict_proba(x_test)[:,1], knn.predict_proba(x_test)[:,1], svm.predict_proba(x_test)[:,1]]
roc_auc = []
pr_curve = []

for y_pred in predictions:
    roc_auc.append(roc_auc_score(y_test, y_pred))
    precision, recall, thresholds = precision_recall_curve(y_test, y_pred)
    pr_curve.append(auc(recall, precision) )

print(np.argmax(np.array(roc_auc)) + 1, np.argmax(np.array(pr_curve)) + 1)
print (roc_auc, pr_curve)



