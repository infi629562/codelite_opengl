#ifndef __COMMON__H__
#define __COMMON__H__
#include <iostream>

#define LOGD(format, ...)    fprintf(stdout, "%-20s <%03d> D: " format "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGE(format, ...)    fprintf(stdout, "%-20s <%03d> E: " format "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGI(format, ...)    fprintf(stdout, "%-20s <%03d> I: " format "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define XDBG(x)  LOGD(#x" = 0x%x", x)
#define DDBG(x)  LOGD(#x" = %d", x)
#define PDBG(x)  LOGD(#x" = %p", x)
#define SDBG(x)  LOGD(#x" = %s", x)

#define HWC_IGNORE(x) ((void)x)

#define HWC_ASSERT(x) do {\
		LOGE(#x "is invalid"); \
		return -ERR_BAD_PARAMETER; \
	}while (0)


#define SCR_WIDTH 800
#define SCR_HEIGHT 600

#define TEXTURE_WALL "/home/infichen/workspace/codelite/gitbase/codelite_opengl/resources/wall.jpg"
#define TEXTURE_DOTA2 "/home/infichen/workspace/codelite/gitbase/codelite_opengl/resources/skin.jpg"
#define TEXTURE_T1 "/home/infichen/Pictures/1080x1920/t2.jpg"
#define TEXTURE_FACE "/home/infichen/Pictures/800x600/awesomeface.png"

void triangle_init();
void triangle_draw();

void texture_init();
void texture_draw();
void texture_exit();

void space_test_init();
void space_test_exit();
void space_test_exit();
#endif
