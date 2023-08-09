import torch
import torch.nn as nn

class MultiHeadAttention(nn.Module):
    def __init__(self, input_dim, num_heads):
        super(MultiHeadAttention, self).__init__()
        self.input_dim = input_dim
        self.num_heads = num_heads
        self.head_dim = input_dim // num_heads
        
        # 线性变换
        self.query_linear = nn.Linear(input_dim, input_dim)
        self.key_linear = nn.Linear(input_dim, input_dim)
        self.value_linear = nn.Linear(input_dim, input_dim)
        
        # 输出线性变换
        self.output_linear = nn.Linear(input_dim, input_dim)
        
    def forward(self, inputs):
        batch_size, seq_len, input_dim = inputs.size()
        
        # 线性变换得到查询、键和值
        queries = self.query_linear(inputs)
        keys = self.key_linear(inputs)
        values = self.value_linear(inputs)
        
        # 将查询、键和值分割成多个头
        queries = queries.view(batch_size, seq_len, self.num_heads, self.head_dim).permute(0, 2, 1, 3)
        keys = keys.view(batch_size, seq_len, self.num_heads, self.head_dim).permute(0, 2, 1, 3)
        values = values.view(batch_size, seq_len, self.num_heads, self.head_dim).permute(0, 2, 1, 3)
        
        # 计算注意力分数
        attention_scores = torch.matmul(queries, keys.permute(0, 1, 3, 2))
        attention_scores = attention_scores / (self.head_dim ** 0.5)
        attention_probs = nn.Softmax(dim=-1)(attention_scores)
        
        # 加权求和得到注意力向量
        attention_vectors = torch.matmul(attention_probs, values)
        attention_vectors = attention_vectors.permute(0, 2, 1, 3).contiguous().view(batch_size, seq_len, input_dim)
        
        # 输出线性变换
        outputs = self.output_linear(attention_vectors)
        
        return outputs