def solver(func, x0, eps=1e-3):
    val = x0
    iternum = 0
    while (abs(func(val)) > eps):
        val = val - func(val) / dfunc(func, val)
        iternum += 1
        print(f'the iter: {iternum}, val: {val}, dx: {dfunc(func, val)}, \
                error: {abs(func(val))}')


def dfunc(func, x, deltax=1e-3):
    dx = x + deltax
    return (func(dx) - func(x)) / deltax


func = lambda x: x**2 - 2  # noqa
res = solver(func, 0)
