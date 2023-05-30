import numpy as np


def calculate_loss_function(X, w, y):
    return np.linalg.norm((X @ w) - y) ** 2


l, n = 3, 4

calculate_loss_function(
    np.reshape(np.arange(0, 12), (l, n)),
    np.arange(0, n),
    np.arange(0, l)
)
