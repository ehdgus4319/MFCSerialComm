﻿
// MFCSerialCommDlg.h: 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "SerialCom.h"


// CMFCSerialCommDlg 대화 상자
class CMFCSerialCommDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCSerialCommDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CSerialComm* m_comm;
	LRESULT		OnThreadClosed(WPARAM length, LPARAM lpara);
	LRESULT		OnReceive(WPARAM length, LPARAM lpara);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSERIALCOMM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_combo_comport_list;
	CString m_str_comport;
	CComboBox m_combo_baudrate_list;
	CString m_combo_baudrate;
public:
	BOOL comport_state;
	afx_msg void OnBnClickedBtConnect();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CEdit m_edit_rcv_view;
	CEdit m_edit_send_data;
	afx_msg void OnCbnSelchangeComboComport();
	afx_msg void OnCbnSelchangeComboBaudrate();



	afx_msg void OnStnClickedStatic1();
	//CString m_static_led_1;
	//CStatic m_Cstatic_LED_1;
	CString m_Edit_LED_1;
	CString m_Edit_LED_2;
	CString m_Edit_LED_3;
};
