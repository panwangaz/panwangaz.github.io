import torch
import torch.nn as nn
import torch.nn.functional as F


class ASFF(nn.Module):

    def __init__(self, in_channels, out_channels, levels, reduction=8):
        super(ASFF, self).__init__()
        reduce_channels = in_channels * levels // reduction
        self.fuse = nn.Sequential(
            nn.AdaptiveAvgPool2d((1, 1)),
            nn.Conv2d(in_channels * levels, reduce_channels, 1),
            nn.BatchNorm2d(reduce_channels),
            nn.ReLU(),
            nn.Conv2d(reduce_channels, in_channels * levels, 1),
            nn.Sigmoid(),
        )
        self.conv = nn.Sequential(
            nn.Conv2d(in_channels * levels, out_channels, 1, 1),
            nn.BatchNorm2d(out_channels),
            nn.ReLU(),
        )

    def forward(self, feats):
        shape = feats[0].shape[-2:]
        outs = []
        for feat in feats:
            outs.append(F.interpolate(feat, shape, mode='bilinear'))
        outs = torch.cat(outs, dim=1)
        outs = outs * self.fuse(outs)
        return self.conv(outs)


feats = [
    torch.randn((2, 256, 100, 80)),
    torch.randn((2, 256, 50, 40)),
    torch.randn((2, 256, 25, 20))
]
model = ASFF(256, 512, 3)
out = model(feats)
