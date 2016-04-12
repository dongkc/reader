#include <map>
#include <iostream>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <Poco/ByteOrder.h>
#include <Poco/NumericString.h>

#include "msg.h"
#include "message.h"
#include "lockid.h"
#include "util.h"

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


void parse(char* buf, int len, Seal_p* seal_p)
{
  seal_p->result = buf[0];
  seal_p->voltage = buf[1];
  seal_p->success_flag = buf[2];
  memcpy((void*)seal_p->timestamp, &buf[3], 8);
  memcpy((void*)seal_p->counter, &buf[11], 4);
}

void parse(char* buf, int len, Unseal_p* unseal_p)
{
  unseal_p->result = buf[0];
  unseal_p->voltage = buf[1];
  unseal_p->success_flag = buf[2];
  memcpy((void*)unseal_p->timestamp, &buf[3], 8);
  unseal_p->alarm_counter = buf[11];
  unseal_p->alarm_type = buf[12];
  memcpy((void*)unseal_p->alarm_timestamp, &buf[13], 8);
  memcpy(unseal_p->counter, &buf[21], 4);
}

void parse(char* buf, int len, Check_p* check_p)
{
  qDebug() << "WRITE: " << format(buf, len).c_str();
  check_p->status = buf[0];
  check_p->voltage = buf[1];
  check_p->success_flag = buf[2];
  memcpy((void*)check_p->timestamp, &buf[3], 8);
  check_p->alarm_counter = buf[11];
  check_p->alarm_type = buf[12];
  memcpy((void*)check_p->alarm_timestamp, &buf[13], 8);
  memcpy(check_p->counter, &buf[21], 4);

}

void parse(char* buf, int len, ClearWarn_p* p)
{
  p->result = buf[0];
  p->voltage = buf[1];
  memcpy((void*)p->timestamp, &buf[2], 8);
}

void parse(char* buf, int len, WriteData_p* p)
{
  p->result = buf[0];
  qDebug() << "WRITE: " << format(buf, len).c_str();
  memcpy((void*)p->data, &buf[1], len - 1);
  p->len = len - 1;
}

void parse(char* buf, int len, ReadData_p* p)
{
  p->result = buf[0];
  qDebug() << "WRITE: " << format(buf, len).c_str();
  memcpy((void*)p->data, &buf[1], len - 1);
  p->len = len - 1;
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
      parse(body, len, &msg->body.seal_p);
      break;
    case ELOCK_UNSEALING_RES:
      parse(body, len, &msg->body.unseal_p);
      break;
    case ELOCK_CHECK_SEALING_RES:
      parse(body, len, &msg->body.check_p);
      break;
    case ELOCK_WRITE_DATA_RES:
      parse(body, len, &msg->body.write_data_p);
      break;
    case ELOCK_READ_DATA_RES:
      parse(body, len, &msg->body.read_data_p);
      break;
    case ELOCK_REMOVE_WARN_RES:
      parse(body, len, &msg->body.clear_warn_p);
      break;
  };

  return 0;
}

string voltage2str(char c)
{
  std::map<char, string> dic;
  dic.insert(make_pair('a', "3.30"));
  dic.insert(make_pair('b', "3.40"));
  dic.insert(make_pair('c', "3.50"));
  dic.insert(make_pair('d', "3.60"));
  dic.insert(make_pair('e', "3.65"));
  dic.insert(make_pair('f', "3.70"));
  dic.insert(make_pair('g', "3.75"));
  dic.insert(make_pair('h', "3.80"));
  dic.insert(make_pair('i', "3.85"));
  dic.insert(make_pair('p', "3.90"));
  dic.insert(make_pair('q', "4.00"));
  dic.insert(make_pair('r', "4.10"));
  dic.insert(make_pair('s', "4.20"));

  map<char, string>::iterator it;
  string voltage;
  it = dic.find(c);
  if (it == dic.end()) {
    return "";
  }
  voltage = it->second;

  return voltage +"V";
}

string timestamp2str(const char buf[8])
{
  char year[4];
  hex2ASCII(buf[0], &year[0]);
  hex2ASCII(buf[1], &year[2]);

  char mon[2];
  hex2ASCII(buf[2], &mon[0]);

  char day[2];
  hex2ASCII(buf[3], &day[0]);

  char hour[2];
  hex2ASCII(buf[4], &hour[0]);

  char minute[2];
  hex2ASCII(buf[5], &minute[0]);

  char second[2];
  hex2ASCII(buf[6], &second[0]);

  return string(year,  4) + "-" +
         string(mon, 2)   + "-" +
         string(day, 2)   + " " +
         string(hour, 2)  + ":" +
         string(minute, 2)+ ":" +
         string(second, 2);
}

string result2str_1(char c)
{
  std::map<int, string> dic;
  dic.insert(make_pair(0, "施封失败"));
  dic.insert(make_pair(1, "锁杆没有插好"));
  dic.insert(make_pair(2, "电压过低"));
  dic.insert(make_pair(3, "重复施封"));
  dic.insert(make_pair(4, "外壳破坏"));
  dic.insert(make_pair(5, "响应超时"));
  dic.insert(make_pair(6, "未检测到封条"));
  dic.insert(make_pair(7, "封条被拆"));

  string content;
  for (int i = 0; i < 8; ++i) {
    if (c & (1 << i)) {
      content += dic[i] + ",";
    }
  }

  return dic[c];
}

string result2str_2(char c)
{
  std::map<int, string> dic;
  dic.insert(make_pair(0, "解封失败"));
  dic.insert(make_pair(1, "口令错误"));
  dic.insert(make_pair(2, "电压过低"));
  dic.insert(make_pair(3, "重复解封"));
  dic.insert(make_pair(4, "未施封时解封"));
  dic.insert(make_pair(5, "报警不能解封"));
  dic.insert(make_pair(6, "响应超时"));
  dic.insert(make_pair(7, "封条报警"));

  string content;
  for (int i = 0; i < 8; ++i) {
    if (c & (1 << i)) {
      content += dic[i] + ",";
    }
  }

  return dic[c];
}

std::string serialize(const Seal_p& msg)
{
  string success_flag = "施封成功";
  if (msg.success_flag == 0xFF) {
    success_flag = "施封失败";
  }

  string voltage(voltage2str(msg.voltage));;
  string timestamp(timestamp2str(msg.timestamp));
  string result(result2str_1(msg.result));

  return success_flag + " " +
         "电压:" + voltage + " " +
         "操作时间:" + timestamp + " " +
         result;
}

string alarmtype2str(char c)
{
  std::map<int, string> dic;
  dic.insert(make_pair(1, "锁杆断开"));
  dic.insert(make_pair(2, "非法拆开"));
  dic.insert(make_pair(3, "封条失联"));
  dic.insert(make_pair(4, "施封下有封条被拆开"));
  dic.insert(make_pair(5, "保留字段"));

  string content;
  for (int i = 0; i < 8; ++i) {
    if (c & (1 << i)) {
      content += dic[i] + ",";
    }
  }

  return dic[c];
}

std::string serialize(const Unseal_p& msg)
{
  string success_flag = "解封成功";
  if (msg.success_flag == 0xFF) {
    success_flag = "解封失败";
  }

  string voltage(voltage2str(msg.voltage));;
  string timestamp(timestamp2str(msg.timestamp));
  string result(result2str_2(msg.result));
  string alarm_counter;
  uIntToStr<char>(msg.alarm_counter, 2, alarm_counter);
  string alarm_timestamp(timestamp2str(msg.alarm_timestamp));

  return success_flag + " " +
         "电压:" + voltage + " " +
         "操作时间:" + timestamp + " " +
         result + " " +
         "报警计数:" + alarm_counter + " " +
         "报警时间:" + alarm_timestamp;
}

string result2str_3(char c)
{
  std::map<char, string> dic;
  dic.insert(make_pair(1, "施封下无报警"));
  dic.insert(make_pair(2, "施封下有报警"));
  dic.insert(make_pair(3, "解封下有报警"));
  dic.insert(make_pair(4, "解封下无报警"));
  dic.insert(make_pair(5, "操作口令错误"));
  dic.insert(make_pair(6, "封条报警"));

  string content;
  for (int i = 0; i < 8; ++i) {
    if (c & (1 << i)) {
      content += dic[i] + ",";
    }
  }

  return dic[c];
}

std::string serialize(const Check_p& msg)
{
  string success_flag = "验封成功";
  if (msg.success_flag == 0xFF) {
    success_flag = "验封失败";
  }

  string voltage(voltage2str(msg.voltage));
  string timestamp(timestamp2str(msg.timestamp));
  string result(result2str_3(msg.status));
  qDebug() << "---------" << format((const char*)&msg.status, 1).c_str();
  //qDebug() << "WRITE: " << format(buf, len).c_str();
  string alarm_counter;
  uIntToStr<char>(msg.alarm_counter, 2, alarm_counter);
  string alarm_timestamp(timestamp2str(msg.alarm_timestamp));

  return success_flag + " " +
         "电压:" + voltage + " " +
         "操作时间:" + timestamp + " " +
         result + " " +
         "报警计数:" + alarm_counter + " " +
         "报警时间:" + alarm_timestamp;
}

string result2str_4(char c)
{
  std::map<int, string> dic;
  dic.insert(make_pair(1, "解除报警成功"));
  dic.insert(make_pair(2, "口令错误"));
  dic.insert(make_pair(3, "没有报警解除"));
  dic.insert(make_pair(4, "响应超时"));

  string content;
  for (int i = 0; i < 8; ++i) {
    if (c & (1 << i)) {
      content += dic[i] + ",";
    }
  }

  return dic[c];
}

std::string serialize(const ClearWarn_p& msg)
{
  string result(result2str_4(msg.result));
  string timestamp(timestamp2str(msg.timestamp));
  return result + "," + timestamp;
}

std::string serialize(const WriteData_p& msg)
{
  string result = "写入车号厢号成功";
  if (msg.result == 0xFF) {
    result = "写入车号厢号失败";
  }

  string data(msg.data, msg.len);
  qDebug() << "DATA: " << format(data.c_str(), msg.len).c_str();
  return result + "," + "车号/厢号: " + data;
}

std::string serialize(const ReadData_p& msg)
{
  string result = "读取车号厢号成功";
  if (msg.result == 0xFF) {
    result = "读取车号厢号失败";
  }

  string data(msg.data, msg.len);
  return result + "," + "车号/厢号: " + data;
}

std::string serialize(const Message& msg)
{
  string lockid;
  GetELockIdFromBuf((unsigned char*)msg.lock_id, 8, lockid);

  string body;
  switch (msg.cmd_id) {
    case  ELOCK_SEALING_RES:
      body = " " + serialize(msg.body.seal_p);
      break;
    case  ELOCK_UNSEALING_RES:
      body = " " + serialize(msg.body.unseal_p);
      break;
    case  ELOCK_CHECK_SEALING_RES:
      body = " " + serialize(msg.body.check_p);
      break;
    case  ELOCK_REMOVE_WARN_RES:
      body = " " + serialize(msg.body.clear_warn_p);
      break;
    case  ELOCK_READ_DATA_RES:
      body = " " + serialize(msg.body.read_data_p);
      break;
    case  ELOCK_WRITE_DATA_RES:
      body = " " + serialize(msg.body.write_data_p);
      break;
  };

  return lockid + body + "\n";
}
