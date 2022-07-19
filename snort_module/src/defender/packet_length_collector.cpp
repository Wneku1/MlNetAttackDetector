#include "packet_length_collector.hpp"
#include "snort/protocols/packet.h"
#include "utils.hpp"

PacketLengthCollector::PacketLengthCollector() = default;

void PacketLengthCollector::update(snort::Packet *packet, unsigned total_packet_count)
{
  if (packet->is_from_server()) {
    m_tot_len_fwd_pkts += packet->pktlen;

    m_fwd_pkt_len_mean = average<double>(m_tot_len_fwd_pkts, total_packet_count);

  } else if (packet->is_from_client()) {
    m_tot_len_bwd_pkts += packet->pktlen;

    m_bwd_pkt_len_mean = average<double>(m_tot_len_bwd_pkts, total_packet_count);
  }

  m_pkt_len_mean = average<double>(m_tot_len_fwd_pkts + m_tot_len_bwd_pkts, total_packet_count);
}