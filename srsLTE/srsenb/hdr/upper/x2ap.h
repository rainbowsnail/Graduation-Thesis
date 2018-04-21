#ifndef X2AP_H
#define X2AP_H

#include "srslte/asn1/liblte_x2ap.h"
namespace srsenb
{

class x2ap
	: public x2ap_interface_rrc
	, public thread
{

};

}
#endif