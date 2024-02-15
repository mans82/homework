import matplotlib.pyplot as plt
import numpy as np


def geometric_distribution(p, x):
    return p * ((1 - p) ** (x - 1))


x_points = np.array([x for x in range(1, 4)])
y_points = np.array([geometric_distribution(0.25, x) for x in x_points])
plt.figure(figsize=(8, 5), dpi=100)
plt.plot(x_points, y_points, marker='o', linestyle='dashed', color='gold')
plt.xlabel("Numbers of examination", fontdict={'size': 15})
plt.ylabel("Possibility", fontdict={'size': 15})
plt.grid(linestyle='--', linewidth=0.5)
plt.xticks(range(1, 4))
for i in range(0, len(y_points)):
    plt.annotate(y_points[i], xy=(x_points[i], y_points[i]))
plt.show()
print(f"p(X|X < 4) = p(1) + p(2) + p(3) = {geometric_distribution(0.25, 1)} + {geometric_distribution(0.25, 2)} + {geometric_distribution(0.25, 3)}")
print(f"= {geometric_distribution(0.25, 1) + geometric_distribution(0.25, 2) + geometric_distribution(0.25, 3)}")