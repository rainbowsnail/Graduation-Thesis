#include "srslte/asn1/liblte_x2ap.h"
# include <stdio.h>
# include <stdarg.h>
# include <math.h>

/*******************************************************************************
/* X2AP_PDU CHOICE
********************************************************************************/
LIBLTE_ERROR_ENUM liblte_x2ap_pack_x2ap_pdu(
  LIBLTE_X2AP_X2AP_PDU_STRUCT *x2ap_pdu,
  LIBLTE_BYTE_MSG_STRUCT      *msg)
{
  LIBLTE_ERROR_ENUM err = LIBLTE_ERROR_INVALID_INPUTS;
  LIBLTE_BIT_MSG_STRUCT bit_msg;

  if(x2ap_pdu                                 != NULL &&
     msg                                      != NULL)
  {
    uint8_t *p    = bit_msg.msg;
    uint8_t **ptr = &p;

    // Extension
    liblte_value_2_bits(x2ap_pdu->ext?1:0, ptr, 1);

    // Message choice
    liblte_value_2_bits(x2ap_pdu->choice_type, ptr, 2);
    liblte_align_up_zero(ptr, 8);

    // Message
    if(LIBLTE_X2AP_X2AP_PDU_CHOICE_INITIATINGMESSAGE == x2ap_pdu->choice_type) {
      if(liblte_x2ap_pack_initiatingmessage(&x2ap_pdu->choice.initiatingMessage, ptr) != LIBLTE_SUCCESS) {
        return LIBLTE_ERROR_ENCODE_FAIL;
      }
    } else if(LIBLTE_X2AP_X2AP_PDU_CHOICE_SUCCESSFULOUTCOME == x2ap_pdu->choice_type) {
      if(liblte_x2ap_pack_successfuloutcome(&x2ap_pdu->choice.successfulOutcome, ptr) != LIBLTE_SUCCESS) {
        return LIBLTE_ERROR_ENCODE_FAIL;
      }
     }else if(LIBLTE_X2AP_X2AP_PDU_CHOICE_UNSUCCESSFULOUTCOME == x2ap_pdu->choice_type) {
      if(liblte_x2ap_pack_unsuccessfuloutcome(&x2ap_pdu->choice.unsuccessfulOutcome, ptr) != LIBLTE_SUCCESS) {
        return LIBLTE_ERROR_ENCODE_FAIL;
      }
    }

    liblte_align_up_zero(ptr, 8);
    bit_msg.N_bits += (*ptr - bit_msg.msg);

    liblte_pack(&bit_msg, msg);
    err = LIBLTE_SUCCESS;

  }
  return err;
}

LIBLTE_ERROR_ENUM liblte_x2ap_unpack_x2ap_pdu(
  LIBLTE_BYTE_MSG_STRUCT      *msg,
  LIBLTE_X2AP_X2AP_PDU_STRUCT *x2ap_pdu)
{
  LIBLTE_ERROR_ENUM err = LIBLTE_ERROR_INVALID_INPUTS;
  LIBLTE_BIT_MSG_STRUCT bit_msg;

  if(x2ap_pdu                                 != NULL &&
     msg                                      != NULL)
  {
    liblte_unpack(msg, &bit_msg);

    uint8_t *p    = bit_msg.msg;
    uint8_t **ptr = &p;

    // Extension
    x2ap_pdu->ext = liblte_bits_2_value(ptr, 1);

    // Message choice
    x2ap_pdu->choice_type = (LIBLTE_X2AP_X2AP_PDU_CHOICE_ENUM)liblte_bits_2_value(ptr, 2);
    liblte_align_up(ptr, 8);

    // Message
    if(LIBLTE_X2AP_X2AP_PDU_CHOICE_INITIATINGMESSAGE == x2ap_pdu->choice_type) {
      if(liblte_x2ap_unpack_initiatingmessage(ptr, &x2ap_pdu->choice.initiatingMessage) != LIBLTE_SUCCESS) {
        return LIBLTE_ERROR_DECODE_FAIL;
      }
    }else if(LIBLTE_X2AP_X2AP_PDU_CHOICE_SUCCESSFULOUTCOME == x2ap_pdu->choice_type) {
      if(liblte_x2ap_unpack_successfuloutcome(ptr, &x2ap_pdu->choice.successfulOutcome) != LIBLTE_SUCCESS) {
        return LIBLTE_ERROR_DECODE_FAIL;
      }
    }else if(LIBLTE_X2AP_X2AP_PDU_CHOICE_UNSUCCESSFULOUTCOME == x2ap_pdu->choice_type) {
      if(liblte_x2ap_unpack_unsuccessfuloutcome(ptr, &x2ap_pdu->choice.unsuccessfulOutcome) != LIBLTE_SUCCESS) {
        return LIBLTE_ERROR_DECODE_FAIL;
      }
    }

    err = LIBLTE_SUCCESS;
  }
  return err;
}