import torch
import torch.nn as nn
import torch.nn.functional as F


class ASFF(nn.Module):

    def __init__(self, in_channels, out_channels, reduction=8):
        super(ASFF, self).__init__()
        self.attention = nn.Sequential(
            nn.AdaptiveAvgPool2d(1),
            nn.Conv2d(out_channels, out_channels // reduction, 1, bias=False),
            nn.BatchNorm2d(out_channels // reduction),
            nn.ReLU(inplace=True),
            nn.Conv2d(out_channels // reduction, out_channels, 1, bias=False),
            nn.Sigmoid(),
        )
        self.project = nn.Sequential(
            nn.Conv2d(in_channels, out_channels, 1, bias=False),
            nn.BatchNorm2d(out_channels),
            nn.ReLU(),
        )

    def forward(self, inputs):
        size = inputs[0].size()[2:]
        feats = []
        for feat in inputs:
            feats.append(
                F.interpolate(feat, size, mode='bilinear',
                              align_corners=False))
        feats = torch.cat(feats, dim=1)

        att = self.attention(feats)
        feats = feats * att
        return self.project(feats)
