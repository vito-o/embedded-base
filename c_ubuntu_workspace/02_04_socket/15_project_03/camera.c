#include "camera.h"
#include "global.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <error.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <jpeglib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

static struct camera_t *camera_data;
static int n_buffer;


int init_camera(const char *dev_path)
{
    // 打开设备
    int fd = open(dev_path, O_RDWR|O_NONBLOCK);
    if (0 > fd)
    {
        perror("open dev failure!");
        return -1;
    }

    // 查询相机能力
    struct v4l2_capability cap; // 存储设备信息的结构体

    // 通过这行代码，程序可以获取摄像头的基本信息和支持的功能，以便后续的设置和操作。若查询失败，程序可以根据错误信息决定后续的处理措施。
    // ioctl: 这是一个系统调用，用于设备控制。它允许程序对设备驱动进行操作，传递命令和数据。
    // VIDIOC_QUERYCAP：这是一个命令，用于查询设备的能力。它通常被用来检查设备是否支持某些功能，例如视频捕捉、回放等。
    // &cap：这是一个指向 v4l2_capability 结构体的指针，用于存储查询到的设备信息。该结构体中包含了设备的各种能力信息，
    // 如：
    // `设备的驱动名称
    // `设备的硬件名称
    // `支持的功能（如视频捕捉、视频输出等）
    // `支持的最大分辨率和像素格式等
    if (0 > ioctl(fd, VIDIOC_QUERYCAP, &cap))
    {
        perror("VIDIOC_QUERYCAP failure!");
        return -1;
    }
    
    if (!(V4L2_CAP_VIDEO_CAPTURE & cap.capabilities))
    {
        perror("camera can`t CAPTURE!");
        return -1;
    }

    // 存储帧描述信息的结构体
    struct v4l2_fmtdesc fmt;
    fmt.index = 0;
    fmt.type = V4L2_CAP_VIDEO_CAPTURE; //V4L2_CAP_VIDEO_CAPTURE，表示要查询的格式是用于视频捕捉的格式。

    // 通过这行代码，程序可以获取摄像头支持的所有图像格式，帮助用户或程序选择合适的格式进行视频捕捉。如果查询失败，程序可以根据错误信息采取相应措施。
    // VIDIOC_ENUM_FMT：这是一个命令，用于查询摄像头支持的图像格式。
    // &fmt：这是一个指向 v4l2_fmtdesc 结构体的指针，用于存储查询到的格式信息。该结构体包含以下字段：
    // `index：格式的索引，从 0 开始，依次增加。
    // `type：格式类型（如视频捕捉）。
    // `pixelformat：像素格式的标识符（如 YUYV、MJPEG 等）。
    // `description：对该格式的描述。
    while(0 == ioctl(fd, VIDIOC_ENUM_FMT, &fmt))
    {
        printf("pixel format:%c%c%c%c, description:%s\n",
               fmt.pixelformat & 0xFF, (fmt.pixelformat >> 8) & 0xFF,
               (fmt.pixelformat >> 16) & 0xFF, (fmt.pixelformat >> 24) & 0xFF,
               fmt.description);
        ++fmt.index;
    }

    // 设置相机帧格式
    struct v4l2_format format;  // 帧格式相关参数
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;      // 指定该格式是用于视频捕捉的类型
    format.fmt.pix.width = IMG_WIDTH;               // 设置捕捉图像的宽度。
    format.fmt.pix.height = IMG_HEIGHT;             // 设置捕捉图像的高度。
    // V4L2_PIX_FMT_YUYV 是一种常见的图像格式（YUYV），用于表示颜色信息。这种格式的优点是能够在相同的数据带宽下提供较高的图像质量。
    format.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV; // 设置图像的像素格式。
    // V4L2_FIELD_INTERLACED 表示使用交错扫描（interlaced）格式。这种格式通常用于电视信号，图像由两个字段交替显示，以减少运动模糊。
    format.fmt.pix.field = V4L2_FIELD_INTERLACED;   // 设置图像的字段类型。

    // 通过这行代码，程序将定义的图像格式应用到摄像头上，使其开始按照指定的格式捕捉图像。如果设置成功，后续的图像捕捉操作将使用这个格式。如果失败，通常会返回错误，程序可以根据错误信息进行相应处理。
    // VIDIOC_S_FMT：这是一个命令，用于设置设备的图像格式。它告诉驱动程序应用指定的格式。
    ioctl(fd, VIDIOC_S_FMT, &format);

    return fd;
}

int init_mmap(int fd)
{
    // ----向驱动申请内存缓冲区(内核空间)
    // 请求相机驱动分配视频捕捉的内存缓冲区，以便在捕捉视频时存储图像帧
    struct v4l2_requestbuffers reqbuf;
    // 设置请求的缓冲区数量为 4。
    // 这意味着希望驱动分配 4 个缓冲区用于视频捕捉。
    reqbuf.count = 4;
    // 指定请求的缓冲区类型为视频捕捉。
    // 这告诉驱动程序申请的缓冲区是用于存储视频帧的。
    reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    // 指定请求的缓冲区的内存类型为内存映射（mmap）。
    // 这表示将使用内存映射的方式将缓冲区映射到用户空间，以便程序可以直接访问。
    reqbuf.memory = V4L2_MEMORY_MMAP;
    // VIDIOC_REQBUFS 命令用于请求驱动程序分配缓冲区
    if (0 > ioctl(fd, VIDIOC_REQBUFS, &reqbuf))
    {
        perror("VIDIOC_REQBUFS failure!");
        return -1;
    }

    // 动态分配一块内存，用于存储多个摄像头缓冲区的信息
    // calloc：这是一个标准库函数，用于动态分配内存。与 malloc 不同，calloc 会初始化分配的内存为零。
    // reqbuf.count：这是之前请求的缓冲区数量，表示希望为多少个缓冲区分配内存。
    // sizeof(struct camera_t)：这是每个缓冲区信息结构体的大小，确保分配足够的内存来存储每个 camera_t 实例。
    camera_data = calloc(reqbuf.count, sizeof(struct camera_t));

    // ----将内核缓冲区映射到用户空间(先查询后映射)
    for(int i = 0; i < reqbuf.count; i++)
    {
        struct v4l2_buffer buf;
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;
        //查询申请到缓冲区的信息.
        if (0 > ioctl(fd, VIDIOC_QUERYBUF, &buf))
        {
            perror("VIDIOC_QUERYBUF failure!");
            return -1;
        }

        camera_data[i].length = buf.length;
        camera_data[i].start = mmap(NULL, buf.length,
                                    PROT_READ | PROT_WRITE,
                                    MAP_SHARED, fd, buf.m.offset);
    }

    // ----将申请的内核缓冲区放入输入队列中
    for (int i = 0; i < reqbuf.count; i++)
    {
        struct v4l2_buffer buf;
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = i;

        if (0 > ioctl(fd, VIDIOC_QBUF, &buf))
        {
            perror("VIDIOC_QBUF failure! 1");
            return -1;
        }
    }

    n_buffer = reqbuf.count;
    return 0;
}

int start_camera(int fd)
{
    // 这两行代码的作用是启动视频捕捉流，以便摄像头开始捕捉视频帧
    // 允许摄像头开始捕捉图像并将其存储在之前排入队列的缓冲区中。成功启动后，可以通过 VIDIOC_DQBUF 来读取捕捉到的帧。如果失败，则需要处理错误情况。
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    // 通过 ioctl 调用发送 VIDIOC_STREAMON 命令，开始视频流。
    // 这个命令告诉驱动程序开始将捕捉到的视频帧放入已排入队列的缓冲区中。
    if (0 > ioctl(fd, VIDIOC_STREAMON, &type))
    {
        perror("VIDIOC_STREAMON failure!");
        return -1;
    }
    return 0;
}

void *start_capturing(void *arg)
{
    // 开始采集数据.
    int fd = (int)arg;
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (0 > ioctl(fd, VIDIOC_STREAMON, &type)){
        perror("VIDIOC_STREAMON failure!");
        return NULL;
    }

    fd_set fds;
    struct timeval tv = {
        .tv_sec = 5,
        .tv_usec = 0,
    };
	while(global.capture) {
        FD_ZERO(&fds);
        FD_SET(fd, &fds);

        int r = select(fd + 1, &fds, NULL, NULL, &tv);
        if (-1 == r){
            if (EINTR == errno)
                continue;

            perror("Fail to select");
            break;
        }

        if (0 == r){
            //printf(stderr, "select Timeout\n");
            continue;
        }

        if (0 != read_frame(fd)){
            printf("read_frame() error\n");
            continue;
        }
    }

    pthread_exit(NULL);
}


int read_camera(int fd)
{
    struct v4l2_buffer buf;
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    // 将申请到的缓冲区放入视频设备的输入队列中，以便驱动可以使用这些缓冲区来存储捕捉到的视频帧。
    // VIDIOC_QBUF：这是一个命令，用于将一个缓冲区排入视频设备的输入队列。设备将使用这些缓冲区来存储捕捉到的视频帧。
    if(0 > ioctl(fd, VIDIOC_DQBUF, &buf))
    {
        perror("VIDIOC_QBUF failure! 2");
        return -1;
    }

    int frame_len = camera_data[buf.index].length;
    void *frame_ptr = camera_data[buf.index].start;

    FILE *yuv_fp = fopen("./picture.yuv", "w");
    if (NULL != yuv_fp)
    {
        fwrite(frame_ptr, frame_len, 1, yuv_fp);
        fflush(yuv_fp);
        fclose(yuv_fp);
    }

    yuyv_to_rgb(frame_ptr, "picture.rgb", IMG_WIDTH, IMG_HEIGHT);
    //yuyv_to_jpeg(frame_ptr, "picture.jpg", IMG_WIDTH, IMG_HEIGHT);
    yuyv_to_jpeg(frame_ptr, "picture.jpeg", IMG_WIDTH, IMG_HEIGHT, 90);

    return 0;
}

int read_frame(int fd)
{
    struct v4l2_buffer buf;
    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;
    if (0 > ioctl(fd, VIDIOC_DQBUF, &buf)){
        perror("VIDIOC_DQBUF failure!");
        return -1;
    }

    //assert(buf.index < n_buffer);

    pthread_mutex_lock(&global.update_lock);

    // 读取到全局的buffer中去.
    global.length = camera_data[buf.index].length;

    // 采集的数据大于预定义的大小, 扩充内存.
    if (global.length > PICTURE_SIZE){
        global.start = realloc(global.start, global.length);
        memcpy(global.start, camera_data[buf.index].start, global.length);
    }
    else {
        memcpy(global.start, camera_data[buf.index].start, global.length);
    }

    // printf("pthread_cond_broadcast\n");
    pthread_mutex_unlock(&global.update_lock);

    // 唤醒等待的线程.
    pthread_cond_broadcast(&global.update_cond);

    if (-1 == ioctl(fd, VIDIOC_QBUF, &buf)){
        perror("Fail to ioctl 'VIDIOC_QBUF'");
        return -1;
    }

    //printf("read_frame() success!\n");
    return 0;
}

int yuyv_to_rgb(const unsigned char *yuv, char *file_name, int width, int height) // 640*480
{
    if (NULL == yuv || NULL == file_name){
        return -1;
    }
    if(0 == width || 0 == height) {
        return -1;
    }

    FILE *fp = fopen(file_name, "w");
    char *lineBuf = malloc(width * 3);
    int y, u, v;
    int r, g, b;
    for (int row = 0; row < height; ++row)
    {
        char *ptr = lineBuf;
        for (int col = 0; col < width; col += 2)
        {
            y = yuv[0];
            u = yuv[1];
            v = yuv[3];
            r = y + 1.402 * (v - 128);
            g = y - 0.344 * (u - 128) - 0.714 * (v - 128);
            b = y + 1.772 * (u - 128);
            ptr[0] = r > 255 ? 255 : (r < 0 ? 0 : r);
            ptr[1] = g > 255 ? 255 : (g < 0 ? 0 : g);
            ptr[2] = b > 255 ? 255 : (b < 0 ? 0 : b);

            y = yuv[2];
            u = yuv[1];
            v = yuv[3];
            r = y + 1.402 * (v - 128);
            g = y - 0.344 * (u - 128) - 0.714 * (v - 128);
            b = y + 1.772 * (u - 128);
            ptr[3] = r > 255 ? 255 : (r < 0 ? 0 : r);
            ptr[4] = g > 255 ? 255 : (g < 0 ? 0 : g);
            ptr[5] = b > 255 ? 255 : (b < 0 ? 0 : b);

            ptr += 6;
            yuv += 4;
        }
        fwrite(lineBuf, width * 3, 1, fp);
        fflush(fp);
    }
    return 0;
}

/*
 * @img: yuyv422格式图像原始数据
 * @fp: yuyv压缩为jpeg格式后的数据存放文件的文件描述符
 * @width: 图像宽度
 * @height: 图像高度
 * @quality: 压缩质量(1-100)
 */
int yuyv_to_jpeg(const unsigned char *yuv, char *file_name, int width, int height, int quality)
{
    FILE *fp = fopen(file_name, "w");
    struct jpeg_compress_struct cinfo; // 定义一个压缩对象.
    struct jpeg_error_mgr jerr;        // 用于存放错误信息.
    JSAMPROW row_pointer[1];           // 一行位图.

    cinfo.err = jpeg_std_error(&jerr); // 错误信息输出绑定到压缩对象.
    jpeg_create_compress(&cinfo);      // 初始化压缩对象.
    jpeg_stdio_dest(&cinfo, fp);       // 将保存输出数据的文件的文件描述符与压缩对象绑定.
    cinfo.image_width = width;
    cinfo.image_height = height;             // 图像的宽和高，单位为像素.
    cinfo.input_components = 3;              // 3表示彩色位图，如果是灰度图则为1.
    cinfo.in_color_space = JCS_RGB;          // JSC_RGB表示彩色图像.
    jpeg_set_defaults(&cinfo);               // 采用默认设置对图像进行压缩.
    jpeg_set_quality(&cinfo, quality, TRUE); // 设置图像压缩质量.
    jpeg_start_compress(&cinfo, TRUE);       // 开始压缩.

    // 申请buf空间，大小为yuyv数据转换为rgb格式后每一行的字节数.
    unsigned char *line_buf = calloc(width*3, 1); // 开辟行缓冲内存
    int r, g, b;
    int y, u, v; // 对每行yuv数据进行rgb转换
    while (cinfo.next_scanline < height)
    { // 逐行进行图像压缩
        unsigned char *ptr = line_buf;
		//对每行yuv数据进行rgb转换
        for (int col = 0; col < width; col += 2)
        {
            y = yuv[0];
            u = yuv[1];
            v = yuv[3];
            r = y + 1.402 * (v - 128);
            g = y - 0.344 * (u - 128) - 0.714 * (v - 128);
            b = y + 1.772 * (u - 128);
            ptr[0] = r > 255 ? 255 : (r < 0 ? 0 : r); //0x101
            ptr[1] = g > 255 ? 255 : (g < 0 ? 0 : g);
            ptr[2] = b > 255 ? 255 : (b < 0 ? 0 : b);

            y = yuv[2];
            u = yuv[1];
            v = yuv[3];
            r = y + 1.402 * (v - 128);
            g = y - 0.344 * (u - 128) - 0.714 * (v - 128);
            b = y + 1.772 * (u - 128);
            ptr[3] = r > 255 ? 255 : (r < 0 ? 0 : r);
            ptr[4] = g > 255 ? 255 : (g < 0 ? 0 : g);
            ptr[5] = b > 255 ? 255 : (b < 0 ? 0 : b);

            ptr += 6;
            yuv += 4;
        }
        row_pointer[0] = line_buf;
        jpeg_write_scanlines(&cinfo, row_pointer, 1); // 将行数据写入压缩对象
    }
    jpeg_finish_compress(&cinfo);  // 压缩完成
    jpeg_destroy_compress(&cinfo); // 释放申请的资源
    free(line_buf);
    return 0;
}