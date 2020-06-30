import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

def func_nlogn(x, cof_nlogn):
	return cof_nlogn * x * np.log(x)

x = [1,2,3,4,5,6,7,8,9,10]
# y = np.array([0.708964, 2.87730, 6.53083, 11.5626, 18.3661, 26.0043, 35.6226, 45.7856, 58.9745, 71.0816])
y1 = [0.0581324,0.0412402,0.0492536,0.0500081,0.0462552,0.0502379,0.0513679,0.0488331,0.0476854,0.0458918]
y2 = [0.0641558,0.0497816,0.0496601,0.0460449,0.0573007,0.0476098,0.0475685,0.0498133,0.049995,0.0507194]
y3 = [0.0662486,0.0488024,0.0534967,0.0480653,0.0485695,0.0488182,0.0484383,0.0484161,0.0533349,0.0471311]



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