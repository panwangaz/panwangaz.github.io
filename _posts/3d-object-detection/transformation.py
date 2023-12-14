import numpy as np
import torch

a = torch.tensor([[2, 3, 4], [5, 4, 2]])
b = torch.tensor([[2, 3], [7, 8], [2, 3]])
c = torch.tensor([2, 3, 9])
d = b.t()
print(d)
print(a @ b)
print(torch.mm(a, b))
print(torch.matmul(a, b))
print(np.dot(a, b))
print(a * c)
print(torch.mul(a, c))
