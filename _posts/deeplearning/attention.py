import torch
import torch.nn as nn
import torch.nn.functional as F

class MultiHeadAttention(nn.Module):
    def __init__(self, query_dim, key_dim, embed_dim, num_heads):
        super(MultiHeadAttention, self).__init__()
        self.query_dim = query_dim
        self.key_dim = key_dim
        self.embed_dim = embed_dim
        self.num_heads = num_heads
        self.query_proj = nn.Linear(query_dim, embed_dim, bias=False)
        self.key_proj = nn.Linear(key_dim, embed_dim, bias=False)
        self.value_proj = nn.Linear(key_dim, embed_dim, bias=False)

    def forward(self, query, key, mask=None):
        querys = self.query_proj(query)
        keys = self.key_proj(key)
        values = self.value_proj(key)

        assert self.embed_dim % self.num_heads == 0
        split_size = self.embed_dim // self.num_heads
        querys = torch.stack(querys.split(split_size, dim=2), dim=0)
        keys = torch.stack(keys.split(split_size, dim=2), dim=0)
        values = torch.stack(values.split(split_size, dim=2), dim=0)

        weights = torch.matmul(querys, keys.transpose(2, 3))
        weights = weights / (self.key_dim ** 0.5)

        if mask is not None:
            mask = mask.unsqueeze(1).unsqueeze(0).repeat(self.num_heads, 1, querys.shape[2], 1)
            weights = weights.masked_fill(mask, -torch.inf)
        weights = F.softmax(weights, dim=3)

        out = torch.matmul(weights, values)
        out = torch.cat(out.split(1, dim=0), dim=3).squeeze(0)

        return out, weights
    
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
