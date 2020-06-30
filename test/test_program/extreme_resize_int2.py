import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

def func_nlogn(x, cof_nlogn):
	return cof_nlogn * x * np.log(x)

x = [1,2,3,4,5,6,7,8,9,10]
# y = np.array([0.708964, 2.87730, 6.53083, 11.5626, 18.3661, 26.0043, 35.6226, 45.7856, 58.9745, 71.0816])
y1 = [0.0118385 ,0.00980478 ,0.00931604 ,0.00973333 ,0.00909841 ,0.00891359 ,0.0102488 ,0.0103176 ,0.00915224 ,0.0100098]
y2 = [0.0108066 ,0.00864114 ,0.00851398 ,0.00928979 ,0.0085244 ,0.00832667 ,0.0096653 ,0.00924929 ,0.00811681 ,0.00771111 ]
y3 = [0.0249732 ,0.0195826 ,0.0127756 ,0.0197457 ,0.0151304 ,0.0136642 ,0.0148113 ,0.0175971 ,0.0136928 ,0.0169095]



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