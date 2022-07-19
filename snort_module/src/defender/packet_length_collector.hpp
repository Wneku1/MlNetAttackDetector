#pragma once

namespace snort {
struct Packet;
}

class PacketLengthCollector final
{
public:
  explicit PacketLengthCollector();

  void update(snort::Packet *, unsigned total_packet_count);

  double m_tot_len_fwd_pkts{};
  double m_tot_len_bwd_pkts{};
  double m_fwd_pkt_len_mean{};
  double m_bwd_pkt_len_mean{};
  double m_pkt_len_mean{};
};