#include "stdafx.h"
#include "ECap.h"
#include "ECapDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_USER_RW   WM_USER + 505


/*--------------------------------------------------------------------
	any question, please send email:          mike.lab@huaqi.com
  ==================================================================*/
VOID CALLBACK AWBCallback( DWORD dw1, LPVOID lpContext )
{
	ECapDlg *pDlgDemo = ( ECapDlg*)lpContext;
	DWORD     dwResult = dw1;
	pDlgDemo->FinishAWB( dwResult );
}

VOID CALLBACK AECallback( DWORD dw1, LPVOID lpContext )
{
	ECapDlg *pDlgDemo = ( ECapDlg*)lpContext;
	DWORD     dwResult = dw1;
	pDlgDemo->FinishAE( dwResult );
}


VOID CALLBACK WINAPI FrameCallBack( LPVOID lpParam1, LPVOID lpPoint, LPVOID lpContext )
{
	UCHAR *pRgb = (UCHAR*)lpParam1;
	OutputDebugString( "Frame CallBack!!!!!!!");
	ECapDlg* pDLDlg = (ECapDlg*)lpContext;

	static int Count = 0;
	TCHAR  Buf[256];
	_stprintf( Buf, "%d", Count );
	OutputDebugString( Buf );
	// 每读一帧，就读取一个引脚
	pDLDlg->ReadPin( Count % 8 );
	Count++;
}



ECapDlg::ECapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ECapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLCWBDEMODlg)
	m_bPlay = FALSE;
	m_bCapture = FALSE;
	m_strMessage = _T("");
	m_bRawDataShow = FALSE;
	m_bUpDown = FALSE;
	m_bClearPreview = FALSE;
	m_bBW = FALSE;
	m_bPause = FALSE;
	//}}AFX_DATA_INIT
	m_hDevice = NULL;
}

void ECapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLCWBDEMODlg)
	DDX_Control(pDX, IDC_COMBOVALUE, m_comboValue);
	DDX_Control(pDX, IDC_COMBORW, m_comboRW);
	DDX_Control(pDX, IDC_COMBOPIN, m_comboPin);
	DDX_Control(pDX, IDC_STATIC_VIDEO, m_staticVideo);
	DDX_Control(pDX, IDC_SLIDER_COLOR, m_sliderColor);
	DDX_Control(pDX, IDC_COMBO_COLOR, m_comboColor);
	DDX_Control(pDX, IDC_COMBO_SIZE, m_comboSize);
	
	DDX_Check(pDX, IDC_CHECK_PLAY, m_bPlay);
	DDX_Text(pDX, IDC_STATIC_MESSAGE, m_strMessage);
	DDX_Check(pDX, IDC_CHECK_RAWDATA, m_bRawDataShow);
	DDX_Check(pDX, IDC_CHECK_UPDOWN, m_bUpDown);
	DDX_Check(pDX, IDC_CHECK_CLEARE, m_bClearPreview);
	DDX_Check(pDX, IDC_CHECK_BW, m_bBW);
	DDX_Check(pDX, IDC_CHECK_PAUSE, m_bPause);

	DDX_Text(pDX, IDC_EDIT_ROW, m_clip.m_currentRow);
	DDX_Text(pDX, IDC_EDIT_COLUMN, m_clip.m_currentColumn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(ECapDlg, CDialog)
	//{{AFX_MSG_MAP(CDLCWBDEMODlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHECK_PLAY, OnCheckPlay)
	ON_CBN_SELCHANGE(IDC_COMBO_SIZE, OnSelchangeComboSize)
	ON_CBN_SELCHANGE(IDC_COMBO_COLOR, OnSelchangeComboColor)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_COLOR, OnReleasedcaptureSliderColor)
	ON_BN_CLICKED(IDC_BUTTON_CAP, OnButtonCap)
	ON_BN_CLICKED(IDC_CHECK_BW, OnCheckBW)
	ON_BN_CLICKED(IDC_CHECK_CLEARE, OnCheckClearB)
	ON_BN_CLICKED(IDC_CHECK_RAWDATA, OnCheckRawdata)
	ON_BN_CLICKED(IDC_CHECK_UPDOWN, OnCheckUpdown)
	ON_BN_CLICKED(IDC_BUTTON_AWB, OnButtonAWB)
	ON_BN_CLICKED(IDC_BUTTON_AE, OnButtonAE)
	ON_BN_CLICKED(IDC_CHECK_PAUSE, OnCheckPause)
	ON_BN_CLICKED(IDC_BUTTON_TESTREAD, OnButtonTestRead)
	ON_BN_CLICKED(IDC_BUTTON_TESTWRITE, OnButtonTestWrite)
	ON_BN_CLICKED(IDC_BUTTONRW, OnButtonRW)
	ON_WM_SYSCOMMAND()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBORW, OnSelChangeComboRW)
	ON_MESSAGE( WM_USER_RW, UserRW )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void ECapDlg::OnPaint() 
{
	CDialog::OnPaint();
}

BOOL ECapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_nROff = m_nGOff = m_nBOff = 0;

	memset( &m_CamFeature, 0, sizeof( CAMFEATURE ) );

	m_pRawData = NULL;
	m_pRawData = ( BYTE* ) new BYTE [ MAXWIDTH * MAXHEIGHT + 512 ];
	m_pRgbData = NULL;
	m_pRgbData = ( BYTE* ) new BYTE [ MAXWIDTH * MAXHEIGHT * 3 ];
	memset( &m_CapInfo, 0, sizeof( CapInfoStruct ) );
	m_CapInfo.Buffer = m_pRawData;
	m_CapInfo.Width    = 640;
	m_CapInfo.Height   = 480;
	m_CapInfo.Exposure = 60;
	memset( m_CapInfo.Gain, 44, 3 );
	///////////////////////////////////////////////////////////////
	
	m_comboSize.SetCurSel( 2 );
	m_comboColor.SetCurSel( 0 );

	int    nIndex;
	if( ResSuccess != HqDLInitialize(_T("Golden Hawk"), &nIndex, &m_CapInfo, &m_hDevice ) ) 
	{
		HqDLUninitialize( &m_hDevice );	
		m_hDevice = NULL;
		::MessageBox( NULL, _T("Initial Error"), _T("Demo"), 0 );
		return FALSE;
	}
	SetCamFeature();

	HqDLEnableColorOffset( m_hDevice, 0, 0, 0, TRUE );


	// IO
	m_comboRW.SetCurSel( 0 );
	m_comboPin.SetCurSel( 0 );
	m_comboValue.EnableWindow( m_comboRW.GetCurSel() ? TRUE : FALSE );
	m_comboValue.SetCurSel( 0 );

	m_Out = 0x0000;
	m_In  = 0x00;

	GETBIT( m_Out, 0 );
	HqDLBitOperationX( m_hDevice, m_Out, &m_In );

	m_comboValue.SetCurSel( GETBITSTATUS( m_In, 0 ) );

	UpdateData( FALSE );


	return TRUE; 
}

BOOL ECapDlg::DestroyWindow() 
{
	
	Play( FALSE );
	if( m_pRawData )
	{
		delete [] m_pRawData;
		m_pRawData = NULL;
	}

	if( m_pRgbData )
	{
		delete [] m_pRgbData;
		m_pRgbData = NULL;
	}

	if( m_hDevice != NULL )    
		HqDLUninitialize( &m_hDevice );

	return CDialog::DestroyWindow();
}

void ECapDlg::OnCheckPlay() 
{
	UpdateData();	
	Play( m_bPlay );						// 开始采集/停止采集
}

void ECapDlg::OnSelchangeComboSize() 
{
	int 	nSize = m_comboSize.GetCurSel();
	ULONG   Width, Height;

	switch( nSize )
	{
	case 0: Width = 320;  Height = 240;  break;
	case 1: Width = 640;  Height = 480;  break;
	case 2: Width = 1280; Height = 1024; break;
	case 3: Width = 1600; Height = 1200; break;
	case 4: Width = 2048; Height = 1536; break;
	}

	m_CapInfo.Width		= Width;
	m_CapInfo.Height	= Height;
	HqDLSetCapInfo( m_hDevice, &m_CapInfo );
	UpdateData( FALSE );

}

void ECapDlg::OnSelchangeComboColor() 
{
	if( m_hDevice == NULL )    return;
	int 	nColor = m_comboColor.GetCurSel();
	ULONG   Min = 1;
	ULONG   Max = 1;
	ULONG   Value;
	switch( nColor )
	{
	case 0: Max = 63;  Value = m_CapInfo.Gain[0];    break;
	case 1: Max = 63;  Value = m_CapInfo.Gain[1];    break;
	case 2:	Max = 63;  Value = m_CapInfo.Gain[2];    break;

	case 3: Max = 500; Value = m_CapInfo.Exposure;    break;

	case 4: Min = -255; Max = 255;  Value = m_nROff; break;
	case 5: Min = -255; Max = 255;  Value = m_nGOff; break;
	case 6: Min = -255; Max = 255;  Value = m_nBOff; break;

	case 7: Min = 0; Max = MAXWIDTH - m_CapInfo.Width;		Value = m_CapInfo.OffsetX;		break;
	case 8: Min = 0; Max = MAXHEIGHT - m_CapInfo.Height;    Value = m_CapInfo.OffsetY;		break;

	}

	m_sliderColor.SetRange( Min, Max );
	m_sliderColor.SetPos( Value );
	UpdateData(FALSE);
}

void ECapDlg::OnReleasedcaptureSliderColor(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int      nPos = m_sliderColor.GetPos();
	int      nColor = m_comboColor.GetCurSel();


	switch( nColor )
	{
#ifdef DLC131
	case 0:  
	case 1:  
	case 2:
		m_CapInfo.Gain[0]  = m_CapInfo.Gain[1]  = m_CapInfo.Gain[2] = nPos; 	
		HqDLSetCapInfo( m_hDevice, &m_CapInfo );
		break;		

#else
	case 0:  m_CapInfo.Gain[0] = nPos;    HqDLSetCapInfo( m_hDevice, &m_CapInfo ); break;
	case 1:  m_CapInfo.Gain[1] = nPos;    HqDLSetCapInfo( m_hDevice, &m_CapInfo ); break;
	case 2:	 m_CapInfo.Gain[2] = nPos;    HqDLSetCapInfo( m_hDevice, &m_CapInfo ); break;
#endif
	case 3:  m_CapInfo.Exposure = nPos;    HqDLSetCapInfo( m_hDevice, &m_CapInfo ); break;

#ifdef DLC131
	// for mono camera, you must set Gain[0] = Gain[1] = Gain[2]
	// and m_nROff = m_nGOff = m_nBOff
	case 4:  
	case 5:  
	case 6:
		m_nROff  = m_nGOff  = m_nBOff = nPos; 	HqDLEnableColorOffset( m_hDevice, m_nROff, m_nGOff, m_nBOff, TRUE ); 
		break;		
#else
	case 4:  m_nROff  = nPos; 	HqDLEnableColorOffset( m_hDevice, m_nROff, m_nGOff, m_nBOff, TRUE ); break;
	case 5:  m_nGOff  = nPos; 	HqDLEnableColorOffset( m_hDevice, m_nROff, m_nGOff, m_nBOff, TRUE ); break;
	case 6:  m_nBOff  = nPos; 	HqDLEnableColorOffset( m_hDevice, m_nROff, m_nGOff, m_nBOff, TRUE ); break;
#endif
	case 7:  m_CapInfo.OffsetX = nPos;		HqDLSetCapInfo( m_hDevice, &m_CapInfo ); break;
	case 8:  m_CapInfo.OffsetY = nPos;		HqDLSetCapInfo( m_hDevice, &m_CapInfo ); break;

	}
	
	*pResult = 0;
}



void ECapDlg::OnButtonCap() 
{
	if( m_hDevice == NULL )    return;


	if( m_CamFeature.bRawDataShow )
	{
		m_strMessage = _T( "Raw.bmp" );
		HqDLGetRawFrameToBmp(m_hDevice, &m_CapInfo, m_strMessage );
		UpdateData( FALSE );
		return;
	}

	/*if( m_CamFeature.bPause )
	{
		m_strMessage = _T( "Pause.bmp" );
		HqDLGetRgbFrameToJpeg(m_hDevice, &m_CapInfo, NULL, m_strMessage, 100);
		//HqDLGetPausedFrameToBmp(m_hDevice, NULL, m_strMessage );
		UpdateData( FALSE );
		return;
	}
	else*/
	{
		Play(FALSE);
		CString img = m_clip.GetCurrentImagePath();
		m_strMessage = img;
		int ret = -1;
		const int maxRetry = 0;
		int nRetry = 0;
		do {
			ret = HqDLGetRgbFrameToJpeg(m_hDevice, &m_CapInfo, NULL, img, 100);
			//ret = HqDLGetRgbFrameToBmp( m_hDevice, &m_CapInfo, NULL, img );
			CString retStr;
			retStr.Format(" Code: %d", ret);
			m_strMessage += retStr;
			UpdateData( FALSE );
			
			if (ret == ResSuccess) {
				m_clip.NextColumn();
				m_clip.NextRow();
				break;
			} else if (nRetry < maxRetry) {
				nRetry ++;
				Sleep(100);
			} else {
				break;
			}
		} while (true);
		//HqDLGetRgbFrameToBmp( m_hDevice, &m_CapInfo, NULL, m_strMessage );

		Play(TRUE);
	}

}

VOID ECapDlg::Play( BOOL bPlay )
{
	if( m_hDevice == NULL )     return;
	m_bPlay = bPlay;

	RECT    rect;
	m_staticVideo.GetClientRect( &rect );

	if( m_bPlay )
	{
		HqDLStartView( m_hDevice, _T("Digital Lab"), WS_CHILD | WS_VISIBLE, 0, 0, rect.right, rect.bottom, m_staticVideo.m_hWnd, NULL );
		// You must call HqDLSetFrameCallback After Video Show - Warning!!!!!!!!!!!!
		HqDLSetFrameCallback( m_hDevice, FrameCallBack, this );

	}
	else
	{
		HqDLSetFrameCallback( m_hDevice, NULL, NULL );
		// Sleep( 1000 );
		Sleep( 50 );
		HqDLStopView( m_hDevice );

	}
}


#define MYFREE(PTR )   { if(PTR)   free(PTR);  PTR = NULL; }

void ECapDlg::OnCheckBW() 
{
	UpdateData();
	m_CamFeature.bBW = m_bBW;
	SetCamFeature();
}

void ECapDlg::OnCheckClearB() 
{
	UpdateData();
	m_CamFeature.bClearView = m_bClearPreview;
	SetCamFeature();
	
}

void ECapDlg::OnCheckRawdata() 
{
	UpdateData();
	m_CamFeature.bRawDataShow = m_bRawDataShow;
	SetCamFeature();
	
}

void ECapDlg::OnCheckUpdown() 
{
	UpdateData();
	m_CamFeature.bUpDown = m_bUpDown;
	SetCamFeature();
	
}

VOID ECapDlg::SetCamFeature()
{
	if( m_hDevice == NULL )    return;
#ifdef DLC131
	// for mono camera, you must set RAWDATASHOW is true
	m_CamFeature.bRawDataShow = TRUE;
#endif
	HqDLSetParam( m_hDevice, BWSHOW, m_CamFeature.bBW );
	HqDLSetParam( m_hDevice, RAWDATASHOW, m_CamFeature.bRawDataShow );
	HqDLSetParam( m_hDevice, CLEARVIEW, m_CamFeature.bClearView );
	HqDLSetParam( m_hDevice, UPDOWN, m_CamFeature.bUpDown );

}

void ECapDlg::FinishAWB(DWORD dwResult)
{
	char buf[256];
	sprintf( buf, "AWB Result: 0x%x\n", dwResult );
	OutputDebugString( buf );
	BYTE btRed   = ( BYTE )dwResult;
	BYTE btGreen = ( BYTE ) ( dwResult>>8 );
	BYTE btBlue  = ( BYTE ) ( dwResult>>16 );
	ULONG Exposure = (BYTE)( dwResult>>24 ) * 2;

	m_CapInfo.Gain[0] = btRed;
	m_CapInfo.Gain[1] = btGreen;
	m_CapInfo.Gain[2] = btBlue;
	m_CapInfo.Exposure = Exposure;

	// YOU MUST CALL HqDLSetCapInfo to Update DLL
	HqDLSetCapInfo( m_hDevice, &m_CapInfo );
	m_strMessage.Format( "AWB Result Gain: Red %d, Green %d, Blue %d, Exposure %d\n", btRed, btGreen, btBlue, Exposure );
	// PostMessage to Update Interface
}

void ECapDlg::FinishAE(DWORD dwResult)
{
	ULONG Exposure = dwResult;
	m_CapInfo.Exposure = Exposure;
	// YOU MUST CALL HqDLSetCapInfo to Update DLL
	HqDLSetCapInfo( m_hDevice, &m_CapInfo );

	m_strMessage.Format( "AE Result Exposure %d",m_CapInfo.Exposure );
	// PostMessage to Update Interface
}

void ECapDlg::OnButtonAWB() 
{
	// for mono senor, you don't need AWB anymore!!!!
	if( m_hDevice == NULL )    return;
	HqDLSetDoAWB( m_hDevice, TRUE, 180, AWBCallback, (VOID*)this );
}

void ECapDlg::OnButtonAE() 
{
	if( m_hDevice == NULL )    return;
	HqDLSetDoAE( m_hDevice, TRUE, 180, AECallback, (VOID*)this );
}

void ECapDlg::OnCheckPause() 
{
	if( m_hDevice == NULL )    return;
	UpdateData();
	m_CamFeature.bPause = m_bPause;
	HqDLPauseView( m_hDevice, m_bPause );
}

void ECapDlg::OnButtonTestRead() 
{
	if( m_hDevice == NULL )    return;

	USHORT   OffH	= 0;
	USHORT   OffV	= 0;
	USHORT   Width	= 0;
	USHORT   Height = 0;
	HqDLSizeCalibration( m_hDevice, &OffH, &OffV, &Width, &Height, FALSE );

	m_strMessage.Format( "%d, %d, %d, %d", OffH, OffV, Width, Height );
	UpdateData( FALSE );
}

void ECapDlg::OnButtonTestWrite() 
{
	if( m_hDevice == NULL )    return;
	USHORT   OffH = 10, OffV = 10, Width = 640, Height = 480;
	HqDLSizeCalibration( m_hDevice, &OffH, &OffV, &Width, &Height, TRUE );
	m_strMessage.Format( "%d, %d, %d, %d", OffH, OffV, Width, Height );
	UpdateData( FALSE );
}



void ECapDlg::OnButtonRW() 
{
	if( m_bPlay )    return;	// You cant do IO while Video Showing - Warning!!!!!!!
	IOControl();
}

void ECapDlg::OnSelChangeComboRW() 
{
	m_comboValue.EnableWindow( m_comboRW.GetCurSel() ? TRUE : FALSE );
	UpdateData( FALSE );
}

void ECapDlg::IOControl()
{
	TCHAR Buf[256]; 

	BOOL bWrite = (BOOL)m_comboRW.GetCurSel();	
	BYTE Pin    = m_comboPin.GetCurSel();
	m_comboValue.EnableWindow( m_comboRW.GetCurSel() ? TRUE : FALSE );

	if( bWrite )
	{
		BOOL bHigh = ( BOOL )m_comboValue.GetCurSel();
		if( bHigh )
		{
			SETBIT( m_Out, Pin );
		}
		else
		{
			CLEARBIT( m_Out, Pin );
		}
		_stprintf( Buf, TEXT("!!!!!!!!Out: 0x%x"), m_Out ); 
		OutputDebugString( Buf );

		HqDLBitOperationX( m_hDevice, m_Out, &m_In );
	}

	else
	{
		GETBIT( m_Out, Pin );
		_stprintf( Buf, "!!!!!!!!Out: 0x%x", m_Out ); 
		OutputDebugString( Buf );
		HqDLBitOperationX( m_hDevice, m_Out, &m_In );
		_stprintf( Buf, "!!!!!!!!In: 0x%x", m_In ); 
		OutputDebugString( Buf );
		m_comboValue.SetCurSel( GETBITSTATUS( m_In, Pin ) );
		UpdateData( FALSE );
	}	
}

void ECapDlg::ReadPin(int PinNum)
{
	TCHAR Buf[256]; 
	GETBIT( m_Out, PinNum );
	_stprintf( Buf, TEXT("!!!!!!!!Out: 0x%x"), m_Out ); 
	OutputDebugString( Buf );
	HqDLBitOperationX( m_hDevice, m_Out, &m_In );
	PostMessage( WM_USER_RW, PinNum, 0 );		// To Update Interface
}


LRESULT ECapDlg::UserRW(WPARAM wParam, LPARAM lParam)
{
	int PinNum = wParam;
	m_comboRW.SetCurSel(0);
	m_comboPin.SetCurSel( PinNum );					// SetCurSel Can't call in Callback Function.
	GETBIT( m_Out, PinNum );
	m_comboValue.SetCurSel( GETBITSTATUS( m_In, PinNum ) );

	return 0;
}