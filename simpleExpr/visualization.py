import json
import matplotlib.pyplot as plt

def plot_function(x_points: list[float], y_points: list[float], title: str="",
                  xlabel: str = "x", ylabel: str = "y"):
  
    plt.figure()
    plt.plot(x_points, y_points)

    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)

    plt.grid()
    plt.show()

def plot_points(x_points: list[float], y_points: list[float],
                              title: str = "", xlabel: str = "x", ylabel: str = "y"):
 
    plt.figure()
    plt.scatter(x_points, y_points)

    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.legend()
    plt.show()


if __name__ == "__main__":
    config = {
        "plot_points": plot_points,
        "plot_function": plot_function
    }

    data = json.loads(input())
    config[data["type"]](**data["values"])
  
