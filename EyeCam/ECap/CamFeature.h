#ifndef CamFeature_H__
#define CamFeature_H__


typedef struct _tagCamFeature
{
	BOOL    bBW;
	BOOL    bRawDataShow;
	BOOL    bClearView;
	BOOL    bPause;
	BOOL    bUpDown;
	BOOL    bCaptureRaw;
}CAMFEATURE, *PCAMFEATURE;


// ͨ����ȡ��״ֵ̬���õ���bits���ŵ�״̬
#define GETBITSTATUS( btIn, bits )		  ( btIn & ( 0x01 << bits ) ) ? 1 : 0

// ���ý���bits������Ϊ��ʱ��Outֵ
#define SETBIT( usOut, bits )         usOut |= ( 0x0100 << bits ); \
									usOut |= ( 0x01 << bits );

// ���ý���bits������Ϊ��ʱ��Outֵ
#define CLEARBIT( usOut, bits )       usOut |=  ( 0x0100 << bits ); \
									usOut &= ( ~( 0x01 << bits ) );

// ���ö���bits����ʱ��Outֵ
#define GETBIT( usOut, bits )		  usOut &= ( ~( 0x0100 << bits ) );


#endif // CamFeature_H__
