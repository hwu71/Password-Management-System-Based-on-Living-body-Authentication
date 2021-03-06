// ZFKDirectExe.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <tchar.h>
#include <iostream>
#include <Windows.h>
#include "zkfvapi.h"
#include "zkfvapierrdef.h"
#include "zkfvapitype.h"

#ifndef _WIN64
#pragma comment(lib, "libzkfv/x86lib/zkfvapi.lib")
#else
#pragma comment(lib, "libzkfv/x64lib/zkfvapi.lib")
#endif

using std::cout;
using std::cin;
using std::cin;
using std::endl;

HANDLE m_hDevice;

int m_imgFPWidth;
int m_imgFPHeight;
int m_imgFVWidth;
int m_imgFVHeight;
bool m_bStopThread;

HBITMAP BuildImage(BYTE *image, int width, int height)
{
	HBITMAP pic = NULL;
	try
	{
		HDC hDC;
		hDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
		BYTE info[256 * 4 + 40], *colors;
		BITMAPINFOHEADER *header = (BITMAPINFOHEADER*)info;

		header->biSize = 40;
		header->biHeight = height;
		header->biWidth = width;
		header->biPlanes = 1;
		header->biCompression = 0;
		header->biSizeImage = width * height;
		header->biXPelsPerMeter = 0;
		header->biYPelsPerMeter = 0;
		header->biClrImportant = 0;
		header->biBitCount = 8;
		header->biClrUsed = 256;

		colors = info + 40;
		for (int i = 0; i < 256; i++)
		{
			*colors++ = i;
			*colors++ = i;
			*colors++ = i;
			*colors++ = 0;
		}

		if (pic)
			DeleteObject(pic);

		void *ptr;
		//	CClientDC dc(NULL);
		pic = CreateDIBSection(hDC, (BITMAPINFO*)info, DIB_RGB_COLORS, &ptr, NULL, 0);

		for (int i = 0; i < height; i++)
		{
			memcpy((char *)ptr + i * width, image + (height - i - 1)*width, width);
		}
	}
	catch (...)
	{
		pic = NULL;
	}
	return pic;
}
BOOL SaveHBITMAPToFile(HBITMAP hBitmap, LPCTSTR lpszFileName)
{
	HDC hDC;
	int iBits;
	WORD wBitCount;
	DWORD dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
	BITMAP Bitmap0;
	BITMAPFILEHEADER bmfHdr;
	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpbi;
	HANDLE fh, hDib, hPal, hOldPal2 = NULL;
	hDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else
		wBitCount = 24;
	GetObject(hBitmap, sizeof(Bitmap0), (LPSTR)&Bitmap0);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap0.bmWidth;
	bi.biHeight = -Bitmap0.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrImportant = 0;
	bi.biClrUsed = 256;
	dwBmBitsSize = ((Bitmap0.bmWidth * wBitCount + 31) & ~31) / 8
		* Bitmap0.bmHeight;
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = GetDC(NULL);
		hOldPal2 = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}


	GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap0.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)
		+ dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);

	if (hOldPal2)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal2, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
	}

	fh = CreateFile(lpszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (fh == INVALID_HANDLE_VALUE)
		return FALSE;

	bmfHdr.bfType = 0x4D42; // "BM"
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);
	return TRUE;
}

int capture_images(LPCTSTR FPname, LPCTSTR FVname) {
	unsigned char* pBufFPImage = new unsigned char[m_imgFPWidth*m_imgFPHeight];
	int nFPImageSize = 0;
	unsigned char* pBufFVImage = new unsigned char[m_imgFVWidth*m_imgFVHeight];
	int nFVImageSize = 0;
	int ret, ans=0;
	cout << "Begin Capturing" << endl;
	while (!m_bStopThread) {
		nFPImageSize = m_imgFPWidth * m_imgFPHeight;
		nFVImageSize = m_imgFVWidth * m_imgFVHeight;
		cout << "Capturing FingerVein && FingerPrint" << endl;
		if (ret = ZKFingerVein_CaptureFingerVeinImage(m_hDevice, pBufFPImage,
			&nFPImageSize, pBufFVImage, &nFVImageSize) != 0) {
			cout << "Image capture Error: " << ret << endl;
			return 0;
		}
		else {
			cout << "Success Capturing FingerVein && FingerPrint" << endl;
			if (nFPImageSize > 0) {
				HBITMAP FPimage = BuildImage(pBufFPImage, m_imgFPHeight, m_imgFPHeight);
				if (!SaveHBITMAPToFile(FPimage, FPname)) {
					cout << "Error in saving HBITMAP" << endl;
					return 0;
				}
				cout << "Success Write FingerVein" << endl;
				ans = 1;
			}
			if (nFVImageSize > 0) {
				HBITMAP FVimage = BuildImage(pBufFVImage, m_imgFVHeight, m_imgFVHeight);
				if (!SaveHBITMAPToFile(FVimage, FVname)) {
					cout << "Error in saving HBITMAP" << endl;
					return 0;
				}
				cout << "Success Write FingerPrint" << endl;
				ans += 1;
			}
		}
		if(ans == 2) m_bStopThread = true;
	}
	cout << "Capturing out" << endl;
	return 1;
}

int init_device() {
	if (NULL == m_hDevice) {
		if (ZKFingerVein_Init() != ZKFV_ERR_OK) {
			cout << "Init ZKFVM fail" << endl;
			return 0;
		}
		if ((m_hDevice = ZKFingerVein_OpenDevice(0)) == NULL) {
			cout << "Open sensor fail" << endl;
			ZKFingerVein_Terminate();
			return 0;
		}
	}
	int nFullWidth = 0;
	int nFullHeight = 0;
	int retSize = sizeof(int);
	ZKFingerVein_GetParameter(m_hDevice, 1, (unsigned char*)&nFullWidth, &retSize);
	retSize = sizeof(int);
	ZKFingerVein_GetParameter(m_hDevice, 2, (unsigned char*)&nFullHeight, &retSize);
	m_imgFPWidth = nFullWidth & 0xFFFF;
	m_imgFPHeight = nFullHeight & 0xFFFF;
	m_imgFVWidth = (nFullWidth >> 16) & 0xFFFF;
	m_imgFVHeight = (nFullHeight >> 16) & 0xFFFF;
	//__version__
	char cVerion[10] = { 0x0 };
	int leng = 10;
	if (ZKFingerVein_GetSDKVersion(cVerion, &leng) == ZKFV_ERR_OK) {
		cout << "Init Succ，Version is " << cVerion << endl;
	}
	//capture_images();
	return 1;
}

int main(int argc, char *argv[]) {
	/*
	if (argc != 3) {
		cout << "Usage: DirectExe [Finger print image name] [Finger vein image name]" << endl;
	}
	LPCTSTR FPname = (LPCTSTR)argv[1];
	cout << "FPname:" << FPname;
	LPCTSTR FVname = (LPCTSTR)argv[2];
	cout << "FVname:" << FVname;
	*/
	LPCTSTR FPname;
	LPCTSTR FVname;
	char a[64], b[64];
	cin >> a;
	cin >> b;
	FPname = (LPCTSTR)a;
	FVname = (LPCTSTR)b;
	cout << "FPname:" << FPname;
	cout << "FVname:" << FVname;
	cout << "Init device ... " << endl;
	init_device();
	if (!capture_images(FPname, FVname)) cout << "Error in capture images" << endl;
	return 0;
}
