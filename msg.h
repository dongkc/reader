#include <QString>
#include <string>
#include <stdint.h>

struct Seal_q
{
  char passwd[10];
  char timestamp[8];
};

struct Seal_p
{
  unsigned char result;
  unsigned char voltage;
  unsigned char success_flag;
  char timestamp[8];
  char counter[4];
};

struct Unseal_q
{
  char passwd[10];
  char timestamp[8];
};

struct Unseal_p
{
  unsigned char result;
  unsigned char voltage;
  unsigned char success_flag;
  char timestamp[8];
  char alarm_counter;
  char alarm_type;
  char alarm_timestamp[8];
  char counter[4];
};

struct Check_q
{
  char passwd[10];
  char timestamp[8];
};

struct Check_p
{
  unsigned char status;
  unsigned char voltage;
  unsigned char success_flag;
  char timestamp[8];
  char alarm_counter;
  char alarm_type;
  char alarm_timestamp[8];
  char counter[4];
};

struct ClearWarn_q
{
  char passwd[10];
  char timestamp[8];
};

struct ClearWarn_p
{
  unsigned char result;
  unsigned char voltage;
  char timestamp[8];
};

struct WriteData_q
{
  char passwd[10];
  char data[256];
  uint8_t len;
  char timestamp[8];
};

struct WriteData_p
{
  unsigned char result;
  char data[256];
  uint8_t len;
};

struct ReadData_q
{
  char passwd[10];
  char timestamp[8];
};

struct ReadData_p
{
  char result;
  char data[256];
  uint8_t len;
  char timestamp[8];
};

struct WriteApn_q
{
  char apn[30];
  char phone[11];
  char ip[22];
  char interval[4];
  char initial_passwd[8];
};

struct WriteApn_p
{
  unsigned char success_flag;
};

struct Message
{
  char protocol_id;
  char lock_id[8];
  char cmd_id;

  union
  {
    Seal_q      seal_q;
    Seal_p      seal_p;
    Unseal_q    unseal_q;
    Unseal_p    unseal_p;
    Check_q     check_q;
    Check_p     check_p;
    ClearWarn_q clear_warn_q;
    ClearWarn_p clear_warn_p;
    ReadData_q  read_data_q;
    ReadData_p  read_data_p;
    WriteData_q write_data_q;
    WriteData_p write_data_p;
    WriteApn_q  write_apn_q;
    WriteApn_p  write_apn_p;
  }body;
};

int parse(char* buf, int len, Message* msg);

QString serialize(const Message& msg);

std::string serialize(const Seal_p& msg);

std::string serialize(const Unseal_p& msg);

std::string serialize(const Check_p& msg);
