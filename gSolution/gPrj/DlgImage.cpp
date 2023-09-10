// DlgImage.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "gPrj.h"
#include "DlgImage.h"
#include "afxdialogex.h"


// CDlgImage ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLGIMAGE, pParent)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_UP_PARENT, &CDlgImage::OnBnClickedBtnUpParent)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage �޽��� ó�����Դϴ�.

#include "gPrjDlg.h"
void CDlgImage::OnBnClickedBtnUpParent()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	static int n = 100;
	CgPrjDlg *pDlg = (CgPrjDlg*)m_pParent;
	pDlg->callFunc(n++);
}


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetWindowText(_T("Origin Image"));
	MoveWindow(0, 0, 640, 480);
	InitImage();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CDlgImage::InitImage()
{
	int nWidth = 640;// 4096 * 5;
	int nHeight = 480;// 4096 * 5;
	int nBpp = 8;

	m_image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_image.GetPitch();
	unsigned char* fm = (unsigned char*)m_image.GetBits();

	memset(fm, 0xff, nWidth*nHeight);
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
	if (m_image)
		m_image.Draw(dc, 0, 0);

	drawData(&dc);
	drawDataCircle(&dc);
}

void CDlgImage::drawData(CDC* pDC)
{
	CRect rect;
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, COLOR_RED);
	CPen* pOldPen = pDC->SelectObject(&pen);
	for (int i = 0; i < m_nDataCount; i++) {
		rect.SetRect(m_ptData[i], m_ptData[i]);
		rect.InflateRect(1,1);
		pDC->Ellipse(rect);
	}
	pDC->SelectObject(pOldPen);
}

void CDlgImage::drawDataCircle(CDC* pDC)
{
	if (m_bDrawCircle) {
		int nCrossLineSize = 3;
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, COLOR_YELLOW);
		CPen* pOldPen = pDC->SelectObject(&pen);

		CBrush brush;
		brush.CreateStockObject(NULL_BRUSH);
		CBrush* pOldBrush = pDC->SelectObject(&brush);

		pDC->Ellipse(m_ptDataCircle.x - m_nCircleRadius, m_ptDataCircle.y - m_nCircleRadius, m_ptDataCircle.x + m_nCircleRadius, m_ptDataCircle.y + m_nCircleRadius);

		pDC->SelectObject(pOldPen);
		pDC->SelectObject(pOldBrush);

		DeleteObject(pen);
		DeleteObject(brush);

		//.//
		CPen pen2;
		pen2.CreatePen(PS_SOLID, 1, COLOR_RED);
		pOldPen = pDC->SelectObject(&pen2);

		pDC->MoveTo(m_ptDataCircle.x - nCrossLineSize, m_ptDataCircle.y);
		pDC->LineTo(m_ptDataCircle.x + nCrossLineSize +1, m_ptDataCircle.y);
		pDC->MoveTo(m_ptDataCircle.x, m_ptDataCircle.y - nCrossLineSize);
		pDC->LineTo(m_ptDataCircle.x, m_ptDataCircle.y + nCrossLineSize +1);

		pDC->SelectObject(pOldPen);
		DeleteObject(pen);
		//.//
	}
}