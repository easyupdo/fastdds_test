
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

#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/qos/SubscriberQos.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>

#include <fastdds/rtps/transport/UDPv4TransportDescriptor.h>

class SubListener : public eprosima::fastdds::dds::DataReaderListener
    {
    public:

        SubListener()
        {
        }

        ~SubListener() override
        {
        }

        void on_data_available(
                eprosima::fastdds::dds::DataReader* reader) override {
                    std::cout<<"on_data_available"<<std::endl;
                    helloworld hw;
                    eprosima::fastdds::dds::SampleInfo sample_info;
                    auto r_code = reader->read_next_sample(&hw,&sample_info);
                    std::cout<<"r_code:"<<r_code()<<std::endl;
                    
                    if(!r_code()){
                        std::cout<<"Data:"<<hw.data()<<std::endl;
                        // std::this_thread::sleep_for(std::chrono::seconds(10));
                    }
                }

        void on_subscription_matched(
                eprosima::fastdds::dds::DataReader* reader,
                const eprosima::fastdds::dds::SubscriptionMatchedStatus& info) override {
                    std::cout<<"on_subscription_matched"<<std::endl;

                }



    RTPS_DllAPI virtual void on_requested_deadline_missed(
            eprosima::fastdds::dds::DataReader* reader,
            const eprosima::fastrtps::RequestedDeadlineMissedStatus& status)
    {
        (void)reader;
        (void)status;
        std::cout<<"on_requested_deadline_missed"<<std::endl;
    }

    RTPS_DllAPI virtual void on_liveliness_changed(
            eprosima::fastdds::dds::DataReader* reader,
            const eprosima::fastrtps::LivelinessChangedStatus& status)
    {
        (void)reader;
        (void)status;
        std::cout<<"alive_count:"<<status.alive_count<<std::endl;
        std::cout<<"alive_count_change:"<<status.alive_count_change<<std::endl;
        std::cout<<"not_alive_count:"<<status.not_alive_count<<std::endl;
        std::cout<<"not_alive_count_change:"<<status.not_alive_count_change<<std::endl;
        std::cout<<"last_publication_handle:"<<status.last_publication_handle<<std::endl;

        std::cout<<"on_liveliness_changed"<<std::endl;
    }

    RTPS_DllAPI virtual void on_sample_rejected(
            eprosima::fastdds::dds::DataReader* reader,
            const eprosima::fastrtps::SampleRejectedStatus& status)
    {
        (void)reader;
        (void)status;
        std::cout<<"on_sample_rejected"<<std::endl;
    }

    RTPS_DllAPI virtual void on_requested_incompatible_qos(
            eprosima::fastdds::dds::DataReader* reader,
            const eprosima::fastdds::dds::RequestedIncompatibleQosStatus& status)
    {
        (void)reader;
        (void)status;
        std::cout<<"on_requested_incompatible_qos"<<std::endl;
    }

    RTPS_DllAPI virtual void on_sample_lost(
            eprosima::fastdds::dds::DataReader* reader,
            const eprosima::fastdds::dds::SampleLostStatus& status)
    {
        (void)reader;
        (void)status;
        std::cout<<"on_sample_lost"<<std::endl;
    }

};



int main(int argc,char ** argv) {

    auto factory = eprosima::fastdds::dds::DomainParticipantFactory::get_instance();

    eprosima::fastdds::dds::DomainParticipantQos dp_qos;
    // dp_qos.wire_protocol().builtin.discovery_config.
    dp_qos.transport().use_builtin_transports = false;

    auto user_udp_transport_dsp = std::make_shared<eprosima::fastdds::rtps::UDPv4TransportDescriptor>();
    dp_qos.transport().user_transports.push_back(user_udp_transport_dsp);

    
    eprosima::fastdds::dds::DomainParticipant* dp = factory->create_participant(111,dp_qos);

    getchar();

    helloworldPubSubType typ;
    eprosima::fastdds::dds::TypeSupport type(&typ);
    type.register_type(dp);

    // eprosima::fastdds::dds::PublisherQos pub_qos;
    // auto publisher = dp->create_publisher(pub_qos);

    eprosima::fastdds::dds::SubscriberQos sub_qos;
    auto subscriber = dp->create_subscriber(sub_qos);

    eprosima::fastdds::dds::TopicQos topic_qos;
    auto topic = dp->create_topic("HW_TOPIC","helloworld",topic_qos);

    // eprosima::fastdds::dds::DataWriterQos dw_qos;
    // auto dw = publisher->create_datawriter(topic,dw_qos);


    eprosima::fastdds::dds::DataReaderQos dr_qos;
    dr_qos.history().kind = eprosima::fastdds::dds::HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS;
    dr_qos.history().depth = 100;
    dr_qos.resource_limits().max_samples = 5;
    dr_qos.resource_limits().allocated_samples = 5;
    dr_qos.durability().kind = eprosima::fastdds::dds::DurabilityQosPolicyKind::TRANSIENT_LOCAL_DURABILITY_QOS;
    dr_qos.reliability().kind = eprosima::fastdds::dds::ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS;
    // dr_qos.lifespan().duration = {1,0};
    dr_qos.liveliness().kind = eprosima::fastdds::dds::AUTOMATIC_LIVELINESS_QOS;
    dr_qos.liveliness().lease_duration = {5,0};
    dr_qos.liveliness().announcement_period = {4,1};

    SubListener sub_listener;
    auto dr = subscriber->create_datareader(topic,dr_qos,&sub_listener);

    while(1) {
        // dw->write((void*)&hw);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}