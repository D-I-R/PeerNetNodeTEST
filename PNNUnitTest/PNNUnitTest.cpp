// PNNUnitTest.cpp                                         (c) DIR, 2020
//
//              Îáúÿâëåíèå è ðåàëèçàöèÿ êëàññà
// PNNUnitTest - Ìîäóëüíîå òåñòèðîâàíèå
//
////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "CppUnitTest.h"
#include "..\PeerNetNode\FileBase.h"
#include "..\PeerNetNode\PeerNetNode.h"
#include "..\PeerNetNode\BlkChain.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
/*
// USAGE EXAMPLE

#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

BEGIN_TEST_MODULE_ATTRIBUTE()
	TEST_MODULE_ATTRIBUTE(L"Date", L"2010/6/12")
END_TEST_MODULE_ATTRIBUTE()

TEST_MODULE_INITIALIZE(ModuleInitialize)
{
	Logger::WriteMessage("In Module Initialize");
}

TEST_MODULE_CLEANUP(ModuleCleanup)
{
	Logger::WriteMessage("In Module Cleanup");
}

TEST_CLASS(Class1)
{

public:

	Class1()
	{
		Logger::WriteMessage("In Class1");
	}

	~Class1()
	{
		Logger::WriteMessage("In ~Class1");
	}

	TEST_CLASS_INITIALIZE(ClassInitialize)
	{
		Logger::WriteMessage("In Class Initialize");
	}

	TEST_CLASS_CLEANUP(ClassCleanup)
	{
		Logger::WriteMessage("In Class Cleanup");
	}

	BEGIN_TEST_METHOD_ATTRIBUTE(Method1)
		TEST_OWNER(L"OwnerName")
		TEST_PRIORITY(1)
	END_TEST_METHOD_ATTRIBUTE()

	TEST_METHOD(Method1)
	{
		Logger::WriteMessage("In Method1");
		Assert::AreEqual(0, 0);
	}

	TEST_METHOD(Method2)
	{
		Assert::Fail(L"Fail");
	}
};*/
namespace PNNUnitTest
{
  TEST_CLASS(PNNUnitTest)
  {
  public:
    PNNUnitTest()
    {
      Logger::WriteMessage("In PNNUnitTest()");
    }
    ~PNNUnitTest()
    {
      Logger::WriteMessage("In ~PNNUnitTest()");
    }
    // Òåñòèðîâàíèå ìåòîäà CPeerNetNode::ParseMessage().
    // Ïðèíöèï òåñòèðîâàíèÿ: ñèíòàêñè÷åñêèé ðàçáîð çàðàíåå çàãîòîâëåííûõ 
    //ñîîáùåíèé è ñðàâíåíèå ðåçóëüòàòîâ ñ îæèäàåìûìè çíà÷åíèÿìè
    TEST_METHOD(ParseMessageTest)
    {
      //ECommandCode  CPeerNetNode::ParseMessage(TMessageBuf &mbMess,
      //                                         WORD &iNodeFrom, WORD &iNodeTo)
      //mbMess[in] - ñîîáùåíèå
      //  TCHAR  _chMess[CHARBUFSIZE];  //áóôåð ñîîáùåíèÿ (TCHAR=wchar_t)
      //  WORD   _wMessBytes;   //îáùàÿ äëèíà ñîîáùåíèÿ â áàéòàõ (âìåñòå ñ '\0')
      static TMessageBuf  mbCmnds[] = { //ìàññèâ òåñòîâûõ ñîîáùåíèé
        TMessageBuf(_T("AAA 0102")),
        TMessageBuf(_T("ACK 0203")),
        TMessageBuf(_T("DTB 0304")),
        TMessageBuf(_T("SCL 040500")),
        TMessageBuf(_T("TRM 0506")),
      };
      static int n = sizeof(mbCmnds) / sizeof(TMessageBuf);
	  TCHAR chMess[CHARBUFSIZE];
      WORD iNodeFrom,   //iNodeFrom - èíäåêñ èñõîäÿùåãî óçëà ñåòè
           iNodeTo;     //iNodeTo   - èíäåêñ âõîäÿùåãî óçëà ñåòè
	  Logger::WriteMessage("CPeerNetNode::ParseMessageTest() -- in");
	  for (int i = 0; i < n; i++) {
        swprintf_s(chMess, CHARBUFSIZE,
                   _T(" - pass %d: %s"), i + 1, mbCmnds[i].Message());
	    Logger::WriteMessage(chMess);
        Assert::AreEqual((int)CPeerNetNode::ParseMessage(mbCmnds[i],
                         iNodeFrom, iNodeTo), i);
        if (i > 0) {
		  Assert::AreEqual((int)iNodeFrom, i + 1);
		  Assert::AreEqual((int)iNodeTo, i + 2);
        }
	    Logger::WriteMessage("OK");
      }
	  Logger::WriteMessage("CPeerNetNode::ParseMessageTest() -- out");
	} // TEST_METHOD(ParseMessageTest)

/*		TEST_METHOD(TestMethod1)
		{
		} */
  };
}
