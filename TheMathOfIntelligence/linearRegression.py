from sklearn import linear_model
import random

regr = linear_model.LinearRegression()
# let's create a linear function with some error called f
def f(x):
    res = x* 25 + 3
    error = res * random.uniform(-0.01, 0.01) # you can play with the error to see how it affects the result
    return res + error

values = []
# now using f we are going to create 300 values.
for i in range(0, 300):
    x = random.uniform(1, 1000)
    y = f(x)
    values.append((x, y))

# split the values into two series instead a list of tuples
x, y = zip(*values)
max_x = max(x)
min_x = min(x)
# split the values in train and data.
train_data_X = map(lambda x: [x], list(x[:-20]))
train_data_Y = list(y[:-20])
test_data_X = map(lambda x: [x], list(x[-20:]))
test_data_Y = list(y[-20:])

# feed the linear regression with the train data to obtain a model.
regr.fit(train_data_X, train_data_Y)
# check that the coeffients are the expected ones.
m = regr.coef_[0]
b = regr.intercept_
print(' y = {0} * x + {1}'.format(m, b))