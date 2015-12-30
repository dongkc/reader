#include <string>
#include <stdint.h>

struct Seal_q
{
  char passwd[10];
  char timestamp[10];
};

struct Seal_p
{
  char result;
  char voltage;
  char success_flag;
  char timestamp;
  char counter[4];
};

struct Unseal_q
{
  char passwd[10];
  char timestamp[10];
};

struct Unseal_p
{
  char result;
  char voltage;
  char success_flag;
  char timestamp;
  char alarm_counter;
  char alarm_type;
  char alarm_timestamp;
  char counter[4];
};

struct Verify_q
{
  char passwd[10];
  char timestamp[10];
};

struct Verify_p
{
  char status;
  char voltage;
  char success_flag;
  char timestamp;
  char alarm_counter;
  char alarm_type;
  char alarm_timestamp;
  char counter[4];
};

struct Message
{
  char protocol_id;
  char lock_id[8];
  char cmd_id;

  union
  {
    Seal_q    seal_q;
    Seal_p    seal_p;
    Unseal_q  unseal_q;
    Unseal_p  unseal_p;
    Verify_q  verify_q;
    Verify_p  verify_p;
  }body;
};


int parse(const Message& msg);
