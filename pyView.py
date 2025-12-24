import matplotlib.pyplot as plt
import json


with open('output.json', 'r') as file:
    data = json.load(file)

plt.plot(data["pwmSignal"], label = "pwm", alpha = 0.5)
plt.plot(data["outputSamples"], label = "Uout", alpha = 0.5, color = "red")
plt.grid()
plt.legend()
plt.show()