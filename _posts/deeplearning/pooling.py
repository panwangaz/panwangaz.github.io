import numpy as np
import torch.nn as nn


class Maxpooling(nn.Module):

    def __init__(self, kernel, pad=0, stride=1):
        super(Maxpooling, self).__init__()
        assert isinstance(kernel, [tuple, list])
        self.kernel = kernel
        self.kx, self.ky = kernel[0], kernel[1]
        self.pad = pad
        self.stride = stride

    def forward(self, input):
        inputW, inputH = input.shpae
        self.input = input
        self.inputW = inputW
        self.inputH = inputH
        outputW = (inputW - self.kx + self.pad) / self.stride + 1
        outputH = (inputH - self.ky + self.pad) / self.stride + 1
        self.outputW, self.outputH = outputW, outputH
        output = np.zeros((outputH, outputW))
        self.arg_max = np.zeros_like(output)

        for row in range(inputH):
            for col in range(inputW):
                row_start = row * self.stride
                col_start = col * self.stride
                row_end = row_start + self.kx
                col_end = col_start + self.ky
                output[row, col] = np.max(input[row_start:row_end,
                                                col_start:col_end])
                self.arg_max[row, col] = np.argmax(
                    input[row_start:row_end][col_start:col_end])
        return output

    def backward(self, d_loss):
        dx = np.zeros_like(self.input)
        for i in range(self.outputH):
            for j in range(self.outputW):
                si = i * self.stride
                sj = j * self.stride
                ei = si + self.kx
                ej = sj + self.ky
                index = np.unravel_index(self.arg_max[i, j], self.kernel)
                dx[si:ei, sj:ej][index] = d_loss[i, j]
        return dx


class AveragePooling(nn.Module):

    def __init__(self, kernel, stride=1, pad=0):
        super(AveragePooling, self).__init__()
        assert isinstance(kernel, [tuple, list])
        self.kernel = kernel
        self.kx, self.ky = kernel[0], kernel[1]
        self.stride = stride
        self.pad = pad

    def forward(self, input):
        self.input = input
        self.inputH, self.inputW = input.shape
        self.outputH = (self.inputH - self.kx + self.pad) / self.stride + 1
        self.outputW = (self.inputW - self.ky + self.pad) / self.stride + 1
        output = np.zeros((self.outputH, self.outputW))
        for i in range(self.outputH):
            for j in range(self.outputW):
                istart = i * self.stride
                iend = istart + self.kx
                jstart = j * self.stride
                jend = jstart + self.ky
                output[i, j] = np.mean(input[istart:iend, jstart:jend])
        return output

    def backward(self, d_loss):
        dx = np.zeros_like(self.input)
        for i in range(self.outputH):
            for j in range(self.outputW):
                istart = i * self.stride
                iend = istart + self.kx
                jstart = j * self.stride
                jend = istart + self.ky
                dx[istart:iend,
                   jstart:jend] = d_loss[i, j] / (self.kx * self.ky)
        return dx
