// compute_expresionsDlg.cpp : implementation file
//
/*
	Copyright 2006 Gabriel Dimitriu

	This file is part of Compute Expresions.

    Compute Expresions is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Compute Expresions is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Compute Expresions; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/

#include "stdafx.h"
#include "compute_expresions.h"
#include "compute_expresionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompute_expresionsDlg dialog

CCompute_expresionsDlg::CCompute_expresionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCompute_expresionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCompute_expresionsDlg)
	m_result = _T("");
	m_expresion = _T("");
	m_history = _T("");
	m_memory = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCompute_expresionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompute_expresionsDlg)
	DDX_Text(pDX, IDC_result, m_result);
	DDX_Text(pDX, IDC_expresion, m_expresion);
	DDX_Text(pDX, IDC_history, m_history);
	DDX_Text(pDX, IDC_memory, m_memory);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCompute_expresionsDlg, CDialog)
	//{{AFX_MSG_MAP(CCompute_expresionsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_compute, Oncompute)
	ON_BN_CLICKED(IDC_reset, Onreset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompute_expresionsDlg message handlers

BOOL CCompute_expresionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	parser=new Cparser_func;
	parser->assign_memory(&memory);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCompute_expresionsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCompute_expresionsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCompute_expresionsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCompute_expresionsDlg::Oncompute() 
{
	UpdateData(TRUE);
	double rez;
	m_history.Insert(m_history.GetLength(),m_expresion);
	m_history.Insert(m_history.GetLength(),"\n");
	LPSTR wstr;
	wstr=m_expresion.GetBuffer(100);
	int type=this->GetCheckedRadioButton(IDC_polish,IDC_algebric);
	if(type==IDC_algebric)
	{
		parser->set_function(wstr);
		m_expresion.ReleaseBuffer(100);
		parser->eval_func(&rez);
		m_result.Empty();
		m_result.Format("%lf",rez);
		m_memory.Empty();
		int flag=0;
		double val;
		char name[256];
		memory.resetGet();
		while(flag==0)
		{
			flag=memory.getVal(&val,name);
			if(flag==0)
			{
				CString temp;
				temp.Empty();
				temp.Format("%s=%lf\n",name,val);
				m_memory.Insert(m_memory.GetLength(),temp);
			}
		}
	}
	if(type==IDC_polish)
	{
		rez=polish.polish(wstr);
		m_expresion.ReleaseBuffer(100);
		m_result.Empty();
		m_result.Format("%lf",rez);
		m_memory.Empty();
		int flag=0;
		double val;
		char name;
		polish.resetGet();
		while(flag==0)
		{
			flag=polish.Get(name,val);
			if(flag==0)
			{
				CString temp;
				temp.Empty();
				temp.Format("%c=%lf\n",name,val);
				m_memory.Insert(m_memory.GetLength(),temp);
			}
		}
	}
	UpdateData(FALSE);
}

void CCompute_expresionsDlg::Onreset() 
{
	int type=this->GetCheckedRadioButton(IDC_polish,IDC_algebric);
	if(type==IDC_algebric)
		memory.deletedata();
	if(type==IDC_polish)
		polish.deletedata();
	m_history.Empty();
	m_memory.Empty();
	m_result.Empty();
	m_expresion.Empty();
	UpdateData(FALSE);
}
