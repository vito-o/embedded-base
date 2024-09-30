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

#endif