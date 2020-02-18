// UniTests.cpp                                            (c) DIR, 2020
//
//              ���������� � ���������� ������
// CPNNUniTests - ��������� ������������
//
////////////////////////////////////////////////////////////////////////

//C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\VC\Auxiliary\VS\UnitTest\include
#include "CppUnitTest.h" //<include/CppUnitTest.h>
#include "FileBase.h"
#include "PeerNetNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PNNTest
{
  TEST_CLASS(CPNNUniTests)
  {
  public:
    // ������������ ������ CPeerNetNode::ParseMessage().
    // ������� ������������: �������������� ������ ������� ������������� 
    //��������� � ��������� ����������� � ���������� ����������
    TEST_METHOD(ParseMessageTest)
    {
//ECommandCode  CPeerNetNode::ParseMessage(TMessageBuf &mbMess,
//                                         WORD &iNodeFrom, WORD &iNodeTo)
//mbMess[in] - ���������
//  TCHAR  _chMess[CHARBUFSIZE];  //����� ��������� (TCHAR=wchar_t)
//  WORD   _wMessBytes;   //����� ����� ��������� � ������ (������ � '\0')
      static TMessageBuf  mbCmnds[] = { //������ �������� ���������
        { _T("AAA 0102"),   18 },   //�������������� ����������
        { _T("ACK 0203"),   18 },
        { _T("DTB 0304"),   18 },
        { _T("SCL 040500"), 22 },
        { _T("TRM 0506"),   18 },
      };
      static int n = sizeof(mbCmnds)/sizeof(TMessageBuf);
      WORD iNodeFrom,   //iNodeFrom - ������ ���������� ���� ����
           iNodeTo;     //iNodeTo   - ������ ��������� ���� ����
      for (int i = 0; i < n; i++) {
        Assert::AreEqual(CPeerNetNode::ParseMessage(mbCmnds[i],
                         iNodeFrom, iNodeTo), (ECommandCode)i);
        ASSERT(iNodeFrom == (WORD)(i+1));
        ASSERT(iNodeTo == (WORD)(i+2));
      }
    } // TEST_METHOD(ParseMessageTest)

    // ������������ ������ CPeerNetNode::WrapData() - ��������� ���������.
    // ������� ������������: �������� ���������� ������� ������������� 
    //��������� � ��������� ����������� � ���������� ����������.
    TEST_METHOD(WrapDataTest)
	{
//void  WrapData(WORD iNodeTo, TMessageBuf &mbRequest);
    } // TEST_METHOD(WrapDataTest)

    // ������������ ������ CPeerNetNode::UnwrapData() - ����������� ���������.
    // ������� ������������: ���������� ���������� ������� ������������� 
    //��������� � ��������� ����������� � ���������� ����������.
    TEST_METHOD(UnwrapDataTest)
	{
//void  UnwrapData(WORD &iNodeFrom, TMessageBuf *pmbReply);
    } // TEST_METHOD(UnwrapDataTest)

    // ������������ �������:
    // CTransRegister::HashToSymbols() - �������������� ��������� ��������-
    //����� ���-���� � ���������� �������������,
    // CTransRegister::SymbolsToHash() - �������������� ����������� ��������-
    //����� ���-���� � �������� �������������.
    // ������� ������������: ������������� ���-���� � ���� ��������� �������-
    //����������� ������, �������������� � ���������� �������������, �������� 
    //�������������� � ��������� � �������� ���������.
    TEST_METHOD(HashTransformTest)
	{
// ������������� ���-��� � ���������� �������������
//static void  CTransRegister::HashToSymbols(char *pcBuff, BYTE btHash[]);
// ������������� ���������� ������������� � ���-���
//static void  CTransRegister::SymbolsToHash(char *pcBuff, BYTE btHash[]);
    } // TEST_METHOD(HashTransformTest)

    // ������������ ������� CBlockChain::ParseMessage() - ��������� ������.
    //������� ����������� ����� CPeerNetNode::ToNumber()
    //����� ���������� ��� ���������� � ��������� - ��������� �������.
    //������� ������������: �������������� ������ ������� ������������� 
    //��������� � ��������� ����������� � ���������� ����������
    TEST_METHOD(ParseSubcmdTest)
	{
//ESubcmdCode  CBlockChain::ParseMessage(TMessageBuf &mbMess, TSubcmd &tCmd)
//mbMess[in] - ���������
//  TCHAR  _chMess[CHARBUFSIZE];  //����� ��������� (TCHAR=wchar_t)
//  WORD   _wMessBytes;   //����� ����� ��������� � ������ (������ � '\0')
//tCmd[out]  - ��������� �������, ��������� ���������
//  ESubcmdCode  _eCode;              //��� ����������
//  TCHAR  _szNode[SHORTNUMSIZ+1];    //����� ���� (2)
//  TCHAR  _szBlock[SHORTNUMSIZ+1];   //����� ��� ���������� ������ (2)
//  TCHAR  _szTrans[LONGNUMSIZE+1];   //����� ���������� (8)
//  BYTE   _chHashFrom[_HASHSIZE];    //���-��� ��� ����� �����-�����������
//  BYTE   _chHashTo[_HASHSIZE];      //���-��� ��� ����� �����-����������
//  TCHAR  _szAmount[NAMESBUFSIZ];    //+1 ����� ���������� (��� ����� �������)
//  BYTE   _chHashPrev[2*HASHSIZE+2]; //���-��� ����������� ����� � ���� ������
      static TMessageBuf  mbCmnds[] = { //������ �������� ���������
        { _T("AAA 0001"), 18 }, //�������������� ����������
        { _T("ATR 0102"), 18 },
        { _T("GTB 02"),   14 },
        { _T("TAQ 000000030304000000000100.00"), 64 },
        { _T("TAR 000000040405000000000100.00"), 64 },
        { _T("TBL 000000050506000000000100.00"), 64 },
        { _T("TRA 000000060607000000000100.00"), 64 },
      };
      static int n = sizeof(mbCmnds)/sizeof(TMessageBuf);
      TSubcmd tCmd;     //��������� ���������
      WORD iUserFrom,   //iUserFrom - ������ ������������-�����������
           iUserTo,     //iUserTo   - ������ ������������-����������
           nTrans, iNode, nBlck;
      for (int i = 0; i < n; i++) {
        // �������� ���������� ������ ������
        Assert::AreEqual(CBlockChain::ParseMessage(mbCmnds[i], tCmd),
                         (ESubcmdCode)((i == 0) ? 0 : i+10));
        if (i > 0) {
          // �������� ���������� �������
		  if (i == 1) {
            iNode = CPeerNetNode::ToNumber((LPTSTR)tCmd._szNode, 2);
            ASSERT(iNode == 1);
            nBlck = CPeerNetNode::ToNumber((LPTSTR)tCmd._szBlock, 2);
            ASSERT(nBlck == (WORD)(i+1));
          }
		  else if (i == 2) {
            nBlck = CPeerNetNode::ToNumber((LPTSTR)tCmd._szBlock, 2);
            ASSERT(nBlck == (WORD)(i+1));
          }
		  else {
            nTrans = CPeerNetNode::ToNumber((LPTSTR)tCmd._szTrans, 8);
            iUserFrom = CPeerNetNode::ToNumber((LPTSTR)tCmd._chHashFrom, 2);
            iUserTo = CPeerNetNode::ToNumber((LPTSTR)tCmd._chHashTo, 2);
            ASSERT(nTrans == (WORD)i);
            ASSERT(iUserFrom == (WORD)(i+1));
            ASSERT(iUserTo == (WORD)(i+2));
          }
        }
      } //for
	} // TEST_METHOD(ParseSubcmdTest)

  }; // End of TEST_CLASS

} // namespace PNNTest
