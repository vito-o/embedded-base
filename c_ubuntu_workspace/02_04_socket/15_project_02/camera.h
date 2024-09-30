#ifndef __CAMERA_H__
#define __CAMERA_H__

#define IMG_WIDTH 640
#define IMG_HEIGHT 480

struct camera_t
{
    void *start;
    int length;
};

extern int init_camera(const char *dev_path);

extern int init_mmap(int fd);

extern int start_camera(int fd);

extern int read_camera(int fd);

extern int yuyv_to_rgb(const unsigned char *yuv, char *file_name, int width, int height);
extern int yuyv_to_jpeg(const unsigned char *yuv, char *file_name, int width, int height, int quality);

#endif