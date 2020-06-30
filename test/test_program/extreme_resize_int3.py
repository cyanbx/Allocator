import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

def func_nlogn(x, cof_nlogn):
	return cof_nlogn * x * np.log(x)

x = [1,2,3,4,5,6,7,8,9,10]
# y = np.array([0.708964, 2.87730, 6.53083, 11.5626, 18.3661, 26.0043, 35.6226, 45.7856, 58.9745, 71.0816])
y1 = [0.00222584 ,0.00222529 ,0.00224259 ,0.00234001 ,0.00221321 ,0.00249773 ,0.00220447 ,0.0032209 ,0.00209935 ,0.00345779]
y2 = [0.0049588 ,0.00544258 ,0.00332104 ,0.00573214 ,0.00606696 ,0.00479722 ,0.00478269 ,0.00403048 ,0.00429592 ,0.00375316]
y3 = [0.00427085 ,0.0052274 ,0.0046279 ,0.00428267 ,0.00494764 ,0.0042973 ,0.00535544 ,0.0054559 ,0.00564969 ,0.00540861]



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