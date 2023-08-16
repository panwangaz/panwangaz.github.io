import torch
import torch.nn as nn
import numpy as np
import torch.nn.functional as F


class MultiHeadAttention(nn.Module):
    '''
    input:
        query --- [N, T_q, query_dim]
        key --- [N, T_k, key_dim]
        mask --- [N, T_k]
        T_q 相当于是图像中的 H*W
    output:
        out --- [N, T_q, embed_dim]
        scores -- [h, N, T_q, T_k]
    '''

    def __init__(self, query_dim, key_dim, embed_dim, num_heads):

        super().__init__()
        self.embed_dim = embed_dim
        self.num_heads = num_heads
        self.key_dim = key_dim

        self.W_query = nn.Linear(query_dim, embed_dim, bias=False)
        self.W_key = nn.Linear(key_dim, embed_dim, bias=False)
        self.W_value = nn.Linear(key_dim, embed_dim, bias=False)

    def forward(self, query, key, mask=None):
        querys = self.W_query(query)  # [N, T_q, embed_dim]
        keys = self.W_key(key)  # [N, T_k, embed_dim]
        values = self.W_value(key)

        assert self.embed_dim % self.num_heads == 0
        split_size = self.embed_dim // self.num_heads
        querys = torch.stack(torch.split(querys, split_size, dim=2), dim=0)  # [h, N, T_q, embed_dim/h]
        keys = torch.stack(torch.split(keys, split_size, dim=2), dim=0)  # [h, N, T_k, embed_dim/h]
        values = torch.stack(torch.split(values, split_size, dim=2), dim=0)  # [h, N, T_k, embed_dim/h]

        ## score = softmax(QK^T / (d_k ** 0.5))
        scores = torch.matmul(querys, keys.transpose(2, 3))  # [h, N, T_q, T_k]
        scores = scores / (self.key_dim ** 0.5)

        ## mask
        if mask is not None:
            ## mask:  [N, T_k] --> [h, N, T_q, T_k]
            mask = mask.unsqueeze(1).unsqueeze(0).repeat(self.num_heads,1,querys.shape[2],1)
            # 将 mask 中为 1 的元素所在的索引在 score 中替换成 -np.inf，经过 softmax 之后这部分的值会变成 0
            # 相当于这部分就不进行 attention 的计算 （ np.exp(-np.inf) = 0 ）
            scores = scores.masked_fill(mask, -np.inf)
        scores = F.softmax(scores, dim=3)

        ## out = score * V
        out = torch.matmul(scores, values)  # [h, N, T_q, embed_dim/h]
        out = torch.cat(torch.split(out, 1, dim=0), dim=3).squeeze(0)  # [N, T_q, embed_dim]

        return out, scores

attention = MultiHeadAttention(256,512,256,16)

## 输入
qurry = torch.randn(8, 2, 256)
key = torch.randn(8, 6 ,512)
mask = torch.tensor([[False, False, False, False, True, True],
                     [False, False, False, True, True, True],
                     [False, False, False, False, True, True],
                     [False, False, False, True, True, True],
                     [False, False, False, False, True, True],
                     [False, False, False, True, True, True],
                     [False, False, False, False, True, True],
                     [False, False, False, True, True, True],])

## 输出
out, scores = attention(qurry, key, mask)
print('out:', out.shape)         ## torch.Size([8, 2, 256])
print('scores:', scores.shape)   ## torch.Size([16, 8, 2, 6])