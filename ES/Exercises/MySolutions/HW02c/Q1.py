from math import factorial
import matplotlib.pyplot as plt

def combinations(n, k):
    return factorial(n) / (factorial(k) * factorial(n - k))

def binomial(x, n, p):
    return combinations(n, x) * p**x * (1-p)**(n-x)

def makeBinomialDistPlot(n, p):
    values = [binomial(x, n, p) for x in range(n + 1)]
    labels = list(range(n + 1))

    plt.figure(figsize=(8, 5), dpi=100, label="HW02c - Q1")
    plt.title(f"Binomial distribution with n={n} & p={p}") 
    plt.bar(labels, values, color='gold', label="Probablity") 
    plt.xticks(labels)
    plt.legend()

    plt.show()

makeBinomialDistPlot(20, 0.5)
