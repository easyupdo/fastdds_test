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
#include <ReceiverResource.h>
#include <NetworkFactory.h>


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
    eprosima::fastdds::rtps::UDPSenderResource;

    eprosima::fastrtps::rtps::RTPSParticipantAttributes attr;

    eprosima::fastrtps::rtps::NetworkFactory network_factory(attr);
    // network_factory.BuildReceiverResources();



    // eprosima::fastdds::rtps::Locator locator(1111);

    std::vector<std::shared_ptr<eprosima::fastrtps::rtps::ReceiverResource>> returned_resources_list;

    network_factory.RegisterTransport(udp_transport->get_configuration());

    eprosima::fastrtps::rtps::LocatorList_t locator_list;
    network_factory.generate_locators(36000,1,locator_list);
    // locator_list.begin()

    bool is_ok = network_factory.BuildReceiverResources(*locator_list.begin(),returned_resources_list,1024);


    // transport.OpenInputChannel(locator, this, max_message_size_);


    // eprosima::fastdds::rtps::TransportReceiverInterface * tri = returned_resources_list.begin()->get();
    // for(auto & locator : locator_list){
    //     udp_transport->OpenInputChannel(locator,tri,36000);
    // }
    // udp_transport->OpenAndBindInputSocket();
    


    // eprosima::fastrtps::rtps::MessageReceiver mr();

    for(auto & rs:returned_resources_list) {
        ;
        // rs->RegisterReceiver();
        // rs->OnDataReceived();
    }

    while(1){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    return 0;
}