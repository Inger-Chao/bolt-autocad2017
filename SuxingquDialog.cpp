// SuxingquDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCad.h"
#include "SuxingquDialog.h"
#include "afxdialogex.h"
#include "ProjectBuilder.h"
#include "DataChecker.h"
#include "DialogManager.h"


// CSuxingquDialog �Ի���

IMPLEMENT_DYNAMIC(CSuxingquDialog, CDialogEx)

CSuxingquDialog::CSuxingquDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SUXINGQU_METHOD_DIALOG, pParent)
	, mInnerFriction(0)
	, mAvgGravity(0)
	, mBoltAttach(0)
	, mMaiDepth(0)
	, mMeiyanZhongdu(0)
	, mNianPower(0)
	, mShuLength(0)
	, mBoltDesignNumber(0)
	, mBoltDiameter(0)
	, mCableDiameter(0)
	, mCableFreeLength(0)
	, mCableAttach(0)
	, mCableBreakPower(0)
{
	// ������Χ��ƽ���ض�
	mAvgGravity = 24.9;
	mMeiyanZhongdu = 7.3;
	mMaiDepth = 561;
	mNianPower = 4.29;
	mInnerFriction = 37.5;
	mShuLength = 20;

	mBoltDiameter = 16;
	mBoltDesignNumber = 50;
	mBoltAttach = 20;
	mCableDiameter = 22;
	mCableBreakPower = 260;
	mCableAttach = 50;
	mCableFreeLength = 5500;
}

CSuxingquDialog::~CSuxingquDialog()
{
}

void CSuxingquDialog::UpdateUI()
{
	CArcProjectBuilder::GetInstance()->BuildMethod();

	CSuxingquMethod * suxingqu = CArcProjectBuilder::GetInstance()->GetSuxingquMethod();
	UpdateData(TRUE);

	mInnerFriction = suxingqu->GetInnerFriction();
	mAvgGravity = suxingqu->GetAvgGravity();
	mMaiDepth = suxingqu->GetMaiDepth();
	mMeiyanZhongdu = suxingqu->GetMeiyanZhongdu();
	mNianPower = suxingqu->GetNianPower();
	mShuLength = suxingqu->GetShuLength();
	mBoltAttach = suxingqu->GetBoltAttach();
	mBoltDesignNumber = suxingqu->GetBoltDesignNumber();
	mBoltDiameter = suxingqu->GetBoltDiameter();
	mCableDiameter = suxingqu->GetCableDiameter();
	mCableFreeLength = suxingqu->GetCableFreeLength();
	mCableAttach = suxingqu->GetCableAttach();
	mCableBreakPower = suxingqu->GetCableBreakPower();

	mConcreteThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetConcreteThickness();
	mQiThickness = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetQiThickness();

	UpdateData(FALSE);
}

void CSuxingquDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INNER_FRICTION, mInnerFriction);
	DDX_Text(pDX, IDC_EDIT_LOOSE_AVG_GRIVITY, mAvgGravity);
	DDX_Text(pDX, IDC_EDIT_LOOSE_BOLT_ATTACH, mBoltAttach);
	DDX_Text(pDX, IDC_EDIT_MAI_DEPTH, mMaiDepth);
	DDX_Text(pDX, IDC_EDIT_MEIYAN_ZHONGDU, mMeiyanZhongdu);
	DDX_Text(pDX, IDC_EDIT_NIAN_POWER, mNianPower);
	DDX_Text(pDX, IDC_EDIT_SHU_LENGTH, mShuLength);
	DDX_Text(pDX, IDC_EDIT_LOOSE_BOLT_DESIGN_NUMBER, mBoltDesignNumber);
	DDX_Text(pDX, IDC_EDIT_LOOSE_BOLT_DIAMETER, mBoltDiameter);
	DDX_Text(pDX, IDC_EDIT_LOOSE_CABLE_DIAMETER, mCableDiameter);
	DDX_Text(pDX, IDC_EDIT_LOOSE_CABLE_FREELENGTH, mCableFreeLength);
	DDX_Text(pDX, IDC_EDIT_LOOSE_CABLE_ATTACH, mCableAttach);
	DDX_Text(pDX, IDC_EDIT_LOOSE_CABLE_BREAK_POWER, mCableBreakPower);
	DDX_Text(pDX, IDC_EDIT_CONCRETE_THICKNESS, mConcreteThickness);
	DDX_Text(pDX, IDC_EDIT_QI_THICKNESS, mQiThickness);
}

void CSuxingquDialog::CheckThickness()
{
	CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();
	switch (pArc->GetZhihuWay())
	{
	case 1:
		pArc->SetConcreteThickness(0);
		pArc->SetQiThickness(0);
		break;
	case 2:
		pArc->SetConcreteThickness(mConcreteThickness);
		pArc->SetQiThickness(mQiThickness);
		break;
	case 3:
		pArc->SetConcreteThickness(mConcreteThickness);
		pArc->SetQiThickness(0);
		break;
	case 4:
		pArc->SetConcreteThickness(mConcreteThickness);
		pArc->SetQiThickness(mQiThickness);
		break;
	default:
		break;
	}
}

void CSuxingquDialog::SetExpertValue()
{
	CSuxingquMethod * suxingqu = CArcProjectBuilder::GetInstance()->GetSuxingquMethod();

	CBolt * topBolt = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetTopBolt();
	CBolt  * leftBolt = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetLeftBolt();
	CCable *cable = CArcProjectBuilder::GetInstance()->GetArcTunnel()->GetCable();
	int tmp = 1000;

	topBolt->setLength(suxingqu->GetTopBoltLength() * tmp);
	topBolt->setDiameter(suxingqu->GetBoltDiameter());
	topBolt->setNumber(suxingqu->GetTopBoltNumber());
	topBolt->setPitch(suxingqu->GetTopSpaceAndPitch() * tmp);
	topBolt->setSpace(suxingqu->GetTopSpaceAndPitch() * tmp);
	topBolt->setALength(suxingqu->GetBoltALength() * tmp);

	leftBolt->setLength(suxingqu->GetBangBoltLength() * tmp);
	leftBolt->setNumber(suxingqu->GetBangBoltNumber());
	leftBolt->setSpace(suxingqu->GetBangSpaceAndPitch() *tmp);
	leftBolt->setPitch(suxingqu->GetBangSpaceAndPitch() *tmp);
	leftBolt->setDiameter(suxingqu->GetBoltDiameter());
	leftBolt->setALength(suxingqu->GetBoltALength() * tmp);

	cable->setDiameter(suxingqu->GetCableDiameter());
	cable->setLength(suxingqu->GetCableLength() * tmp);
	cable->setNumber(suxingqu->GetCableNumber());
	cable->setPitch(suxingqu->GetCablePitch() * tmp);
	cable->setSpace(suxingqu->GetCableSpace() *tmp);
	cable->setALength(suxingqu->GetCableALength() * tmp);
}


BEGIN_MESSAGE_MAP(CSuxingquDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSuxingquDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CSuxingquDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_TUNNEL_DIALOG, &CSuxingquDialog::OnBnClickedButtonTunnelDialog)
END_MESSAGE_MAP()


// CSuxingquDialog ��Ϣ��������


void CSuxingquDialog::OnBnClickedOk()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	UpdateData(TRUE);

	std::vector<double> mVecValue = {  mInnerFriction,
	 mAvgGravity,
	 mMaiDepth,
	 mMeiyanZhongdu,
	 mNianPower,
	 mShuLength,
	 mBoltAttach,
	 mBoltDesignNumber,
	 mBoltDiameter,
	 mCableDiameter,
	 mCableFreeLength,
	 mCableAttach,
	 mCableBreakPower
	};

	if (DataChecker::HasZeroOrNegativeValue(mVecValue) == true) {
		MessageBox(_T("�����������0"), _T("����"), MB_ICONWARNING);
		pmLeagal = false;
	}
	else {
		CSuxingquFactory * factory = new CSuxingquFactory();
		CMethod * method = factory->createMethod();

		// ��̬ת��
		CSuxingquMethod* tmpMethod = static_cast<CSuxingquMethod *>(method);
		CArcProjectBuilder::GetInstance()->SetMethod(tmpMethod);

		CSuxingquMethod * zuheliang = CArcProjectBuilder::GetInstance()->GetSuxingquMethod();
		CArcTunnel * pArc = CArcProjectBuilder::GetInstance()->GetArcTunnel();

		if (CArcProjectBuilder::GetInstance()->GetTunnelProejct()->GetTunnelType() == 3) {
			zuheliang->SetA(pArc->GetTrapBottomWidth()/1000);
		}
		else
		{
			zuheliang->SetA(pArc->GetWidth()/1000);
		}
		zuheliang->SetH(pArc->GetHeight() / 1000);
		zuheliang->SetInnerFriction(mInnerFriction);
		zuheliang->SetAvgGravity(mAvgGravity);
		zuheliang->SetMaiDepth(mMaiDepth);
		zuheliang->SetMeiyanZhongdu(mMeiyanZhongdu);
		zuheliang->SetNianPower(mNianPower);
		zuheliang->SetShuLength(mShuLength);
		zuheliang->SetBoltAttach(mBoltAttach);
		zuheliang->SetBoltDesignNumber(mBoltDesignNumber);
		zuheliang->SetBoltDiameter(mBoltDiameter);
		zuheliang->SetCableDiameter(mCableDiameter);
		zuheliang->SetCableFreeLength(mCableFreeLength);
		zuheliang->SetCableAttach(mCableAttach);
		zuheliang->SetCableBreakPower(mCableBreakPower);

		CArcProjectBuilder::GetInstance()->GetMethod()->SetConcreteThickness(mConcreteThickness);
		CArcProjectBuilder::GetInstance()->GetMethod()->SetQiThickness(mQiThickness);
		CArcProjectBuilder::GetInstance()->SetCalMethodSaveToInstance(TRUE);

		SetExpertValue();
		CheckThickness();
		pmLeagal = true;
	}

	if (pmLeagal) {
		DialogManager::GetInstance().setHasCalculated(true);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetHasLeftBolt(true);
		CArcProjectBuilder::GetInstance()->GetArcTunnel()->SetHasCable(true);

		DialogManager::GetInstance().ShowResultDlg();
		ShowWindow(SW_HIDE);
	}
}


void CSuxingquDialog::OnBnClickedCancel()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowMethodChooseDlg();
}


void CSuxingquDialog::OnBnClickedButtonTunnelDialog()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	ShowWindow(SW_HIDE);
	DialogManager::GetInstance().ShowMethodChooseDlg();
}


BOOL CSuxingquDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	CRect dlg;
	GetWindowRect(dlg);
	ScreenToClient(dlg);
	SetWindowPos(0, (GetSystemMetrics(SM_CXSCREEN) / 2) - (dlg.Width() / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - (dlg.Height() / 2), dlg.Width(), dlg.Height(),
		SW_SHOW);

	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_FOLDER));
	SetIcon(hIcon, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}