import matplotlib.pyplot as plt
import json


with open('output.json', 'r') as file:
    data = json.load(file)

plt.plot(data["array2"])
plt.show()