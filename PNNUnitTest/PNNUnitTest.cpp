// PNNUnitTest.cpp                                         (c) DIR, 2020
//
//              ќбъ€вление и реализаци€ класса
// PNNUnitTest - ћодульное тестирование
//
////////////////////////////////////////////////////////////////////////

#include "pch.h"
#include "CppUnitTest.h"
#include "FileBase.h"
#include "PeerNetNode.h"
#include "BlkChain.h"

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
    // “естирование метода CPeerNetNode::ParseMessage().
    // ѕринцип тестировани€: синтаксический разбор заранее заготовленных 
    //сообщений и сравнение результатов с ожидаемыми значени€ми
    TEST_METHOD(ParseMessageTest)
    {
      //ECommandCode  CPeerNetNode::ParseMessage(TMessageBuf &mbMess,
      //                                         WORD &iNodeFrom, WORD &iNodeTo)
      //mbMess[in] - сообщение
      //  TCHAR  _chMess[CHARBUFSIZE];  //буфер сообщени€ (TCHAR=wchar_t)
      //  WORD   _wMessBytes;   //обща€ длина сообщени€ в байтах (вместе с '\0')
      static TMessageBuf  mbCmnds[] = { //массив тестовых сообщений
        TMessageBuf(_T("AAA 0102")),
        TMessageBuf(_T("ACK 0203")),
        TMessageBuf(_T("DTB 0304")),
        TMessageBuf(_T("SCL 040500")),
        TMessageBuf(_T("TRM 0506")),
      };
      static int n = sizeof(mbCmnds) / sizeof(TMessageBuf);
	  TCHAR chMess[CHARBUFSIZE];
      WORD iNodeFrom,   //iNodeFrom - индекс исход€щего узла сети
           iNodeTo;     //iNodeTo   - индекс вход€щего узла сети
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
