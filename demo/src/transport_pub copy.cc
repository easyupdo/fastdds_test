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

int main(int argc, char ** argv) {

    auto user_udp_transport_dsp = std::make_shared<eprosima::fastdds::rtps::UDPv4TransportDescriptor>();
    eprosima::fastdds::rtps::TransportInterface * transport_udp_interface =  user_udp_transport_dsp->create_transport();


    // eprosima::fastdds::rtps:
    eprosima::fastdds::rtps::UDPv4Transport * udp_transport = static_cast<eprosima::fastdds::rtps::UDPv4Transport*>(transport_udp_interface);
    bool is_init = udp_transport->init();

    //eprosima::fastdds::rtps::SendResourceList &sender_resource_list
    //std::vector<std::unique_ptr<fastrtps::rtps::SenderResource>>;
    eprosima::fastdds::rtps::SendResourceList send_res_list;

    // std::unique_ptr<eprosima::fastrtps::rtps::SenderResource> sr = std::make_unique<eprosima::fastdds::rtps::UDPSenderResource>(udp_transport,);
    // send_res_list.push_back(sr);

    //eprosima::fastrtps::rtps::Locator_t;
    eprosima::fastdds::rtps::Locator locator(1111);
    
    udp_transport->OpenOutputChannel(send_res_list,locator);
    


    /*
    return transport.send(data, dataSize, socket_, destination_locators_begin,
                    destination_locators_end, only_multicast_purpose_, whitelisted_,
                    max_blocking_time_point);
    */

   std::vector<eprosima::fastdds::rtps::Locator> vec_locators; 
   vec_locators.push_back(locator);


    eprosima::fastdds::rtps::Locators locators(vec_locators.begin());

    std::vector<eprosima::fastdds::rtps::LocatorsIterator *> dds_locators;
    dds_locators.push_back(&locators);

    eprosima::fastrtps::rtps::octet data[10];

    std::chrono::_V2::steady_clock::time_point tp;
    for(auto &send:send_res_list){
        send->send(data,5,*dds_locators.begin(),*dds_locators.end(),tp);
    }

    return 0;
}