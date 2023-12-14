import numpy as np


def project_point_cloud_to_image(point_cloud, extrinsic, intrinsic):
    # 首先，我们将外参矩阵分解为旋转矩阵和平移向量
    rotation = extrinsic[:3, :3]
    translation = extrinsic[:3, 3]

    # 然后，我们将旋转和平移应用到点云上, np.dot , np.matmul, @ 应该都可以。
    rotated_point_cloud = np.dot(point_cloud, rotation.T)
    translated_point_cloud = rotated_point_cloud + translation

    # 我们只保留Z>0的点，也就是在相机前方的点
    camera_coordinates_front = np.where(translated_point_cloud[:, 2:3] > 0,
                                        translated_point_cloud, 0)

    # 然后，我们将点云的z轴归一化到1
    normalized_point_cloud = camera_coordinates_front.copy()
    normalized_point_cloud[:,
                           0] = camera_coordinates_front[:,
                                                         0] / camera_coordinates_front[:,
                                                                                       2]
    normalized_point_cloud[:,
                           1] = camera_coordinates_front[:,
                                                         1] / camera_coordinates_front[:,
                                                                                       2]
    normalized_point_cloud[:, 2] = 1

    # 最后，我们使用内参矩阵将点云从相机坐标系投影到图像平面
    image_points = np.dot(intrinsic, normalized_point_cloud.T).T

    return image_points


def project_pts_on_img(points,
                       raw_img,
                       lidar2img_rt):
    """Project the 3D points cloud on 2D image.

    Args:
        points (numpy.array): 3D points cloud (x, y, z) to visualize.
        raw_img (numpy.array): The numpy array of image.
        lidar2img_rt (numpy.array, shape=[4, 4]): The projection matrix
            according to the camera intrinsic parameters.
        max_distance (float): the max distance of the points cloud.
            Default: 70.
        thickness (int, optional): The thickness of 2D points. Default: -1.
    """
    img = raw_img.copy()
    num_points = points.shape[0]
    pts_4d = np.concatenate([points[:, :3], np.ones((num_points, 1))], axis=-1)
    pts_2d = pts_4d @ lidar2img_rt.T

    # cam_points is Tensor of Nx4 whose last column is 1
    # transform camera coordinate to image coordinate
    pts_2d[:, 2] = np.clip(pts_2d[:, 2], a_min=1e-5, a_max=99999)
    pts_2d[:, 0] /= pts_2d[:, 2]
    pts_2d[:, 1] /= pts_2d[:, 2]

    fov_inds = ((pts_2d[:, 0] < img.shape[1])
                & (pts_2d[:, 0] >= 0)
                & (pts_2d[:, 1] < img.shape[0])
                & (pts_2d[:, 1] >= 0))

    imgfov_pts_2d = pts_2d[fov_inds, :3]  # u, v, d
    
    return imgfov_pts_2d
