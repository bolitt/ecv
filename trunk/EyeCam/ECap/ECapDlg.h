#if !defined(AFX_ECAPDLG_H__305025F0_5BF0_4EDD_AC52_928C854DA164__INCLUDED_)
#define AFX_ECAPDLG_H__305025F0_5BF0_4EDD_AC52_928C854DA164__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "CamFeature.h"
#include "Clip.h"

class DCam
{
protected:
	BYTE             *m_pRawData;
	BYTE             *m_pRgbData;
	CapInfoStruct    m_CapInfo;
	int       m_nROff, m_nGOff, m_nBOff;
	HANDLE    m_hDevice;
	CAMFEATURE       m_CamFeature;

	USHORT    m_Out;
	BYTE      m_In;
};

class ECapDlg : public CDialog, DCam
{
public:
	void ReadPin( int PinNum );
	void IOControl();
	void FinishAE( DWORD dwResult );
	void FinishAWB( DWORD dwResult );
	VOID SetCamFeature();
	ECapDlg(CWnd* pParent = NULL);
	//{{AFX_DATA(ECapDlg)
	enum { IDD = IDD_DLCWBDEMO_DIALOG };
	CComboBox	m_comboValue;
	CComboBox	m_comboRW;
	CComboBox	m_comboPin;
	CStatic	m_staticVideo;
	CSliderCtrl	m_sliderColor;
	CComboBox	m_comboColor;
	CComboBox	m_comboSize;
	Clip		m_clip;

	CString	m_strMessage;
	BOOL	m_bPlay;
	BOOL	m_bCapture;
	BOOL	m_bRawDataShow;
	BOOL	m_bUpDown;
	BOOL	m_bClearPreview;
	BOOL	m_bBW;
	BOOL	m_bPause;
	//}}AFX_DATA
	//{{AFX_VIRTUAL(ECapDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(ECapDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnCheckPlay();
	afx_msg void OnSelchangeComboSize();
	afx_msg void OnSelchangeComboColor();
	afx_msg void OnReleasedcaptureSliderColor(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonCap();
	afx_msg void OnCheckBW();
	afx_msg void OnCheckClearB();
	afx_msg void OnCheckRawdata();
	afx_msg void OnCheckUpdown();
	afx_msg void OnButtonAWB();
	afx_msg void OnButtonAE();
	afx_msg void OnCheckPause();
	afx_msg void OnButtonTestRead();
	afx_msg void OnButtonTestWrite();
	afx_msg void OnButtonRW();
	afx_msg void OnSelChangeComboRW();
	afx_msg HRESULT UserRW(WPARAM wParam, LPARAM lParam) ;
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////////////
private:
	VOID      Play( BOOL bPlay );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ECAPDLG_H__305025F0_5BF0_4EDD_AC52_928C854DA164__INCLUDED_)
