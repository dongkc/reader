#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>
//////////////////////////////
#define ELOCK_MSG_HEAD           0x7B

////////////protocol id//////////////////
#define ELOCK_ID_MSG             0x5A
#define ELOCK_READER_ACTION_MSG  0x5B
#define ELOCK_SECOND_SIGN_MSG    0x5C
#define ELOCK_PRESS_KEY_MSG      0x5D
#define ELOCK_M1_ACTION_MSG      0x5E

///////operate command //////////////////
#define ELOCK_SEALING_REQ            0x41
#define ELOCK_SEALING_RES            0x42
#define ELOCK_UNSEALING_REQ          0x43
#define ELOCK_UNSEALING_RES          0x44
#define ELOCK_CHECK_SEALING_REQ      0x45
#define ELOCK_CHECK_SEALING_RES      0x46
#define ELOCK_REMOVE_WARN_REQ        0x47
#define ELOCK_REMOVE_WARN_RES        0x48

#define ELOCK_WRITE_EXTENSION_DATA_REQ         0x49
#define ELOCK_WRITE_EXTENSION_DATA_RES         0x4A
#define ELOCK_READ_EXTENSION_DATA_REQ          0x4B
#define ELOCK_READ_EXTENSION_DATA_RES          0x4C

#define ELOCK_WRITE_DATA_REQ   0x4F
#define ELOCK_WRITE_DATA_RES   0x50
#define ELOCK_READ_DATA_REQ    0x51
#define ELOCK_READ_DATA_RES    0x52
#define ELOCK_APN_REQ          0x57
#define ELOCK_APN_RES          0x58
#define ELOCK_READ_LOCKID_REQ  0x5D
#define ELOCK_READ_LOCKID_RES  0x5E

#define ELOCK_OPEN_WIFI_REQ          0x81
#define ELOCK_OPEN_WIFI_RES          0x82
#define ELOCK_CLOSE_WIFI_REQ         0x83
#define ELOCK_CLOSE_WIFI_RES         0x84
#define ELOCK_WRITE_SEALING_REQ      0x85
#define ELOCK_WRITE_SEALING_RES      0x86
#define ELOCK_READ_SEALING_REQ       0x87
#define ELOCK_READ_SEALING_RES       0x88

#define ELOCK_WRITE_SECOND_SIGN_REQ      0x89
#define ELOCK_WRITE_SECOND_SIGN_RES      0x8A
#define ELOCK_READ_SECOND_SIGN_REQ       0x8B
#define ELOCK_READ_SECOND_SIGN_RES       0x8C
#define ELOCK_SECOND_SIGN_READ_ID_REQ    0x8D
#define ELOCK_SECOND_SIGN_READ_ID_RES    0x8E
#define ELOCK_PRESS_KEY_READ_ID_REQ      0x8F
#define ELOCK_PRESS_KEY_READ_ID_RES      0x90
#define ELOCK_READ_M1_SEALINGID_REQ      0x91
#define ELOCK_READ_M1_SEALINGID_RES      0x92
#define ELOCK_PUSH_ID_MSG                0x9D

////////////////////request///////////////////////
bool CreateSealingReq(const std::string &lockid, const std::string &passwd, unsigned char * outbuf, unsigned int &buflen);
bool CreateUnSealingReq(const std::string &lockid, const std::string &passwd, unsigned char * outbuf, unsigned int &buflen);
bool CreateCheckSealingReq(const std::string &lockid, const std::string &passwd, unsigned char * outbuf, unsigned int &buflen);
bool CreateRemoveWarnReq(const std::string &lockid, const std::string &passwd, unsigned char * outbuf, unsigned int &buflen);
bool CreateOpenWifiReq(const std::string &lockid, unsigned char * outbuf, unsigned int &buflen);
bool CreateCloseWifiReq(const std::string &lockid, unsigned char * outbuf, unsigned int &buflen);
bool CreateWriteSealingReq(const std::string &lockid, const std::string &passwd, const std::vector<std::string> &vec, unsigned char * outbuf, unsigned int &buflen);
bool CreateReadSealingReq(const std::string &lockid, unsigned char * outbuf, unsigned int &buflen);
bool CreateWriteSecondSignReq(const std::string &lockid, const std::string &passwd, const unsigned char *signbuf, int signbuflen, unsigned char * outbuf, unsigned int &buflen);
bool CreateReadSecondSignReq(const std::string &lockid, unsigned char * outbuf, unsigned int &buflen);

bool CreateWriteExtensionDataReq(const std::string &lockid, const std::string &passwd, const unsigned char *data, int datalen, unsigned char * outbuf, unsigned int &buflen);
bool CreateReadExtensionDataReq(const std::string &lockid, const std::string &passwd, unsigned char * outbuf, unsigned int &buflen);


bool CreateSecondSignReadIdReq(const unsigned char *signbuf, int signbuflen, unsigned char * outbuf, unsigned int &buflen);
bool CreatePressKeyReadIdReq(unsigned char * outbuf, unsigned int &buflen);
bool CreateReadM1SealingIdReq(unsigned char * outbuf, unsigned int &buflen);

bool CreateReadMemoryInfoReq(const std::string &lockid, const std::string &passwd,unsigned char * outbuf, unsigned int &buflen);
bool CreateWriteMemoryInfoReq(const std::string &lockid, const std::string &passwd,const std::string &plateno,const std::string &containno,
	const std::string & manifestno, const std::string & width,const std::string &height,const std::string &length,const std::string &weight,unsigned char * outbuf, unsigned int &buflen);

////////////response/////////////
bool ParseElockIdActionRes(unsigned char * buf, unsigned int buflen, std::string & strresult);
bool ParseSecondSignActionRes(unsigned char * buf, unsigned int buflen, std::string & strresult);
bool ParsePushIdMsg(unsigned char * buf, unsigned int buflen, std::string & strresult);
bool ParsePressKeyActionRes(unsigned char * buf, unsigned int buflen, std::string & strresult);
bool ParseM1SealingActionRes(unsigned char * buf, unsigned int buflen, std::string & strresult);

////////////////////////////////////////////
unsigned char GetCmdcodeFromPacket(unsigned char * buf, unsigned int buflen, int & len);
int IsCompletePacket(unsigned char * buf, unsigned int buflen);
bool ProcessPacket(unsigned char * buf, unsigned int buflen, std::string & strresult);

void CreateGeneralResponse(const std::string & id,  std::string & elockid, std::string & strret);

bool CreateWriteDataReq(const std::string &lockid,
                        const std::string &passwd,
                        const char * data,
                        int datalen,
                        unsigned char * outbuf,
                        unsigned int &buflen);

bool CreateRemoveWarnReq(const std::string &lockid,
                         const std::string &passwd,
                         unsigned char * outbuf,
                         unsigned int &buflen);

bool CreateReadDataReq(const std::string &lockid,
                       const std::string &passwd,
                       unsigned char * outbuf,
                       unsigned int &buflen);

bool CreateAPNReq(const std::string &lockid,
                  const std::string &passwd,
                  const std::string &apn,
                  const std::string &phone,
                  const std::string &ip,
                  const std::string &port,
                  const std::string &interval,
                  const std::string &pass,
                  unsigned char * outbuf,
                  unsigned int &buflen);

bool CreateReadLockidReq(const std::string &lockid,
                         const std::string &passwd,
                         unsigned char * outbuf,
                         unsigned int &buflen);
#endif
