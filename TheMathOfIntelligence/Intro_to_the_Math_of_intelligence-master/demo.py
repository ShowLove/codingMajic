#The optimal values of m and b can be actually calculated with way less effort than doing a linear regression. 
#this is just to demonstrate gradient descent

"""
Goal: We want to be able to predict the calories lost for a new person
given the distance they biked (Optimize 'b' and 'm')

(Our plot)
|y (y = number of calories lost )
|
|_______x  (x = distance biked)

Our labeled data has a bunch of points on it 
we want to draw a straight line that hits the most possible points
y = m*x + b
m = slope
b = y intercept

Our error value is a measure of closeness
(1/N)*∑.(i=1,n)(y.i - y̅)^2
y̅ = m*x.i + b)
totalError += (y - (m * x + b)) ** 2

We take the partial derivative of the error function to get the gradient
Partial derivative with respect to b and m (to perform gradient descent)
(∂/∂m) = (2/N)*∑.(i=1,N)[(-x.i)(y.i - y̅)]
(∂/∂b) = (2/N)*∑.(i=1,N)[(-1)(y.i - y̅)]

To solve for the gradient, we iterate through our data points using our 
new m and b values and compute the partial derivatives. This new gradient tells 
us the slope of our cost function at our current position (current parameter values) 
and the direction we should move to update our parameters. The size of our update is 
controlled by the learning rate.
"""

from numpy import *

# y = mx + b
# m is slope, b is y-intercept
"""
We want to see how far away the the y value of the actual data is 
from the equivalent y value of of the line we are testing
@param b, m : The b and m value of the line we are testing for error.  
@param points : the actual points representing real data
"""
def compute_error_for_line_given_points(b, m, points):
    totalError = 0
    for i in range(0, len(points)):
        x = points[i, 0]
        y = points[i, 1]
        totalError += (y - (m * x + b)) ** 2
    return totalError / float(len(points))
"""
Calculates the partial derivative of the cost/error function with respect to 
b and m of the equation y=mx+b.
"""
def step_gradient(b_current, m_current, points, learningRate):
    b_gradient = 0
    m_gradient = 0
    N = float(len(points))
    for i in range(0, len(points)):
        # this represents myTODO
        x = points[i, 0]
        y = points[i, 1]

        """
        Gradient =  (Change in Y)/(Change in X) = slope  
        We're looking at a 3d graph of m,b with error as a 'z' dimesion.
        i.e partial deriv w/respec to 'm' : slices the 3d graph into a 2d graph
        with m as x and error as y ('realy it's z'). The aswer can be seen as the slope at that point.
        ie slope of -2; down 2 and right one. 2 up two and right one.
        #(∂/∂m) = (2/N)*∑.(i=1,N)[(-x.i)(y.i - y̅)]
        #(∂/∂b) = (2/N)*∑.(i=1,N)[(-1)(y.i - y̅)]
        """
        b_gradient += -(2/N) * (y - ((m_current * x) + b_current))
        m_gradient += -(2/N) * x * (y - ((m_current * x) + b_current))

    """
    # new_b,new_m will be fed back into this function, each iteration is a step closer
    # to the line with least error.
    Learning rate: The size of these steps is called the learning rate. With a high learning rate we 
    can cover more ground each step, but we risk overshooting the lowest point since the 
    slope of data is constantly changing. With a very low learning rate, we can 
    confidently move in the direction of the negative gradient since we are recalculating 
    it so frequently. A low learning rate is more precise, but calculating the gradient is 
    time-consuming, so it will take us a very long time to get to the bottom.
    """
    # We subtract because the derivatives point in direction of steepest ascent
    # The right side of this equation will always be negative because we are decending (slope)
    new_b = b_current - (learningRate * b_gradient)
    new_m = m_current - (learningRate * m_gradient)
    return [new_b, new_m]

"""
@param starting_b, starting_m : starting line y=mx+b, points : points holding actual data
@param learning_rate : 
"""
def gradient_descent_runner(points, starting_b, starting_m, learning_rate, num_iterations):
    b = starting_b
    m = starting_m
    # At it's final iteration we will have two values b,m of a line with the least error
    for i in range(num_iterations):
        b, m = step_gradient(b, m, array(points), learning_rate)
    return [b, m]

def run():
    points = genfromtxt("data.csv",  =",")
    learning_rate = 0.0001
    initial_b = 0 # initial y-intercept guess
    initial_m = 0 # initial slope guess
    num_iterations = 1000
    print "Starting gradient descent at b = {0}, m = {1}, error = {2}".format(initial_b, initial_m, compute_error_for_line_given_points(initial_b, initial_m, points))
    print "Running..."
    [b, m] = gradient_descent_runner(points, initial_b, initial_m, learning_rate, num_iterations)
    print "After {0} iterations b = {1}, m = {2}, error = {3}".format(num_iterations, b, m, compute_error_for_line_given_points(b, m, points))

if __name__ == '__main__':
    run()



'''
******************
input vs label
******************
Briefly, feature is input; label is output.

A feature is one column of the data in your input set. 
For instance, if you're trying to predict the type of pet someone will choose, your 
input features might include age, home region, family income, etc. 
The label is the final choice, such as dog, fish, iguana, rock, etc.

Once you've trained your model, you will give it sets of new input 
containing those features; it will return the predicted "label" (pet type) for that person.

In our case, our data is ...
Input: Distance in meters someone bikes 
Output: Calories the person lost

Sometimes our data is labeled, sometimes it isn't
hence: supervised_learning(isLabeled), un_supervised_learning(ins'tLabeled)
Our data is labeled.
************************************
Labeled Data Supervised learning Math
************************************

(Our data set of labeled examples) = S
S = {(X.1, Y,1),...,(X.n,Y.n)} ⊆ X x Y
h : X --> Y
err(h) = 𝔼.(χ ~ D)⟦h(x) - f(x)⟧

A⊆B , subset,  A is a subset of B. set A is included in set B.
Cartesian product: for sets A and B, the Cartesian product A × B 
is the set of all ordered pairs (a, b) where a ∈ A and b ∈ B. 
     1     2     3
X (X,1) (X,2) (X,3)
Y (Y,1) (Y,2) (Y,3)
Z (Z,1) (Z,2) (Z,3)

h = A prediction rule/hypothesis

How I inerpreate this in laymans.

Our set which goes up to a fixed number of pairs n
Is a subset of all the pairs in the Cartesian product of X and Y
Our prediction rule attempts to predict, given a new x value,
What's it's associated Y value

We have to learn this mapping !!!

to do this we use err(h), which is our error function
that acts as a performance metric

So we choos from prossible models to represent this function
i.e 
Regression
    Linear Regresion
Classification
    Naive Bayes
    Preceptron
    Decisions Trees
    Logistic Regression
clustering
    K-Means 
    KD Trees
    agglomerative/Hierarchical

Algorithm: Learn Something
Input: Data, Mental Model
Output: Updated Mental Model

While Mental Model Makes Bad Preditions  DO
    make a guess at answer
    measure error
    if (error is acceptably small)
        break
    else
        propose model adjustment
        Mental Model = (Mental Model + Adjustment)
'''
