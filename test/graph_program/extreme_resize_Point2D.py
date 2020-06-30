import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit

def func_nlogn(x, cof_nlogn):
	return cof_nlogn * x * np.log(x)

x = [1,2,3,4,5,6,7,8,9,10]
# y = np.array([0.708964, 2.87730, 6.53083, 11.5626, 18.3661, 26.0043, 35.6226, 45.7856, 58.9745, 71.0816])
y1 = [0.00129817 ,0.00244545 ,0.00143258 ,0.00151694 ,0.00262041 ,0.00178119 ,0.0014136 ,0.00196502 ,0.00140238 ,0.00151579]
y2 = [0.0023254 ,0.00225391 ,0.00335806 ,0.00286201 ,0.00326309 ,0.00242146 ,0.00262711 ,0.00222883 ,0.00476155 ,0.00243107]
y3 = [0.00242164 ,0.0037881 ,0.00362538 ,0.0028512 ,0.00250028 ,0.00263472 ,0.00312508 ,0.00301578 ,0.00252561 ,0.00262472]



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