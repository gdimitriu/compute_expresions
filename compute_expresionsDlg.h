// compute_expresionsDlg.h : header file
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

#if !defined(AFX_COMPUTE_EXPRESIONSDLG_H__2C0ADDE7_CD48_11DA_B910_8AAB59E47C60__INCLUDED_)
#define AFX_COMPUTE_EXPRESIONSDLG_H__2C0ADDE7_CD48_11DA_B910_8AAB59E47C60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "parser_func.h"
#include "calculexp.h"
/////////////////////////////////////////////////////////////////////////////
// CCompute_expresionsDlg dialog

class CCompute_expresionsDlg : public CDialog
{
// Construction
public:
	CCompute_expresionsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCompute_expresionsDlg)
	enum { IDD = IDD_COMPUTE_EXPRESIONS_DIALOG };
	CString	m_result;
	CString	m_expresion;
	CString	m_history;
	CString	m_memory;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompute_expresionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	Cparser_func *parser;
	Cparser_func_memory memory;
	calculexp polish;
	// Generated message map functions
	//{{AFX_MSG(CCompute_expresionsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void Oncompute();
	afx_msg void Onreset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPUTE_EXPRESIONSDLG_H__2C0ADDE7_CD48_11DA_B910_8AAB59E47C60__INCLUDED_)
