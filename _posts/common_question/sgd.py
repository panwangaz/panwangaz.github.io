def solver(func, x0, loss=lambda x: x**2, lr=1e-2, eps=1e-3, iternum=1000):
    val = x0
    curNum = 0
    momentumbuf = None
    while (curNum < iternum):
        forward = func(val)
        dloss_dy = dfunc(loss, forward)
        dy_dx = dfunc(func, val)
        curNum += 1
        grad = dloss_dy * dy_dx
        momentumbuf = momentumbuf * 0.9 + 0.1 * grad if momentumbuf else grad
        val = val - lr * momentumbuf
        print(f'the iter: {iternum}, val: {val}, grad: {momentumbuf}')


def dfunc(func, x, deltax=1e-3):
    dx = x + deltax
    return (func(dx) - func(x)) / deltax


func = lambda x: x**2 - 2.45  # noqa
res = solver(func, 0)
