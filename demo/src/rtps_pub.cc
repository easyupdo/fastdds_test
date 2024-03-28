#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>

#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>

#include <fastdds/rtps/transport/UDPv4TransportDescriptor.h>

// #include </rtps/transport/UDPv4Transport.h>
#include <UDPv4Transport.h>
#include <UDPSenderResource.hpp>
// /home/linux/Data/DDS/src/fastrtps/src/cpp/rtps/transport
#include <NetworkFactory.h>

#include <UDPTransportInterface.h>

#include <RTPSDomainImpl.hpp>
#include <RTPSParticipantListener.h>
#include <RTPSParticipant.h>

#include <memory>
// /home/linux/Data/Fast-DDS-2.13.3/src/cpp/rtps/transport/UDPTransportInterface.h

int main(int argc, char ** argv) {

    std::shared_ptr< eprosima::fastrtps::rtps::RTPSDomainImpl> rtps_domain = eprosima::fastrtps::rtps::RTPSDomainImpl::get_instance();

    eprosima::fastrtps::rtps::RTPSParticipantAttributes arrt;
    eprosima::fastrtps::rtps::RTPSParticipantListener listener;
    eprosima::fastrtps::rtps::RTPSParticipant * rtps_dp = rtps_domain->createParticipant(111,true,arrt,&listener);

    rtps_dp->enable();
    
    getchar();
   

    return 0;
}