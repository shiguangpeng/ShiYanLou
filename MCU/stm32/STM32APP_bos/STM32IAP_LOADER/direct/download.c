/*******************************************************************************
** �ļ���: 		download.c
** �汾��  		1.0
** ��������: 	RealView MDK-ARM 5 
** ����: 		wuguoyana
** ��������: 	2011-04-29
** ����:		�ȴ��û�ѡ�����ļ�����,���߷��������Լ�һЩ��ʾ��Ϣ��
                ������ʵ�ִ��͵���ymodem��cԴ�ļ���
** ����ļ�:	common.h
** �޸���־��	2011-04-29   �����ĵ�
*******************************************************************************/

/* ����ͷ�ļ� *****************************************************************/
#include "common.h"

/* �������� ------------------------------------------------------------------*/
extern uint8_t file_name[FILE_NAME_LENGTH];
uint8_t tab_1024[1024] =
{
    0
};

/*******************************************************************************
  * @��������	SerialDownload
  * @����˵��   ͨ�����ڽ���һ���ļ�
  * @�������   ��
  * @�������   ��
  * @���ز���   ��
*******************************************************************************/
void SerialDownload(void)
{
    uint8_t Number[10] = "          ";// �洢�ļ���С���ַ�������
    int32_t Size = 0;//�ļ���С
    // ��ʾ��Ϣ
    SerialPutString("Waiting for the file to be sent ... (press 'a' to abort)\n\r");
    Size = Ymodem_Receive(&tab_1024[0]);//�����ļ� �������ļ���С
    if (Size > 0) //�ļ����سɹ�  ���ﲻ֪�� �����Ƿ����� ����
    {
        SerialPutString("\n\n\r Programming Completed Successfully!\n\r--------------------------------\r\n Name: ");
        SerialPutString(file_name);//�ļ���
        Int2Str(Number, Size);     //����ת�����ַ���  ����Size ת�����ַ���Number
        SerialPutString("\n\r Size: ");
        SerialPutString(Number);   //��ʾ��С
        SerialPutString(" Bytes\r\n");
		    // SerialPutString(" Bytes\r\n");
        SerialPutString("-------------------\n");
			  FLASH_WriteByte(g_bUpdateFlag_Address,0x00); //���� ������־
			  NVIC_SystemReset();  //������ɺ�����ϵͳ
    }
    else if (Size == -1)//�ļ���С���������ڴ�ռ�
    {
        SerialPutString("\n\n\rThe image size is higher than the allowed space memory!\n\r");
			  FLASH_WriteByte(g_bUpdateFlag_Address,0x00); //���� ������־
			  NVIC_SystemReset();  //������ɺ�����ϵͳ
    }
    else if (Size == -2)//�ļ�CRCУ��ʧ��
    {
        SerialPutString("\n\n\rVerification failed!\n\r");
			  FLASH_WriteByte(g_bUpdateFlag_Address,0x00); //���� ������־
			  NVIC_SystemReset();  //������ɺ�����ϵͳ
    }
    else if (Size == -3)//�û���ֹ
    {
        SerialPutString("\r\n\nAborted by user.\n\r");
			  FLASH_WriteByte(g_bUpdateFlag_Address,0x00); //���� ������־
			  NVIC_SystemReset();  //������ɺ�����ϵͳ
    }
    else                //�����ļ�ʧ��
    {
        SerialPutString("\n\rFailed to receive the file!\n\r");
			  FLASH_WriteByte(g_bUpdateFlag_Address,0x00); //���� ������־
			  NVIC_SystemReset();  //������ɺ�����ϵͳ
    }
		
}

/*******************************�ļ�����***************************************/