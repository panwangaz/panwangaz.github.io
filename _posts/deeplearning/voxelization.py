import numpy as np


def points_to_voxel(points,
                    voxel_size,
                    coors_range,
                    max_points=35,
                    max_voxels=20000):
    """
    Args:
        points: [N, ndim] float tensor. points[:, :3] contain xyz points and
            points[:, 3:] contain other information such as reflectivity.
        voxel_size: [3] array, float. xyz, indicate voxel size
        coors_range: [6] array, float. indicate voxel range. format: xyzxyz, minmax
        max_points: int. indicate maximum points contained in a voxel.
        max_voxels: int. indicate maximum voxels this function create.
    Returns:
        voxels: [M, max_points, ndim] float tensor. only contain points.
        coordinates: [M, 3] int32 tensor.
        num_per_voxel: [M] int32 tensor.
    """
    voxel_shape = (coors_range[3:] - coors_range[:3]) / voxel_size
    grid_size = np.round(voxel_shape, 0).astype(np.int32)

    coor_to_voxelidx = -np.ones(grid_size.tolist(), dtype=np.int32)
    num_per_voxel = np.zeros((max_voxels, ), dtype=np.int32)
    voxels = np.zeros((max_voxels, max_points, 3), dtype=points.dtype)
    coors = np.zeros((max_voxels, 3), dtype=np.int32)

    coor, voxel_num = np.zeros((3, ), dtype=np.int32), 0
    for i in range(points.shape[0]):
        failed = False
        # calcurate coordinate
        for j in range(3):
            c = np.floor((points[i, j] - coors_range[j]) / voxel_size[j]) # 计算在哪个voxel
            if c < 0 or c >= grid_size[j]: # 剔除掉外面的点
                failed = True
                break
            coor[j] = c
        if failed:
            continue
        # update voxel index
        voxelidx = coor_to_voxelidx[coor[0], coor[1], coor[2]]
        if voxelidx == -1:
            voxelidx = voxel_num
            if voxel_num >= max_voxels:
                continue
            voxel_num += 1
            coor_to_voxelidx[coor[0], coor[1], coor[2]] = voxelidx
            coors[voxelidx] = coor
        # update reults
        num = num_per_voxel[voxelidx]
        if num < max_points:
            voxels[voxelidx, num] = points[i]
            num_per_voxel[voxelidx] += 1
    return voxels[:voxel_num], coors[:voxel_num], num_per_voxel[:voxel_num]


points = np.random.rand(10000, 3)
voxel_size = np.array([0.01, 0.01, 0.01])
coors_range = np.array([0.01, 0.01, 0.01, 0.99, 0.99, 0.99])
outs = points_to_voxel(points, voxel_size, coors_range)
