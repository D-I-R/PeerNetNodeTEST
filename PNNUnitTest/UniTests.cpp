// UniTests.cpp                                            (c) DIR, 2020
//
//              Объявление и реализация класса
// CPNNUniTests - Модульное тестирование
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
    // Тестирование метода CPeerNetNode::ParseMessage().
    // Принцип тестирования: синтаксический разбор заранее заготовленных 
    //сообщений и сравнение результатов с ожидаемыми значениями
    TEST_METHOD(ParseMessageTest)
    {
//ECommandCode  CPeerNetNode::ParseMessage(TMessageBuf &mbMess,
//                                         WORD &iNodeFrom, WORD &iNodeTo)
//mbMess[in] - сообщение
//  TCHAR  _chMess[CHARBUFSIZE];  //буфер сообщения (TCHAR=wchar_t)
//  WORD   _wMessBytes;   //общая длина сообщения в байтах (вместе с '\0')
      static TMessageBuf  mbCmnds[] = { //массив тестовых сообщений
        { _T("AAA 0102"),   18 },   //несуществующая подкоманда
        { _T("ACK 0203"),   18 },
        { _T("DTB 0304"),   18 },
        { _T("SCL 040500"), 22 },
        { _T("TRM 0506"),   18 },
      };
      static int n = sizeof(mbCmnds)/sizeof(TMessageBuf);
      WORD iNodeFrom,   //iNodeFrom - индекс исходящего узла сети
           iNodeTo;     //iNodeTo   - индекс входящего узла сети
      for (int i = 0; i < n; i++) {
        Assert::AreEqual(CPeerNetNode::ParseMessage(mbCmnds[i],
                         iNodeFrom, iNodeTo), (ECommandCode)i);
        ASSERT(iNodeFrom == (WORD)(i+1));
        ASSERT(iNodeTo == (WORD)(i+2));
      }
    } // TEST_METHOD(ParseMessageTest)

    // Тестирование метода CPeerNetNode::WrapData() - упаковать сообщение.
    // Принцип тестирования: упаковка нескольких заранее заготовленных 
    //сообщений и сравнение результатов с ожидаемыми значениями.
    TEST_METHOD(WrapDataTest)
	{
//void  WrapData(WORD iNodeTo, TMessageBuf &mbRequest);
    } // TEST_METHOD(WrapDataTest)

    // Тестирование метода CPeerNetNode::UnwrapData() - распаковать сообщение.
    // Принцип тестирования: распаковка нескольких заранее заготовленных 
    //сообщений и сравнение результатов с ожидаемыми значениями.
    TEST_METHOD(UnwrapDataTest)
	{
//void  UnwrapData(WORD &iNodeFrom, TMessageBuf *pmbReply);
    } // TEST_METHOD(UnwrapDataTest)

    // Тестирование методов:
    // CTransRegister::HashToSymbols() - преобразование двоичного представ-
    //ления хеш-кода в символьное представление,
    // CTransRegister::SymbolsToHash() - преобразование символьного представ-
    //ления хеш-кода в двоичное представление.
    // Принцип тестирования: генерирование хеш-кода в виде случайной последо-
    //вательности байтов, преобразование в символьное представление, обратное 
    //преобразование и сравнение с исходным значением.
    TEST_METHOD(HashTransformTest)
	{
// Преобразовать хеш-код в символьное представление
//static void  CTransRegister::HashToSymbols(char *pcBuff, BYTE btHash[]);
// Преобразовать символьное представление в хеш-код
//static void  CTransRegister::SymbolsToHash(char *pcBuff, BYTE btHash[]);
    } // TEST_METHOD(HashTransformTest)

    // Тестирование методов CBlockChain::ParseMessage() - разобрать подком.
    //Попутно тестируется метод CPeerNetNode::ToNumber()
    //Метод возвращает код подкоманды и описатель - результат разбора.
    //Принцип тестирования: синтаксический разбор заранее заготовленных 
    //подкоманд и сравнение результатов с ожидаемыми значениями
    TEST_METHOD(ParseSubcmdTest)
	{
//ESubcmdCode  CBlockChain::ParseMessage(TMessageBuf &mbMess, TSubcmd &tCmd)
//mbMess[in] - сообщение
//  TCHAR  _chMess[CHARBUFSIZE];  //буфер сообщения (TCHAR=wchar_t)
//  WORD   _wMessBytes;   //общая длина сообщения в байтах (вместе с '\0')
//tCmd[out]  - результат разбора, описатель сообщения
//  ESubcmdCode  _eCode;              //код подкоманды
//  TCHAR  _szNode[SHORTNUMSIZ+1];    //номер узла (2)
//  TCHAR  _szBlock[SHORTNUMSIZ+1];   //номер или количество блоков (2)
//  TCHAR  _szTrans[LONGNUMSIZE+1];   //номер транзакции (8)
//  BYTE   _chHashFrom[_HASHSIZE];    //хеш-код рег имени польз-отправителя
//  BYTE   _chHashTo[_HASHSIZE];      //хеш-код рег имени польз-получателя
//  TCHAR  _szAmount[NAMESBUFSIZ];    //+1 сумма транзакции (или текущ остатка)
//  BYTE   _chHashPrev[2*HASHSIZE+2]; //хеш-код предыдущего блока в симв предст
      static TMessageBuf  mbCmnds[] = { //массив тестовых сообщений
        { _T("AAA 0001"), 18 }, //несуществующая подкоманда
        { _T("ATR 0102"), 18 },
        { _T("GTB 02"),   14 },
        { _T("TAQ 000000030304000000000100.00"), 64 },
        { _T("TAR 000000040405000000000100.00"), 64 },
        { _T("TBL 000000050506000000000100.00"), 64 },
        { _T("TRA 000000060607000000000100.00"), 64 },
      };
      static int n = sizeof(mbCmnds)/sizeof(TMessageBuf);
      TSubcmd tCmd;     //описатель сообщения
      WORD iUserFrom,   //iUserFrom - индекс пользователя-отправителя
           iUserTo,     //iUserTo   - индекс пользователя-получателя
           nTrans, iNode, nBlck;
      for (int i = 0; i < n; i++) {
        // Проверка результата вызова метода
        Assert::AreEqual(CBlockChain::ParseMessage(mbCmnds[i], tCmd),
                         (ESubcmdCode)((i == 0) ? 0 : i+10));
        if (i > 0) {
          // Проверки результата разбора
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
