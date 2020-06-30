import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

def func_nlogn(x, cof_nlogn):
	return cof_nlogn * x * np.log(x)

x = [1,2,3,4,5,6,7,8,9,10]
# y = np.array([0.708964, 2.87730, 6.53083, 11.5626, 18.3661, 26.0043, 35.6226, 45.7856, 58.9745, 71.0816])
y1 = [0.00121264 ,0.00129062 ,0.00146224 ,0.00148353 ,0.00152734 ,0.00151184 ,0.0014016 ,0.00148693 ,0.00145609 ,0.00143458]
y2 = [0.0043864 ,0.00312248 ,0.0023281 ,0.00263175 ,0.00248904 ,0.00236083 ,0.00242659 ,0.00350404 ,0.00259828 ,0.0023764]
y3 = [0.00183215 ,0.00242681 ,0.00248865 ,0.0021936 ,0.002782 ,0.00228569 ,0.00240314 ,0.00294864 ,0.00327762 ,0.00629761]



# f_linear = np.poly1d(np.polyfit(x, y, 1))
# f_poly = np.poly1d(np.polyfit(x, y, 2))
# f_exp = np.poly1d(np.polyfit(x, np.log(y), 1))
# popt = curve_fit(func_nlogn, x, y)
# cof_nlogn = popt[0]


plt.plot(x, y1, label = "pool")
plt.plot(x, y2, label = "malloc")
plt.plot(x, y3, label = "std")
# plt.plot(x, f_linear(x), label = "Linear")
# plt.plot(x, f_poly(x), label = "Quadratic")
# plt.plot(x, np.exp(f_exp(x)), label = "Exponent")
# plt.plot(x, func_nlogn(x, cof_nlogn), label = "O(NlogN)")


plt.xlabel("ID")
plt.ylabel("Time/sec")
plt.legend()
plt.grid()
plt.show()