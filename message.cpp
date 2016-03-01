#include <vector>
#include <math.h>
#include <time.h>

#include <windows.h>

#include <QString>

#include "message.h"
#include "Poco/ByteOrder.h"

using namespace std;
using Poco::ByteOrder;

namespace {
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

} //namespace

/////////////////////////////////////////////////////////////////////////////////
bool CreateSealingReq(const std::string &lockid,
                      const std::string &passwd,
                      unsigned char * outbuf,
                      unsigned int &buflen)
{
  if(lockid.length() != 14 || outbuf == NULL || buflen <32 || passwd.length() > 10)
    return false;

  memset(outbuf, 0, buflen);

  outbuf[0] = 0x7B;
  outbuf[1] = ELOCK_ID_MSG;
  int n = GetELockId(lockid,outbuf + 2, 8);
  if(n != 8)
  {
    return false;
  }

  outbuf[10] = ELOCK_SEALING_REQ;
  outbuf[11] = 0x12;
  memcpy(outbuf + 12, passwd.c_str(), passwd.length());

  char chTime[100]= {0};
  __time64_t time_utc;
  struct tm tm_utc = {0};
  time_utc = _time64(NULL);
  _gmtime64_s(&tm_utc, &time_utc);
  BYTE bTime[7]= {0};
  _snprintf(chTime,
            sizeof(chTime) - 1,
            "%02d%02d%02d%02d%02d%02d%02d",
            (tm_utc.tm_year + 1900)/100,
            (tm_utc.tm_year + 1900)%100,
            tm_utc.tm_mon + 1,
            tm_utc.tm_mday,
            tm_utc.tm_hour,
            tm_utc.tm_min,
            tm_utc.tm_sec);
  StrToBCD(chTime, bTime, 7);

  memcpy(outbuf + 22, bTime, 7);
  outbuf[29] = XOR_BCDCrcCheck(bTime,7);

  Crc16_Ccitt(outbuf, 30, outbuf+30);
  buflen = 32;

  return true;
}

bool CreateUnSealingReq(const std::string &lockid,
                        const std::string &passwd,
                        unsigned char * outbuf,
                        unsigned int &buflen)
{
  if(lockid.length() != 14 || outbuf == NULL || buflen <32 || passwd.length() > 10)
    return false;

  memset(outbuf, 0, buflen);

  outbuf[0] = 0x7B;
  outbuf[1] = ELOCK_ID_MSG;
  int n = GetELockId(lockid,outbuf + 2, 8);
  if(n != 8)
  {
    return false;
  }

  outbuf[10] = ELOCK_UNSEALING_REQ;
  outbuf[11] = 0x12;
  memcpy(outbuf + 12, passwd.c_str(), passwd.length());

  char chTime[100]= {0};
  __time64_t time_utc;
  struct tm tm_utc = {0};
  time_utc = _time64(NULL);
  _gmtime64_s(&tm_utc, &time_utc);

  BYTE bTime[7]= {0};
  _snprintf(chTime,
            sizeof(chTime) - 1,
            "%02d%02d%02d%02d%02d%02d%02d",
            (tm_utc.tm_year + 1900)/100,
            (tm_utc.tm_year + 1900)%100,
            tm_utc.tm_mon + 1,
            tm_utc.tm_mday,
            tm_utc.tm_hour,
            tm_utc.tm_min,
            tm_utc.tm_sec);
  StrToBCD(chTime, bTime, 7);

  memcpy(outbuf + 22, bTime, 7);
  outbuf[29] = XOR_BCDCrcCheck(bTime,7);
  Crc16_Ccitt(outbuf,30,outbuf+30);
  buflen = 32;

  return true;
}

bool CreateCheckSealingReq(const std::string &lockid,
                           const std::string &passwd,
                           unsigned char * outbuf,
                           unsigned int &buflen)
{
  if(lockid.length() != 14 || outbuf == NULL || buflen <32 || passwd.length() > 10)
    return false;

  memset(outbuf, 0, buflen);

  outbuf[0] = 0x7B;
  outbuf[1] = ELOCK_ID_MSG;
  int n = GetELockId(lockid,outbuf + 2, 8);
  if(n != 8)
  {
    return false;
  }
  outbuf[10] = ELOCK_CHECK_SEALING_REQ;
  outbuf[11] = 0x12;
  memcpy(outbuf + 12, passwd.c_str(), passwd.length());

  char chTime[100]= {0};
  __time64_t time_utc;
  struct tm tm_utc = {0};
  time_utc = _time64(NULL);
  _gmtime64_s(&tm_utc, &time_utc);

  BYTE bTime[7]= {0};
  _snprintf(chTime,
            sizeof(chTime) - 1,
            "%02d%02d%02d%02d%02d%02d%02d",
            (tm_utc.tm_year + 1900)/100,
            (tm_utc.tm_year + 1900)%100,
            tm_utc.tm_mon + 1,
            tm_utc.tm_mday,
            tm_utc.tm_hour,
            tm_utc.tm_min,
            tm_utc.tm_sec);
  StrToBCD(chTime, bTime, 7);

  memcpy(outbuf + 22, bTime, 7);
  outbuf[29] = XOR_BCDCrcCheck(bTime,7);

  Crc16_Ccitt(outbuf,30,outbuf+30);
  buflen = 32;

  return true;
}

bool CreateWriteDataReq(const std::string &lockid,
                        const std::string &passwd,
                        unsigned char * data,
                        int datalen,
                        unsigned char * outbuf,
                        unsigned int &buflen)
{
  if (lockid.length() != 14 ||
      outbuf == NULL ||
      buflen <34 ||
      passwd.length() > 10 ||
      data == NULL ||
      datalen > 108) {
    return false;
  }

  memset(outbuf, 0, buflen);

  outbuf[0] = 0x7B;
  outbuf[1] = ELOCK_ID_MSG;
  int n = GetELockId(lockid,outbuf + 2, 8);
  if(n != 8)
  {
    return false;
  }
  outbuf[10] = ELOCK_WRITE_EXTENSION_DATA_REQ;
  outbuf[11] = 20 + datalen;

  memcpy(outbuf + 12, passwd.c_str(), passwd.length());

  char chTime[100]= {0};
  __time64_t time_utc;
  struct tm tm_utc = {0};
  time_utc = _time64(NULL);
  _gmtime64_s(&tm_utc, &time_utc);

  BYTE bTime[7]= {0};
  _snprintf(chTime,
            sizeof(chTime) - 1,
            "%02d%02d%02d%02d%02d%02d%02d",
            (tm_utc.tm_year + 1900)/100,
            (tm_utc.tm_year + 1900)%100,
            tm_utc.tm_mon + 1,
            tm_utc.tm_mday,
            tm_utc.tm_hour,
            tm_utc.tm_min,
            tm_utc.tm_sec);
  StrToBCD(chTime, bTime, 7);

  memcpy(outbuf + 22, bTime, 7);
  outbuf[29] = XOR_BCDCrcCheck(bTime,7);
  outbuf[30] = 0x00;  //serialno, now only use the first extension data,total 10 extension data
  outbuf[31] = datalen;
  memcpy(outbuf + 32, data, datalen);
  Crc16_Ccitt(outbuf,12 + 20 + datalen, outbuf+12 + 20 + datalen);
  buflen = 12 + 20 + datalen + 2;

  return true;
}

bool CreateReadDataReq(const std::string &lockid,
                       const std::string &passwd,
                       unsigned char * outbuf,
                       unsigned int &buflen)
{
  if(lockid.length() != 14 || outbuf == NULL || buflen <34 || passwd.length() > 10)
    return false;

  memset(outbuf, 0, buflen);

  outbuf[0] = 0x7B;
  outbuf[1] = ELOCK_ID_MSG;
  int n = GetELockId(lockid,outbuf + 2, 8);
  if(n != 8)
  {
    return false;
  }
  outbuf[10] = ELOCK_READ_EXTENSION_DATA_REQ;
  outbuf[11] = 0x13;

  memcpy(outbuf + 12, passwd.c_str(), passwd.length());

  char chTime[100]= {0};
  __time64_t time_utc;
  struct tm tm_utc = {0};
  time_utc = _time64(NULL);
  _gmtime64_s(&tm_utc, &time_utc);

  BYTE bTime[7]= {0};
  _snprintf(chTime,
            sizeof(chTime) - 1,
            "%02d%02d%02d%02d%02d%02d%02d",
            (tm_utc.tm_year + 1900)/100,
            (tm_utc.tm_year + 1900)%100,
            tm_utc.tm_mon + 1,
            tm_utc.tm_mday,
            tm_utc.tm_hour,
            tm_utc.tm_min,
            tm_utc.tm_sec);
  StrToBCD(chTime, bTime, 7);

  memcpy(outbuf + 22, bTime, 7);
  outbuf[29] = XOR_BCDCrcCheck(bTime,7);
  outbuf[30] = 0x00;  //serialno, now only use the first extension data,total 10 extension data

  Crc16_Ccitt(outbuf,31,outbuf+31);
  buflen = 33;

  return true;
}

