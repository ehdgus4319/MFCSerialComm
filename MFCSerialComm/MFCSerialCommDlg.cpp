
// MFCSerialCommDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCSerialComm.h"
#include "MFCSerialCommDlg.h"
#include "afxdialogex.h"
#include "stdafx.h"
#include <string>
#include <vector>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int flag[3];

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCSerialCommDlg 대화 상자



CMFCSerialCommDlg::CMFCSerialCommDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSERIALCOMM_DIALOG, pParent)
	, m_str_comport(_T(""))
	, m_combo_baudrate(_T(""))



	, m_Edit_LED_1(_T(""))
	, m_Edit_LED_2(_T(""))
	, m_Edit_LED_3(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCSerialCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_COMPORT, m_combo_comport_list);
	DDX_CBString(pDX, IDC_COMBO_COMPORT, m_str_comport);
	DDX_Control(pDX, IDC_COMBO_BAUDRATE, m_combo_baudrate_list);
	DDX_CBString(pDX, IDC_COMBO_BAUDRATE, m_combo_baudrate);


	DDX_Text(pDX, IDC_EDIT1, m_Edit_LED_1);
	DDX_Text(pDX, IDC_EDIT2, m_Edit_LED_2);
	DDX_Text(pDX, IDC_EDIT3, m_Edit_LED_3);
}

BEGIN_MESSAGE_MAP(CMFCSerialCommDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_CONNECT, &CMFCSerialCommDlg::OnBnClickedBtConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCSerialCommDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCSerialCommDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCSerialCommDlg::OnBnClickedButton4)

	ON_MESSAGE(WM_MYCLOSE, &CMFCSerialCommDlg::OnThreadClosed)
	ON_STN_CLICKED(IDC_STATIC1, &CMFCSerialCommDlg::OnStnClickedStatic1)
	ON_MESSAGE(WM_MYRECEIVE, &CMFCSerialCommDlg::OnReceive)

END_MESSAGE_MAP()


// CMFCSerialCommDlg 메시지 처리기

BOOL CMFCSerialCommDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_combo_comport_list.AddString(_T("COM1"));
	m_combo_comport_list.AddString(_T("COM2"));
	m_combo_comport_list.AddString(_T("COM3"));
	m_combo_comport_list.AddString(_T("COM4"));
	m_combo_comport_list.AddString(_T("COM5"));
	m_combo_comport_list.AddString(_T("COM6"));
	m_combo_comport_list.AddString(_T("COM7"));
	m_combo_comport_list.AddString(_T("COM8"));
	m_combo_comport_list.AddString(_T("COM9"));
	m_combo_comport_list.AddString(_T("COM10"));

	m_combo_baudrate_list.AddString(_T("9600"));
	m_combo_baudrate_list.AddString(_T("19200"));
	m_combo_baudrate_list.AddString(_T("115200"));

	comport_state = false;
	GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
	m_str_comport = _T("COM10");
	m_combo_baudrate = _T("115200");




	UpdateData(FALSE);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCSerialCommDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCSerialCommDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCSerialCommDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT	CMFCSerialCommDlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	((CSerialComm*)lpara)->HandleClose();
	delete ((CSerialComm*)lpara);

	return 0;
}
uint8_t buf[40];
uint8_t bufindex = 0;

std::vector<char>rxBuffer;

// m_edit_led_1 m_edit_led_2 m_edit_led_3
LRESULT CMFCSerialCommDlg::OnReceive(WPARAM length, LPARAM lpara)
{
	char* data = new char[length + 1];
	if (m_comm)
	{
		m_comm->Receive(data, length);	// Length 길이만큼 데이터 받음.
		data[length] = _T('\0');
		//str += _T("\r\n");
		for (int i = 0; i < length; i++)
		{
			rxBuffer.push_back(data[i]);
		}

		
		while (rxBuffer.size() >= 8)
		{

			if (rxBuffer.at(0) == '$' && rxBuffer.at(7) == 'E')
			{
				if (rxBuffer.at(1) == '1' && rxBuffer.at(2) == '1') // LED 1 번 제어
				{

					m_Edit_LED_1.SetString("LED1ON");
					GetDlgItem(IDC_BUTTON2)->SetWindowTextA(_T("LED1ON"));
					flag[0] = 1;

				}
				else if (rxBuffer.at(1) == '1' && rxBuffer.at(2) == '0')
				{

					m_Edit_LED_1.SetString("LED1OFF");
					GetDlgItem(IDC_BUTTON2)->SetWindowTextA(_T("LED1OFF"));
					flag[0] = 0;

				}

				if (rxBuffer.at(3) == '2' && rxBuffer.at(4) == '1') // LED 2 번 제어
				{
					m_Edit_LED_2.SetString("LED2ON");
					GetDlgItem(IDC_BUTTON3)->SetWindowTextA(_T("LED2ON"));
					flag[1] = 1;
				}
				else if (rxBuffer.at(3) == '2' && rxBuffer.at(4) == '0')
				{
					m_Edit_LED_2.SetString("LED2OFF");
					GetDlgItem(IDC_BUTTON3)->SetWindowTextA(_T("LED2OFF"));
					flag[1] = 0;
				}

				if (rxBuffer.at(5) == '3' && rxBuffer.at(6) == '1')  // LED 3 번 제어
				{
					m_Edit_LED_3.SetString("LED3ON");
					GetDlgItem(IDC_BUTTON4)->SetWindowTextA(_T("LED3ON"));
					flag[2] = 1;
				}
				else if (rxBuffer.at(5) == '3' && rxBuffer.at(6) == '0')
				{
					m_Edit_LED_3.SetString("LED3OFF");
					GetDlgItem(IDC_BUTTON4)->SetWindowTextA(_T("LED3OFF"));
					flag[3] = 0;
				}
				rxBuffer.erase(rxBuffer.begin(), rxBuffer.begin() + 8);
			}
			else
			{
				while (rxBuffer.at(0) != '$') 
				{
					rxBuffer.erase(rxBuffer.begin());
					if (rxBuffer.size() == 0)
						break;
				}
					
			}
		}
		
		

		/*
		if (str != "")
		{
			CString tmp_led_2;
			if (data[0] == '$')  // 데이터 시작 문자
			{
				if (data[7] == 'E')  // 데이터 끝 문자
				{
					if (data[1] == '1' && data[2] == '1')   // LED 1 상태
					{
						m_Edit_LED_1.SetString("LED 1 ON");
						GetDlgItem(IDC_BUTTON2)->SetWindowTextA(_T("LED1 ON"));
					}
					else if (data[1] == '1' && data[2] == '0')
					{
						m_Edit_LED_1.SetString("LED 1 OFF");
						GetDlgItem(IDC_BUTTON2)->SetWindowTextA(_T("LED1 OFF"));
					}


					if (data[3] == '2' && data[4] == '1')  // LED 2 상태
					{
						m_Edit_LED_2.SetString("LED 2 ON");
						GetDlgItem(IDC_BUTTON3)->SetWindowTextA(_T("LED2 ON"));
					}
					else if (data[3] == '2' && data[4] == '0')
					{
						m_Edit_LED_2.SetString("LED 2 OFF");
						GetDlgItem(IDC_BUTTON3)->SetWindowTextA(_T("LED2 OFF"));
					}

					if (data[5] == '3' && data[6] == '1')  // LED 3 상태
					{
						m_Edit_LED_3.SetString("LED 3 ON");
						GetDlgItem(IDC_BUTTON4)->SetWindowTextA(_T("LED3 ON"));
					}
					else if (data[5] == '3' && data[6] == '0')
					{
						m_Edit_LED_3.SetString("LED 3 OFF");
						GetDlgItem(IDC_BUTTON4)->SetWindowTextA(_T("LED3 OFF"));
					}
				}
			}

		}
		*/

		UpdateData(false);

	}
	//delete data;
	rxBuffer.clear();

	return 0;
}

void CMFCSerialCommDlg::OnBnClickedBtConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	if (comport_state)
	{
		if (m_comm)        //컴포트가존재하면
		{
			m_comm->Close();
			m_comm = NULL;
			AfxMessageBox(_T("COM 포트닫힘"));
			comport_state = false;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("OPEN"));
			GetDlgItem(IDC_BUTTON2)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
			GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
		}
	}
	else
	{
		m_comm = new CSerialComm(_T("\\\\.\\") + m_str_comport, m_combo_baudrate, _T("None"), _T("8 Bit"), _T("1 Bit"));         // initial Comm port
		if (m_comm->Create(GetSafeHwnd()) != 0) //통신포트를열고윈도우의핸들을넘긴다.
		{
			AfxMessageBox(_T("COM 포트열림"));
			comport_state = true;
			GetDlgItem(IDC_BT_CONNECT)->SetWindowText(_T("CLOSE"));
			GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON3)->EnableWindow(true);
			GetDlgItem(IDC_BUTTON4)->EnableWindow(true);

		}
		else
		{
			AfxMessageBox(_T("ERROR!"));
		}

	}
}

void CMFCSerialCommDlg::OnCbnSelchangeComboComport()
{
	// TODO: Add your control notification handler code here
	UpdateData(); /* 추가 부분  MrKang*/
}


void CMFCSerialCommDlg::OnCbnSelchangeComboBaudrate()
{
	// TODO: Add your control notification handler code here
	UpdateData(); /* 추가 부분  MrKang*/
}

void CMFCSerialCommDlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	CString tmp;
	if (m_Edit_LED_1 == _T("LED1OFF"))
	{
		m_Edit_LED_1 = _T("LED1ON");
		GetDlgItem(IDC_BUTTON2)->SetWindowTextA(_T("LED1ON"));
		tmp = "";
		tmp += _T("LED1ON");
	}
	else if (m_Edit_LED_1 == _T("LED1ON"))
	{
		m_Edit_LED_1 = _T("LED1OFF");
		GetDlgItem(IDC_BUTTON2)->SetWindowTextA(_T("LED1OFF"));
		tmp = "";
		tmp += _T("LED1OFF");
	}

	tmp += "\r\n";
	UpdateData(false);

	m_comm->Send(tmp, tmp.GetLength());


}


void CMFCSerialCommDlg::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//0UpdateData(true);
	CString str;

	if (flag[1] == 1)
	{
		m_Edit_LED_2 = _T("LED2OFF");
		//GetDlgItem(IDC_BUTTON3)->SetWindowTextA(_T("LED2OFF"));
		str = "";
		str += _T("LED2OFF");

	}
	else if (flag[1] == 0)
	{
		m_Edit_LED_2 = _T("LED2ON");
		//GetDlgItem(IDC_BUTTON3)->SetWindowTextA(_T("LED2ON"));
		str = "";
		str += _T("LED2ON");

	}
	str += "\r\n";
	m_comm->Send(str, str.GetLength());


}


void CMFCSerialCommDlg::OnBnClickedButton4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


}


void CMFCSerialCommDlg::OnStnClickedStatic1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
