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


// 通过读取的状态值，得到第bits引脚的状态
#define GETBITSTATUS( btIn, bits )		  ( btIn & ( 0x01 << bits ) ) ? 1 : 0

// 设置将第bits引脚设为高时的Out值
#define SETBIT( usOut, bits )         usOut |= ( 0x0100 << bits ); \
									usOut |= ( 0x01 << bits );

// 设置将第bits引脚设为低时的Out值
#define CLEARBIT( usOut, bits )       usOut |=  ( 0x0100 << bits ); \
									usOut &= ( ~( 0x01 << bits ) );

// 设置读第bits引脚时的Out值
#define GETBIT( usOut, bits )		  usOut &= ( ~( 0x0100 << bits ) );


#endif // CamFeature_H__
