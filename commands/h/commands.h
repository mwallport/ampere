#ifndef __COMMANDS__
#define __COMMANDS__
#include <inttypes.h>

// temp controller read and write cmds
static const uint16_t   CTRLR_READ_FUNC     = 0x03;
static const uint16_t   CTRLR_WRITE_FUNC    = 0x06;
static const size_t     WRITE_RESP_PKT_LEN  = 8;
static const size_t     READ_RESP_PKT_LEN   = 8;


class cmdResp
{
  public:
  cmdResp(bool retCode, uint8_t* buff, uint8_t bufflen)
    : m_retCode(retCode), m_buff(buff), m_bufflen(bufflen) {}

  bool      m_retCode;  // true is success, false is failed
  uint8_t*  m_buff;     // for read cmd, this is the data that came back
                        // or , should this just be the whole packet . . ?
  uint16_t  m_bufflen;  // the lenght of the data in the buff
};


class cmd
{
  public:
  cmd();
  virtual ~cmd();
  uint8_t buildReadCmd(uint8_t* buff, uint8_t bufflen, uint16_t dataCnt, uint8_t id, uint16_t param_addr);
  uint8_t buildWriteCmd(uint8_t* buff, uint8_t bufflen, uint16_t dataCnt, uint8_t id, uint16_t param_addr);
  cmdResp buildReadResp(uint8_t*, uint8_t, uint8_t);
  cmdResp buildWriteResp(uint8_t*, uint8_t, uint8_t);

  cmd(const cmd&) = delete;
  cmd& operator=(const cmd&) = delete;

  bool validateCtrlrRxPkt(uint8_t* buff, uint8_t bufflen, uint8_t id, bool=false);
  uint16_t  paramAddr() const;
  uint8_t   cmdLength() const;
  uint8_t   dataLength() const;

  protected:
  uint16_t    m_paramAddr;
  uint8_t     m_cmdLength;  // length of the cmd, should always be 8
  uint8_t     m_data;       // for read cmds is the requested byte count
                            // for write cmds is the data to be written

  private:
};

#endif

