import torch
import torch.nn as nn
import torch.nn.functional as F


class ASPPConv(nn.Sequential):

    def __init__(self, in_channels, out_channels, dilation):
        modules = [
            nn.Conv2d(in_channels,
                      out_channels,
                      3,
                      padding=dilation,
                      dilation=dilation,
                      bias=False),
            nn.BatchNorm2d(out_channels),
            nn.ReLU(inplace=True),
        ]
        super(ASPPConv, self).__init__(*modules)


class ASPPPooling(nn.Sequential):

    def __init__(self, in_channels, out_channels):
        modules = [
            nn.AdaptiveAvgPool2d((1, 1)),
            nn.Conv2d(in_channels, out_channels, 1, bias=False),
            nn.BatchNorm2d(out_channels),
            nn.ReLU(inplace=True),
        ]
        super(ASPPPooling, self).__init__(*modules)

    def forward(self, x):
        size = x.shape[-2:]
        x = super(ASPPPooling, self).forward(x)
        return F.interpolate(x,
                             size=size,
                             mode='bilinear',
                             align_corners=False)


class ASPP(nn.Module):

    def __init__(self, in_channels, out_channels, atrous_rates):
        super(ASPP, self).__init__()
        modules = []
        modules.append(
            nn.Sequential(
                nn.Conv2d(in_channels, out_channels, 1, bias=False),
                nn.BatchNorm2d(out_channels),
                nn.ReLU(inplace=True),
            ))

        for rate in atrous_rates:
            modules.append(ASPPConv(in_channels, out_channels, rate))

        modules.append(ASPPPooling(in_channels, out_channels))

        self.convs = nn.ModuleList(modules)

        self.project = nn.Sequential(
            nn.Conv2d(out_channels * (len(atrous_rates) + 2),
                      out_channels,
                      1,
                      bias=False),
            nn.BatchNorm2d(out_channels),
            nn.ReLU(inplace=True),
        )

    def forward(self, x):
        res = []
        for conv in self.convs:
            res.append(conv(x))
        res = torch.cat(res, dim=1)
        return self.project(res)


x = torch.randn((2, 256, 100, 80))
model = ASPP(256, 512, [4, 6, 8])
out = model(x)
