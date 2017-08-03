//
// Created by gps on 8/1/17.
//

#ifndef GNSS_SDR_ANTI_SPOOF_MESSAGE_H_
#define GNSS_SDR_ANTI_SPOOF_MESSAGE_H_

#include "gnss_signal.h"
#include "gnss_synchro.h"

class Anti_Spoofing_Message
{
public:
    Anti_Spoofing_Message(){
        System = 'N';
        Tracking_timestamp_secs = 0.0;
        PRN = 0;
        Flag_valid_pseudorange = false;
        dll_Ei = 0;
        dll_Pi = 0;
        dll_Li = 0;
        dll_Eq = 0;
        dll_Pq = 0;
        dll_Lq = 0;

        CN0_dB_hz = 0.0;
        d_TOW_at_current_symbol = 0.0;
        Pseudorange_m = 0.0;
    };

    Anti_Spoofing_Message(Gnss_Synchro sync)
    {
        System = sync.System;
        Tracking_timestamp_secs = sync.Tracking_timestamp_secs;
        PRN = sync.PRN;
        Flag_valid_pseudorange = sync.Flag_valid_pseudorange;

        dll_Ei = sync.dll_Ei;
        dll_Pi = sync.dll_Pi;
        dll_Li = sync.dll_Li;
        dll_Eq = sync.dll_Eq;
        dll_Pq = sync.dll_Pq;
        dll_Lq = sync.dll_Lq;

        CN0_dB_hz = sync.CN0_dB_hz;
        d_TOW_at_current_symbol = sync.d_TOW_at_current_symbol;
        Pseudorange_m = sync.Pseudorange_m;
    };

    friend std::ostream& operator<<(std::ostream& os, const Anti_Spoofing_Message& _asm)
    {
        os << _asm.Tracking_timestamp_secs << ',' << _asm.PRN << ',' << _asm.Flag_valid_pseudorange
              << ',' << _asm.dll_Eq << ',' << _asm.dll_Pq << ',' << _asm.dll_Lq
              << ',' << _asm.dll_Ei << ',' << _asm.dll_Pi << ',' << _asm.dll_Li
              << ',' << _asm.CN0_dB_hz << ',' << _asm.d_TOW_at_current_symbol << _asm.Pseudorange_m << std::endl;

        return  os;
    }

private:
    char System;
    double Tracking_timestamp_secs;
    unsigned int PRN;
    bool Flag_valid_pseudorange;
    float dll_Eq;
    float dll_Pq;
    float dll_Lq;
    float dll_Ei;
    float dll_Pi;
    float dll_Li;

    double CN0_dB_hz;
    double d_TOW_at_current_symbol;
    double Pseudorange_m;
};

#include <boost/interprocess/ipc/message_queue.hpp>

// could easily be made a template; make sure T is a POD!
class Anti_Spoofing_Message_Queue {
public:
    Anti_Spoofing_Message_Queue(const char* const name,
              const unsigned max_queue_size) :
            Anti_Spoofing_Message_Queue{ name, max_queue_size, delete_queue(name) }
    {}

    Anti_Spoofing_Message_Queue(const char* const name) :
            mq_{ boost::interprocess::open_only, name }
    {}

    void send(int i) {
        mq_.send(&i, sizeof(i), 0 /* priority */);
    }

    int receive() {
        int result;
        boost::interprocess::message_queue::size_type recvsize;
        unsigned recvpriority;
        mq_.receive(&result, sizeof(result), recvsize, recvpriority);
        return result;
    }

private:
    struct did_delete_t {};

    did_delete_t delete_queue(const char* const name) {
        boost::interprocess::message_queue::remove(name);
        return did_delete_t{};
    }

    Anti_Spoofing_Message_Queue(const char* const name,
              const unsigned max_queue_size,
              did_delete_t) :
            mq_ { boost::interprocess::create_only, name, max_queue_size, sizeof(int) }
    {}

    boost::interprocess::message_queue mq_;
};

#endif