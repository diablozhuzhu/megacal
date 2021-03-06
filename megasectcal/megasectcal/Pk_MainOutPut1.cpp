#include "StdAfx.h"
#include "Pk_MainOutPut.h"
#include "ParagraphMacroHeader.h"
 

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
 

using namespace sd;
 
const CString TextTool::Eng = "ENGLISH";
 

bool TextTool::readJson()
{
	TCHAR szFilePath[MAX_PATH+1];
	GetModuleFileName(NULL,szFilePath,MAX_PATH);
	(_tcsrchr(szFilePath,_T('\\')))[1]=0;
	CString strPa;
	strPa.Format("%sReportDoc.json",szFilePath);
	std::ifstream is;
	is.open(strPa.GetBuffer());
	strPa.ReleaseBuffer();
	if(is.is_open())
	{
	 
	}
	else
	{
		//ASSERT(FALSE);
		CString str;
		str.Format("未找到多语言文件!\n文件:%s",strPa);
		AfxMessageBox(str);
		return false;
	}

	Json::Reader reader;
	Json::Value jsRoot;

	if (true == reader.parse(is,jsRoot))
	{
		jsDocs = jsRoot["DOC"];
		return true;
	}

	return false;
	
}

TextTool::TextTool()
{

}

TextTool::~TextTool()
{

}
void TextTool::Set( sd::IGenerateText* pT1,sd::PARAGRAPH_FORMAT* pF1 )
{
	SetGenerateText(pT1);
	SetPARAGRAPH_FORMAT(pF1);
}

void TextTool::SetGenerateText( sd::IGenerateText* pT1 )
{
	pT = pT1;
}
void TextTool::SetTEXT_FORMAT( TEXT_FORMAT tf1 )
{
	this->tf = tf1;

	tfup = tf;
	tfup.subscript = sdSuperscript;

	tfsub = tf;
	tfsub.subscript = sdSubscript;
// 
// 	tfUpSub = tf;
// 	tfUpSub.subscript = sdSuperscript|sdSubscript;
}



void TextTool::SetPARAGRAPH_FORMAT( sd::PARAGRAPH_FORMAT* pF1 )
{
	pF = pF1;
}

void TextTool::BeginP()
{
	pT->beginParagraph(pF);
}

void TextTool::EndP()
{
	pT->endParagraph();
}
void TextTool::Txt(CString str1)
{
	pT->appendText(str1,&tf);
}
void TextTool::TxSub(CString str1)
{
	pT->appendText(str1,&tfsub);
}

void TextTool::TxSub(CString str1,CString up,CString sign)
{
	pT->appendText(str1,&tf);
	pT->appendText(up,&tfsub);
	if (false == sign.IsEmpty())
	{
		pT->appendText(sign,&tf);
	}
}
void TextTool::TxUp(CString str1)
{
	pT->appendText(str1,&tfup);
}
void TextTool::TxUp(CString str1,CString sub,CString sign)
{
	pT->appendText(str1,&tf);
	pT->appendText(sub,&tfup);
	if (false == sign.IsEmpty())
	{
		pT->appendText(sign,&tf);
	}
}
void TextTool::TxUpSub(CString str1,CString up,CString sub,CString sign)
{
	TxSub(str1,sub);
	TxUp(up);
}
CString TextTool::format( double ff,int nPre )
{
	CString oneStr;
	CString oneFormat;
	if (nPre==0)
	{
		oneStr.Format("%d",int(ff+0.0001));
		return oneStr ;
	}
	else 
	{
		oneFormat.Format("%%0.%df",nPre);
		oneStr.Format(oneFormat,ff);
		return oneStr ;
	}
}
void TextTool::TxV(double f,int nPre )
{
	Txt(format(f,nPre));
}
void TextTool::TxV(int n)
{
	CString oneStr;
	oneStr.Format("%d",n);
	Txt(oneStr);	 
}

void TextTool::Txt(int nC,int nAt)
{
	jsLang = jsDocs[Eng];
	CString strC ;
	CString strAt;
	strC.Format("C%04d",nC);
	strAt.Format("@%04d",nAt);

	jsC = jsLang[strC];
	jsAt = jsC[strAt];
 	if (jsAt.isString())
 	{
		CString str = jsAt.asCString();
		Txt(str);
	}
	
}
void TextTool::m()
{
	Txt("m");
}
void TextTool::m(double ff,int nPre )
{
	Txt(format(ff,nPre));m();
}
void TextTool::m(double ff,int nPre ,int _n10n)
{
	double chu = pow(10.0,_n10n);
	double ff1 = ff/chu;

	CString str10;
	str10.Format("%d",_n10n);
	Txt(format(ff1,nPre));
	Txt("×10");
	TxUp(str10);m();
}
 


void TextTool::mm()
{
	Txt("mm");
}
void TextTool::mm(double ff,int nPre)
{
	Txt(format(ff,nPre));
	Txt("mm");
}

void TextTool::mm3()
{
	Txt("mm");
	TxUp("3");
}
void TextTool::mm3( double ff,int nPre )
{
	

	Txt(format(ff,nPre));
	mm3();
}
void TextTool::mm3(double ff,int nPre ,int _n10n)
{
	double chu = pow(10.0,_n10n);
	double ff1 = ff/chu;

	CString str10;
	str10.Format("%d",_n10n);
	Txt(format(ff1,nPre));
	Txt("×10");
	TxUp(str10);
	mm3();
}
void TextTool::mm2()
{
	Txt("mm");
	TxUp("2");
}
void TextTool::mm2(double ff,int nPre)
{
	Txt(format(ff,nPre));
	Txt("mm");
	TxUp("2");
}
void TextTool::mm4()
{
	Txt("mm");
	TxUp("4");
}
void TextTool::mm4(double ff,int nPre,int _n10n)
{
	double chu = pow(10.0,_n10n);
	double ff1 = ff/chu;

	
	Txt(format(ff1,nPre));
	if (_n10n>=1)
	{
		Txt("×10");
		CString str10;
		str10.Format("%d",_n10n);
		TxUp(str10);
	}
	Txt("mm");
	TxUp("4");

}
void TextTool::m$s2()
{
	Txt("m/s");
	TxUp("2");
}
void TextTool::m$s2(double ff,int nPre)
{
	Txt(format(ff,nPre));
	Txt("m/s");
	TxUp("2");
}
void TextTool::kg$m()
{
	Txt("kg/m");
}
void TextTool::kg$m(double ff,int nPre)
{
	Txt(format(ff,nPre));
	Txt("kg/m");
}
void TextTool::MPa()
{
	Txt("MPa");
}
void TextTool::MPa(double ff,int nPre)
{
	Txt(format(ff,nPre));
	Txt("MPa");
}
void TextTool::C(int CXX)
{
	CString str;
	str.Format("C%d",CXX);
	Txt(str);
}
void TextTool::days(int ndy)
{
	if (ndy>1)
	{
		CString str;
		str.Format("%ddays",ndy);
		Txt(str);
	}
	else  if (ndy==1)
	{
		CString str;
		str.Format("%dday",ndy);
		Txt(str);
	}
	
}
void TextTool::kN()
{
	Txt("kN");
}
void TextTool::kN(double ff,int nPre)
{
	Txt(format(ff,nPre));
	kN();
}

void TextTool::kN(double ff,int nPre /* = 0 */,int _n10n/* =4 */)
{
	double chu = pow(10.0,_n10n);
	double ff1 = ff/chu;

	CString str10;
	str10.Format("%d",_n10n);
	Txt(format(ff1,nPre));
	Txt("×10");
	TxUp(str10);kN();
}

void TextTool::N()
{
	Txt("N");
}
void TextTool::N(double ff,int nPre)
{
	Txt(format(ff,nPre));
	N();
}
void TextTool::kNm()
{
	Txt("kN·m");
}
void TextTool::kNm(double ff,int nPre)
{
	Txt(format(ff,nPre));
	kNm();
}

void TextTool::Nmm2()
{
	Txt("N·");
	TxUp("mm","2");
}
void TextTool::Nmm2(double ff,int nPre)
{
	Txt(format(ff,nPre));
	Nmm2();
}

void TextTool::kNm2()
{
	Txt("kN·");
	TxUp("m","2");
}
void TextTool::kNm2(double ff,int nPre)
{
	Txt(format(ff,nPre));
	kNm2();
}

void TextTool::kNm2(double ff,int nPre /* = 0 */,int _n10n/* =4 */)
{
	double chu = pow(10.0,_n10n);
	double ff1 = ff/chu;

	CString str10;
	str10.Format("%d",_n10n);
	Txt(format(ff1,nPre));
	Txt("×10");
	TxUp(str10);kNm2();
}

void TextTool::N$mm()
{
	Txt("N/mm");
}
void TextTool::N$mm(double ff,int nPre)
{
	Txt(format(ff,nPre));
	N$mm();
}
void TextTool::kN$m()
{
	Txt("kN/m");
}
void TextTool::kN$m(double ff,int nPre)
{
	Txt(format(ff,nPre));
	kN$m();
}
void TextTool::N$m()
{
	Txt("N/m");
}
void TextTool::N$m(double ff,int nPre)
{
	Txt(format(ff,nPre));N$m();
}
void TextTool::studs$1m()
{
	Txt("studs/1m");
}
void TextTool::studs$1m(double ff,int nPre)
{
	Txt(format(ff,nPre));
	studs$1m();
}
void TextTool::SpTab______(int n)
{
	if (n == 1)
	{
		Txt("\t");
	}
	else if (n == 2)
	{
		Txt("\t\t");
	}
	else if (n == 3)
	{
		Txt("\t\t\t");
	}
	else if (n>=4)
	{
		Txt("\t\t\t\t");
	}
	
}



