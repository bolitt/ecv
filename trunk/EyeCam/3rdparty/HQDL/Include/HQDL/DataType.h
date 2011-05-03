#ifndef DATATYPE_H
#define DATATYPE_H

/*-------------------------------------------------------------
	����ֵ����
  *===========================================================*/
#define		ResSuccess					0x0000		// ���سɹ�
#define		ResNullHandleErr			0x0001		// ��Ч���
#define		ResNullPointerErr			0x0002		// ָ��Ϊ��
#define		ResFileOpenErr				0x0003
#define		ResNoDeviceErr				0x0004
#define		ResInvalidParameterErr		0x0005
#define		ResOutOfMemoryErr			0x0006
#define		ResNoPreviewRunningErr		0x0007		// Ԥ��û�п���
#define		ResOSVersionErr				0x0008
#define		ResUsbNotAvailableErr		0x0009
#define		ResNotSupportedErr			0x000a
#define		ResNoSerialString			0x000b
#define		ResVerificationErr			0x000c
#define		ResTimeoutErr	            0x000d
#define		ResScaleModeErr				0x000f
#define		ResUnknownErr				0x00ff

#define     ResFail						0x0010
#define		ResDisplayWndExist			0x0011		// Ӧ�ùر�Ԥ������
#define		ResAllocated				0x0012		// �ڴ��Ѿ�����
#define		ResAllocateFail				0x0013		// �ڴ����ʧ��
#define		ResReadError				0x0014      // USB��ȡʧ��
#define		ResWriteError				0x0015		// USB�����ʧ��
#define		ResUsbOpen					0x0016      // USB�˿��Ѿ���
#define     ResCreateStreamErr			0x0017		// ����avi��ʧ��
#define     ResSetStreamFormatErr		0x0018		// ����AVI����ʽʧ��

typedef struct _tagDLVIDEORECT
{
	int     Left;		// ����ڸ����ڵ�ˮƽƫ��
	int     Top;		// ����ڸ����ڵĴ�ֱƫ��
	int     Width;		// ��Ƶ���ڿ��
	int     Height;		// ��Ƶ���ڸ߶�
}DLVIDEORECT, *PDLVIDEORECT;

/*-------------------------------------------------------------
	����ͷ��ز����ṹ
  *===========================================================*/
struct CapInfoStruct 
{
	UCHAR	*Buffer;		// �û����䣬���ڷ���ԭʼ����8bit
	ULONG	Height;			// �ɼ��߶�
	ULONG	Width;			// �ɼ����
	ULONG	OffsetX;		// ˮƽƫ��
	ULONG	OffsetY;		// ��ֱƫ��
	ULONG	Exposure;		// �ع�ֵ 1-500MS
	UCHAR	Gain[3];		// R G B ���� 1-63
	UCHAR	Control;		// ����λ
	UCHAR	InternalUse;	// �û���Ҫ�Դ��ֽڽ��в���
	UCHAR	ColorOff[3];	// �û������治Ҫ�ı�������ֵ��Ҫ����EnableColorOffset���ı�
	UCHAR	Reserved[4];	// ����λ
};


/*-----------------------------------------------------------
	Control ����λ˵��
	BIT7       BIT6      BIT5     BIT4     BIT3     BIT2     BIT1     BIT0
	UV         IR        VB       RESERVED RESERVED SENSE1   SENSE0   Camera Switch(Golden Eagle only)
  ===========================================================*/

enum     DLPARAM {  BWSHOW = 0,		// �Ƿ�ڰ���ʾ
					RAWDATASHOW,	// �Ƿ�ֱ����ʾԭʼ����
					CLEARVIEW,		// �Ƿ������Ż��㷨����ת��
					UPDOWN,			// ���·�ת
	};

#endif