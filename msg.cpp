#include <string>
#include <iostream>
#include <QDebug>
#include <QMessageBox>
#include <Poco/ByteOrder.h>

#include "msg.h"
#include "message.h"
#include "lockid.h"

using namespace std;
using namespace Poco;

namespace {
typedef char BYTE;

int EqualValue[26] = {10,12,13,14,15,16,17,18,19,20,21,23,24,25,26,27,28,29,30,31,32,34,35,36,37,38};
int CheckCode[11]  = {0,1,2,3,4,5,6,7,8,9,0};
char HexToAsni[16] = {0,1,2,3,4,5,6,7,8,9,'A','B','C','D','E','F'};

void StrToBCD(char src[], BYTE dest[], int len)
{
  for(int i = 0; i < len; i++)
  {
    dest[i] = ((src[2*i] - '0') << 4) + src[2*i+1] - '0';
  }
}

void BCDToStr(BYTE src[], char dest[], int len)
{
  for(int i = 0; i < len; i++)
  {
    //dest[i] = ((src[2*i] - '0') << 4) + src[2*i+1] - '0';
    dest[2*i] = (src[i] >> 4) + '0';
    dest[2*i + 1] = (src[i] & 0x0F) + '0';
  }
}

unsigned char XOR_BCDCrcCheck(unsigned char *xor_data, unsigned char xor_length)
{
  unsigned char i = 0x00;
  unsigned char result_crc = 0x00;
  unsigned char crc_data_temp;

  crc_data_temp = (*(xor_data+i));
  i++;
  result_crc = crc_data_temp ^ (*(xor_data+i));
  i++;

  for(; i<xor_length; i++)
  {
    result_crc = result_crc ^ (*(xor_data+i));
  }
  return  result_crc;
}

void Crc16_Ccitt( unsigned char *ucbuf,  unsigned char iLen,  unsigned char *resut_arry)
{
    unsigned int crc = 0xFFFF;          // initial value
    unsigned int polynomial = 0x1021;   // 0001 0000 0010 0001  (0, 5, 12)

    for (int j = 0; j < iLen; ++j) {
        for (int i = 0; i < 8; i++) {
            char bit = ((ucbuf[j]   >> (7-i) & 1) == 1);
            char c15 = ((crc >> 15    & 1) == 1);
            crc <<= 1;
            if (c15 ^ bit) crc ^= polynomial;
        }
    }

    crc &= 0xffff;

    resut_arry[0]= ( unsigned char)(crc>>8);
    resut_arry[1]= ( unsigned char)(crc & 0x00ff);
}

bool CheckVerifyCode(unsigned char * buf, unsigned int buflen)
{
  if(buf == NULL || buflen < 8)
    return false;

  int i=0;
  int n = 0;
  std::vector<int> vec;
  for(i=0; i<4; i++)
  {
    n = buf[i] - 'A';
    if(n < 0 || n >= 26)
    {
      return false;
    }
    vec.push_back(EqualValue[n]);
  }

  unsigned int num = 0;
  for(i=4; i<8;i++)
  {
    n = buf[i] & 0xF0;
    n = n >> 4;
    n = HexToAsni[n];
    if((n - 'A') >= 0 && (n - 'A') < 26)
    {
      vec.push_back(EqualValue[n - 'A']);
    }else if(n >= 0 && n <= 9)
    {
      vec.push_back(n);
    }else
    {
      return false;
    }
    num++;
    if(num == 7)
      break;
    n = buf[i] & 0x0F;
    n = HexToAsni[n];
    if((n - 'A') >= 0 && (n - 'A') < 26)
    {
      vec.push_back(EqualValue[n - 'A']);
    }else if(n >= 0 && n <= 9)
    {
      vec.push_back(n);
    }else
    {
      return false;
    }
    num++;
    if(num == 7)
      break;
  }

  num = 0;
  for(i=0; i<vec.size(); i++)
  {
    num += vec[i] * ((unsigned int)pow((double)2,i));
  }
  n = num % 11;

  if(CheckCode[n] == (buf[7] & 0x0F))
    return true;
  return false;
}

int GetELockId(const std::string &lockid, unsigned char * outbuf, unsigned int buflen)
{
  if(lockid.length() != 14 || buflen != 8)
    return 0;

  int id = QString(lockid.c_str() + 4).toInt();
  id = ByteOrder::toNetwork(id);
  memcpy(outbuf, lockid.c_str(), 4);
  memcpy(outbuf + 4, &id, 4);

  if(CheckVerifyCode(outbuf, buflen))
  {
    return 8;
  }else
  {
    return 0;
  }
}

bool GetELockIdFromBuf(unsigned char * buf, unsigned int buflen, std::string &lockid)
{
  lockid = "";
  if(buf == NULL || buflen < 8)
    return false;

  if(CheckVerifyCode(buf, 8))
  {
    unsigned char tmpbuf[100] = {0};
    memcpy(tmpbuf, buf, 4);
    lockid = (char *)tmpbuf;
    memset(tmpbuf, 0, sizeof(tmpbuf));
    int id = 0;
    memcpy(&id, buf+4, 4);
    id = ByteOrder::fromNetwork(id);
    _snprintf((char *)tmpbuf, sizeof(tmpbuf) - 1,"%010d",id);
    lockid += (char *)tmpbuf;
    return true;
  }

  return false;
}

bool CheckCrc(unsigned char * buf, int buflen)
{
  if(buf == NULL || buflen < 3)
    return false;

  unsigned char res[2] = {0};
  Crc16_Ccitt(buf,buflen - 2, res);
  if((res[0] == buf[buflen -2]) && (res[1] == buf[buflen - 1]))
    return true;

  return false;
}

} //  namespace


void parse_seal(char* buf, int len, Seal_p* seal_p)
{
  seal_p->result = buf[0];
  seal_p->voltage = buf[1];
  seal_p->success_flag = buf[2];
  memcpy((void*)seal_p->timestamp, &buf[3], 8);
  memcpy((void*)seal_p->counter, &buf[11], 4);
}

void parse_unseal(char* buf, int len, Unseal_p* unseal_p)
{
  unseal_p->result = buf[0];
  unseal_p->voltage = buf[1];
  unseal_p->success_flag = buf[2];
  memcpy((void*)unseal_p->timestamp, &buf[3], 8);
  unseal_p->alarm_counter = buf[11];
  memcpy((void*)unseal_p->alarm_timestamp, &buf[12], 4);
  memcpy(unseal_p->counter, &buf[16], 4);
}

void parse_check_seal(char* buf, int len, Check_p* check_p)
{
  check_p->status = buf[0];
  check_p->voltage = buf[1];
  check_p->success_flag = buf[2];
  memcpy((void*)check_p->timestamp, &buf[3], 8);
  check_p->alarm_counter = buf[11];
  memcpy((void*)check_p->alarm_timestamp, &buf[12], 4);
  memcpy(check_p->counter, &buf[16], 4);

}

int parse(char* buf, int32_t len, Message* msg)
{
  if (!CheckCrc((unsigned char*)buf, len)) {
    cout << "check crc failed";
    return -1;
  }

  msg->protocol_id = buf[1];
  memcpy(msg->lock_id, &buf[2], 8);
  msg->cmd_id = buf[10];
  cout << "cmd_id: " << msg->cmd_id << endl;

  char *body = &buf[12];
  len = buf[11];

  cout << "body: " << *body <<  " len: " << len << endl;
  // body
  switch (msg->cmd_id) {
    case ELOCK_SEALING_RES:
      parse_seal(body, len, &msg->body.seal_p);
      break;
    case ELOCK_UNSEALING_RES:
      parse_unseal(body, len, &msg->body.unseal_p);
      break;
    case ELOCK_CHECK_SEALING_RES:
      parse_check_seal(body, len, &msg->body.check_p);
      break;
  };

  return 0;
}

std::string serial(const Message& msg)
{
#if 1
  LockId lock_id;
  QString lockid = lock_id.calculate(QString(QChar(msg.lock_id[0])) + QString(QChar(msg.lock_id[1])),
                                     QString(QChar(msg.lock_id[2])) + QString(QChar(msg.lock_id[3])),
                                     QString(QChar(msg.lock_id[4])) + QString(QChar(msg.lock_id[5])) + QString(QChar(msg.lock_id[6])),
                                     QString(QChar(msg.lock_id[7])));
  return lockid.toStdString();
#endif
  return "===========";
}
