// (C) Copyright 2002-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- MethodChooseDialog.cpp : Implementation of CMethodChooseDialog
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "MethodChooseDialog.h"

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC (CMethodChooseDialog, CAcUiDialog)

BEGIN_MESSAGE_MAP(CMethodChooseDialog, CAcUiDialog)
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)
	ON_BN_CLICKED(IDOK, &CMethodChooseDialog::OnBnClickedOk)
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
CMethodChooseDialog::CMethodChooseDialog (CWnd *pParent /*=NULL*/, 
	HINSTANCE hInstance /*=NULL*/) : CAcUiDialog (CMethodChooseDialog::IDD, pParent, hInstance) {
}

//-----------------------------------------------------------------------------
void CMethodChooseDialog::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO_THEORETICAL_CALCULATION, mRadioTheoretical);
	DDX_Control(pDX, IDC_RADIO_PROGRAM_EXPERIENCE, mRadioExperience);
	DDX_Control(pDX, IDC_RADIO_LOOSE_RANGE_DESIGN, mRadioLooseRange);
	DDX_Control(pDX, IDC_RADIO_EXPERT_DECISION, mRadioExpert);
	DDX_Control(pDX, IDC_STATIC_CHOOSE_METHOD, mMethodChooseTitle);
}

//-----------------------------------------------------------------------------
//----- Needed for modeless dialogs to keep focus.
//----- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT CMethodChooseDialog::OnAcadKeepFocus (WPARAM, LPARAM) {
	return (TRUE) ;
}


void CMethodChooseDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int pTheoreticalState = mRadioTheoretical.GetCheck();
	int pExperienceState = mRadioExperience.GetCheck();
	int pLooseState = mRadioLooseRange.GetCheck();
	int pExpertState = mRadioExpert.GetCheck();

	if(pTheoreticalState != 0)
	{
		//理论法被选中
		CTheoreticalDialog * mTheoDlg = new CTheoreticalDialog();
		mTheoDlg->DoModal();
	}
	if (pExperienceState != 0)
	{
		CExperienceDialog * mExpDlg = new CExperienceDialog();
		mExpDlg->DoModal();
	}
	if (pLooseState != 0) {
		CLooseRangeDialog * mLooseDlg = new CLooseRangeDialog();
		mLooseDlg->DoModal();
	}
	if (pExpertState != 0) {
		CTunnelChooseDialog::GetInstance()->StartParameterDialog();
	}
}


BOOL CMethodChooseDialog::OnInitDialog()
{
	CAcUiDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CRect dlg;
	GetWindowRect(dlg);
	ScreenToClient(dlg);
	SetWindowPos(&wndTopMost, (GetSystemMetrics(SM_CXSCREEN) / 2) - (dlg.Width() / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (dlg.Height() / 2), dlg.Width(), dlg.Height(),
		SWP_SHOWWINDOW);

	// 设置标题字体
	mMethodChooseTitle.SetFont(CDrawUtil::GetTitleFont());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
