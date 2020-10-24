////////////////////////////////////////////////////////// 网络数据包格式相关常量，根据"调度软件与工位控制软件通讯协议"-begin
// 网络数据包(最大)容量[Byte]
const unsigned int g_unNetPackSize = 1024;
// 网络数据包包头大小[Byte]
const unsigned int g_unNetPackHeaderSize = 2;
// 网络数据包"数据段大小指示区(DataSecSizePointer)"大小
const unsigned int g_unNetPackDSSPSize = 4;
// 网络数据包包尾大小[Byte]
const unsigned int g_unNetPackTailSize = 2;
// 请求编号QN大小
const unsigned int g_unQNSize = 17;
// 总包数PCNT大小
const unsigned int g_unPCNTSize = 4;
// 包号PNO大小
const unsigned int g_unPNOSize = 4;
// 网络数据包各标识占用的总大小
const unsigned int g_unNetPackSignsSize = g_unNetPackHeaderSize + g_unNetPackDSSPSize + g_unNetPackTailSize + g_unQNSize + g_unPCNTSize + g_unPNOSize;
// 网络数据包(最大)负载容量
const unsigned int g_unNetPackPayloadSize = g_unNetPackSize - g_unNetPackSignsSize;
// 包头标识
const char * const g_pchNetPackHeaderSign = "##";
// 包尾标识
const char * const g_pchNetPackTailSign = "\r\n";
////////////////////////////////////////////////////////// 网络数据包格式相关常量，根据"调度软件与工位控制软件通讯协议"-end
