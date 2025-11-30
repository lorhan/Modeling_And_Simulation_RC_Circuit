from scipy import signal
import numpy as np

# Example continuous transfer function H(s) = 1 / (s + 1)

R = 10
C = 33e-6
fsw = 10e3

w0 = 1/(R*C)
Tsw = 1/fsw
# Sampling time
Ts = Tsw/200

num = [w0]
den = [1, w0]

system = (num, den)

# Convert using Zero-Order Hold (ZOH)
d_num, d_den, dt = signal.cont2discrete(system, Ts, method='tustin')

print("Discrete numerator:", d_num)
print("Discrete denominator:", d_den)