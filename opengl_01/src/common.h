#ifndef __COMMON__H__
#define __COMMON__H__
#include <iostream>


#define LOGD(format, ...)    fprintf(stderr, "%-20s <%03d> D: " format "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGE(format, ...)    fprintf(stderr, "%-20s <%03d> E: " format "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOGI(format, ...)    fprintf(stderr, "%-20s <%03d> I: " format "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define XDBG(x)  LOGD(#x" = 0x%x", x)
#define DDBG(x)  LOGD(#x" = %d", x)
#define PDBG(x)  LOGD(#x" = %p", x)
#define SDBG(x)  LOGD(#x" = %s", x)

#define HWC_IGNORE(x) ((void)x)

#define HWC_ASSERT(x) do {\
	LOGE(#x "is invalid"); \
	return -ERR_BAD_PARAMETER; \
	}while (0)

void triangle_init();
void triangle_draw();

#endif
