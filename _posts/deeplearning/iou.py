import torch


def boxes_iou_normal(boxes_a, boxes_b):
    """

    Args:
    boxes_a: (N, 4) [x1, y1, x2, y2]
    boxes_b: (M, 4) [x1, y1, x2, y2]

    Returns:

    """

    assert boxes_a.shape[1] == boxes_b.shape[1] == 4
    x_min = torch.max(boxes_a[:, 0, None], boxes_b[None, :, 0])
    x_max = torch.min(boxes_a[:, 2, None], boxes_b[None, :, 2])
    y_min = torch.max(boxes_a[:, 1, None], boxes_b[None, :, 1])
    y_max = torch.min(boxes_a[:, 3, None], boxes_b[None, :, 3])
    x_len = torch.clamp_min(x_max - x_min, min=0)
    y_len = torch.clamp_min(y_max - y_min, min=0)

    area_a = (boxes_a[:, 2] - boxes_a[:, 0]) * (boxes_a[:, 3] - boxes_a[:, 1])
    area_b = (boxes_b[:, 2] - boxes_b[:, 0]) * (boxes_b[:, 3] - boxes_b[:, 1])
    a_intersect_b = x_len * y_len
    iou = a_intersect_b / torch.clamp_min(
        area_a[:, None] + area_b[None, :] - a_intersect_b, min=1e-6)
    return iou


boxa = torch.rand((20, 4))
boxb = torch.rand((10, 4))
iou = boxes_iou_normal(boxa, boxb)
