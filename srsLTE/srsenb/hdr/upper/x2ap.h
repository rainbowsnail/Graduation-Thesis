#ifndef X2AP_H
#define X2AP_H

#include "srslte/asn1/liblte_x2ap.h"
#include "srslte/common/threads.h"
#include "srslte/interfaces/enb_interfaces.h"

namespace srsenb
{

class x2ap
	: public x2ap_interface_rrc
	, public thread
{
};

} // namespace srsenb
#endif