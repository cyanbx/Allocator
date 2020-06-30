import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

def func_nlogn(x, cof_nlogn):
	return cof_nlogn * x * np.log(x)

x = [1,2,3,4,5,6,7,8,9,10]
# y = np.array([0.708964, 2.87730, 6.53083, 11.5626, 18.3661, 26.0043, 35.6226, 45.7856, 58.9745, 71.0816])
y1 = [0.219642  ,0.171867  ,0.17  ,0.183273  ,0.190242  ,0.176774  ,0.170748  ,0.174267  ,0.174981  ,0.17339  ]
y2 = [0.17857  ,0.170772  ,0.172059  ,0.170825  ,0.168595  ,0.167521  ,0.177944  ,0.182568  ,0.178723  ,0.177064 ]
y3 = [0.208085  ,0.169348  ,0.178989  ,0.174532  ,0.172871  ,0.168033  ,0.166095  ,0.171932  ,0.169621  ,0.171863]



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