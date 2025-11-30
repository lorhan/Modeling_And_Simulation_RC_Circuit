import matplotlib.pyplot as plt
import json


with open('output.json', 'r') as file:
    data = json.load(file)

plt.plot(data["array1"], label = "pwm", alpha = 0.5)
plt.plot(data["array2"], label = "Uout", alpha = 0.5)
plt.grid()
plt.legend()
plt.show()