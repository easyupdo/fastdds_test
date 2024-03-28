
#include <iostream>
#include <chrono>
#include <thread>

#include "demoPubSubTypes.h"

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



class A;

class B{
    friend class A;
    public:
    B() = default;
    void B_Test(){}

    private:
    B(int i){
        std::cout<<"private::B(int i)"<<std::endl;
    }

    int B2(){}

    int B_a;
};


class A{
    public:
    A() = default;

    void A_Test() {
        b.B_a = 1;
        B * bb = new B(1);
    }

    private:
    B b;
    int A_a;
};






int main(int argc,char ** argv) {

    A a;
    B b;
    // a.B(1);
    
    b.B_Test();

    auto factory = eprosima::fastdds::dds::DomainParticipantFactory::get_instance();

    eprosima::fastdds::dds::DomainParticipantQos dp_qos;
    dp_qos.wire_protocol().builtin.discovery_config.discoveryProtocol = eprosima::fastrtps::rtps::DiscoveryProtocol_t::SIMPLE;
    dp_qos.name("DemoPubDP");
    dp_qos.transport().use_builtin_transports = false;

    auto user_udp_transport = std::make_shared<eprosima::fastdds::rtps::UDPv4TransportDescriptor>();
    dp_qos.transport().user_transports.push_back(user_udp_transport);
    


    

    eprosima::fastdds::dds::DomainParticipant* dp = factory->create_participant(111,dp_qos);
    getchar();

    helloworldPubSubType typ;
    eprosima::fastdds::dds::TypeSupport type(&typ);
    ReturnCode_t r_code = type.register_type(dp);

    eprosima::fastdds::dds::PublisherQos pub_qos;
    auto publisher = dp->create_publisher(pub_qos);

    eprosima::fastdds::dds::TopicQos topic_qos;
    auto topic = dp->create_topic("HW_TOPIC","helloworld",topic_qos);

    eprosima::fastdds::dds::DataWriterQos dw_qos;
    dw_qos.history().kind = eprosima::fastdds::dds::HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS;
    dw_qos.history().depth = 100;
    dw_qos.resource_limits().max_samples = 5;
    dw_qos.resource_limits().allocated_samples = 5;
    dw_qos.reliability().kind = eprosima::fastdds::dds::ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS;
    dw_qos.durability().kind = eprosima::fastdds::dds::DurabilityQosPolicyKind::TRANSIENT_LOCAL_DURABILITY_QOS;

    // dw_qos.lifespan().duration = {1,0};
    dw_qos.liveliness().kind = eprosima::fastdds::dds::AUTOMATIC_LIVELINESS_QOS;
    dw_qos.liveliness().lease_duration = {5,0};
    dw_qos.liveliness().announcement_period = {4,1};

    auto dw = publisher->create_datawriter(topic,dw_qos);

    // send

    helloworld hw;
    // hw.data() = "HelloWorld";
    int index = 0;
    std::string s = "HelloWorld";
    std::string ss ="";
    while(1) {
        ss = s+std::to_string(index++);
        hw.data() = ss;
        bool is_write = dw->write((void*)&hw);
        std::cout<<"Writr:"<<is_write<<"Data:"<<ss<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    return 0;
}