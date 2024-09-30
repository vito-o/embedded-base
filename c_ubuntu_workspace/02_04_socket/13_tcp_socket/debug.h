#ifndef __DEBUG_H__
#define __DEBUG_H__

/*
    __FILE__: 输出文件名
    __FUNCTION__: 输出函数名
    __LINE__: 输出行号
*/

#define DEBUG_INFO(args...) do{ \
	char b__[1024];\
	sprintf(b__,args);\
	fprintf(stderr,"[%s,%s,%d] : %s",__FILE__,__FUNCTION__,__LINE__,b__); \
}while(0)

#endif