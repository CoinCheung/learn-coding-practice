import numpy as np
import matplotlib
import matplotlib.pyplot as plt



def main():
    xt = (np.arange(100) - 50) / 10
    y = - np.log(1 + np.exp(-xt))
    f, ax = plt.subplots()
    ax.plot(xt, y)
    plt.show()


if __name__ == "__main__":
    main()
