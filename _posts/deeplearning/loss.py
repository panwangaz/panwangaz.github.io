# 主要是记住公式，尤其是 FocalLoss 的公式，前面是 (1-p)，p 是经过 softmax 之后的概率，其实跟 CE 是一样的，
# 如果 p 特别大的话 loss 就几乎是 0，然后用 gamma 进行指数运算，loss 就更小了，
# 就是通过这样的机制来调整不同样本产生的 loss

# torch 版本

import torch
import torch.nn.functional as F
# => official
pred = torch.randn(5,5)
target = torch.tensor([0,3,1,2,4], dtype=torch.long)
official_ce_loss = F.cross_entropy(pred, target)

# => my
# softmax_logits = F.softmax(pred, dim=1) # 或者直接用这一句
softmax_logits = torch.exp(pred) / torch.sum(torch.exp(pred), dim=1) 
onehot_target = F.one_hot(target)
my_ce_loss = -1 * torch.sum(onehot_target * torch.log(softmax_logits)) / pred.shape[0]

print(my_ce_loss)
print(official_ce_loss)

#focal
gamma = 2
alpha = 0.25

# => official
ce_loss = F.cross_entropy(pred, target, 
                          reduction='none')
pt = torch.exp(-ce_loss)
official_focal_loss = (alpha * (1-pt) ** gamma * ce_loss).mean()

# => my
pt = F.softmax(pred, dim=1)
neg_ylogp = -1 * onehot_target * torch.log(pt)
focal = alpha * (1-pt) ** gamma * neg_ylogp
my_focal_loss = torch.sum(focal) / pred.shape[0]

print(my_focal_loss)
print(official_focal_loss)



def l2_loss(prediction, target):
    loss = torch.mean((prediction - target)**2)
    return loss

def l1_loss(prediction, target):
    loss = torch.mean(torch.abs(prediction - target))
    return loss

def smooth_l1_loss(prediction, target, beta=1.0):
    diff = torch.abs(prediction - target)
    loss = torch.where(diff < beta, 0.5 * diff**2, beta * (diff - 0.5 * beta))
    loss = torch.mean(loss)
    return loss


# 示例输入和目标
prediction = torch.tensor([1.5, 2.5, 3.5])
target = torch.tensor([1.0, 2.0, 4.0])

# 计算L1 Loss
loss = l1_loss(prediction, target)

# 打印损失
print(loss)

softmax_logits = torch.exp(pres) / torch.sum(torch.exp(pres), dim=1)
onehot_taget = F.one_hot(target)
loss = -1 * torch.sum(torch.log(softmax_logits) * onehot_taget) / pres.shape[0]