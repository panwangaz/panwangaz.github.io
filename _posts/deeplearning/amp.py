import torch
from torch import nn, optim
from torch.cuda.amp import autocast, GradScaler

# 创建模型
model = YourModel()

# 定义损失函数和优化器
criterion = nn.CrossEntropyLoss()
optimizer = optim.SGD(model.parameters(), lr=0.01)

# 定义混合精度训练的缩放器
scaler = GradScaler()

# 将模型和数据移动到GPU上（如果可用）
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
model.to(device)

# 训练循环
for epoch in range(num_epochs):
    for inputs, labels in train_dataloader:
        inputs = inputs.to(device)
        labels = labels.to(device)

        # 混合精度训练的上下文管理器
        with autocast():
            # 前向传播
            outputs = model(inputs)
            loss = criterion(outputs, labels)

        # 反向传播和优化器步骤
        optimizer.zero_grad()
        scaler.scale(loss).backward()
        scaler.step(optimizer)
        scaler.update()

        # 打印损失
        print(f"Epoch [{epoch+1}/{num_epochs}], Batch Loss: {loss.item()}")

# 在评估模型时，要记得取消混合精度训练的上下文管理器
model.eval()
with torch.no_grad():
    for inputs, labels in test_dataloader:
        inputs = inputs.to(device)
        labels = labels.to(device)
        outputs = model(inputs)
        # 继续执行评估过程...