////////////////////////////////////////////////////////// �������ݰ���ʽ��س���������"��������빤λ�������ͨѶЭ��"-begin
// �������ݰ�(���)����[Byte]
const unsigned int g_unNetPackSize = 1024;
// �������ݰ���ͷ��С[Byte]
const unsigned int g_unNetPackHeaderSize = 2;
// �������ݰ�"���ݶδ�Сָʾ��(DataSecSizePointer)"��С
const unsigned int g_unNetPackDSSPSize = 4;
// �������ݰ���β��С[Byte]
const unsigned int g_unNetPackTailSize = 2;
// ������QN��С
const unsigned int g_unQNSize = 17;
// �ܰ���PCNT��С
const unsigned int g_unPCNTSize = 4;
// ����PNO��С
const unsigned int g_unPNOSize = 4;
// �������ݰ�����ʶռ�õ��ܴ�С
const unsigned int g_unNetPackSignsSize = g_unNetPackHeaderSize + g_unNetPackDSSPSize + g_unNetPackTailSize + g_unQNSize + g_unPCNTSize + g_unPNOSize;
// �������ݰ�(���)��������
const unsigned int g_unNetPackPayloadSize = g_unNetPackSize - g_unNetPackSignsSize;
// ��ͷ��ʶ
const char * const g_pchNetPackHeaderSign = "##";
// ��β��ʶ
const char * const g_pchNetPackTailSign = "\r\n";
////////////////////////////////////////////////////////// �������ݰ���ʽ��س���������"��������빤λ�������ͨѶЭ��"-end
