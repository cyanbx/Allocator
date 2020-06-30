import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

def func_nlogn(x, cof_nlogn):
	return cof_nlogn * x * np.log(x)

x = [1,2,3,4,5,6,7,8,9,10]
# y = np.array([0.708964, 2.87730, 6.53083, 11.5626, 18.3661, 26.0043, 35.6226, 45.7856, 58.9745, 71.0816])
y1 = [0.0930649, 0.0888079, 0.087959, 0.0821851, 0.0900343, 0.0931164, 0.0926603, 0.0919755, 0.0946618, 0.0961349]
y2 = [0.0836015, 0.0901506, 0.0907893, 0.0925909, 0.0934823, 0.0977491, 0.0961467, 0.0919799, 0.0886796, 0.0950415]
y3 = [0.0817066,0.096363,0.0963933,0.0963209,0.0904114,0.0895104,0.090578,0.0935039,0.0931063,0.0972077]



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