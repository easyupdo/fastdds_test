DEMO_SRC=./include/demo.cxx ./include/demoPubSubTypes.cxx

FASTCDR_INC=/home/linux/Data/DDS/install/fastcdr/include
FASTCDR_LIB=/home/linux/Data/DDS/install/fastcdr/lib

FASTRTPS_INC=/home/linux/Data/DDS/install/fastrtps/include
FASTRTPS_lib=/home/linux/Data/DDS/install/fastrtps/lib

TRANSPORT_SRC=/home/linux/Data/Fast-DDS-2.13.3/src/cpp/rtps/transport
NETWORK_SRC=/home/linux/Data/Fast-DDS-2.13.3/src/cpp/rtps/network
COMMON_SRC=/home/linux/Data/Fast-DDS-2.13.3/src/cpp
COMMON_INC= -I/home/linux/Data/Fast-DDS-2.13.3/include/fastdds/rtps/common/ -I/home/linux/Data/Fast-DDS-2.13.3/src/cpp/rtps/ -I/home/linux/Data/DDS/install/fastrtps/include/fastdds/rtps/participant/ -I/home/linux/Data/DDS/src/fastrtps/test/mock/rtps/RTPSParticipant/fastdds/rtps/participant/ -I/home/linux/Data/Fast-DDS-2.13.3/thirdparty/filewatch/

COMMON_LIB= -lpthread

pub:
	g++ src/demo_pub.cc ${DEMO_SRC} -o demo_pub -g -std=c++11 -I${FASTCDR_INC} -I${FASTRTPS_INC} -I./include -L${FASTCDR_LIB} -L${FASTRTPS_lib} -lfastcdr -lfastrtps
sub:
	g++ src/demo_sub.cc ${DEMO_SRC} -o demo_sub -g -std=c++11 -I${FASTCDR_INC} -I${FASTRTPS_INC} -I./include -L${FASTCDR_LIB} -L${FASTRTPS_lib} -lfastcdr -lfastrtps


n_pub:
	g++ src/network_pub.cc ${DEMO_SRC} -o network_pub -g -std=c++11 -I ${COMMON_INC} -I${COMMON_SRC} -I${TRANSPORT_SRC} -I${NETWORK_SRC} -I${FASTCDR_INC} -I${FASTRTPS_INC} -I./include -L${FASTCDR_LIB} -L${FASTRTPS_lib} -lfastcdr -lfastrtps ${COMMON_LIB}

n_sub:
	g++ src/network_sub.cc ${DEMO_SRC} -o network_sub -g -std=c++11 -I${COMMON_SRC} -I${TRANSPORT_SRC} -I${NETWORK_SRC} -I${FASTCDR_INC} -I${FASTRTPS_INC} -I./include -L${FASTCDR_LIB} -L${FASTRTPS_lib} -lfastcdr -lfastrtps ${COMMON_LIB}


r_pub:
	g++ src/rtps_pub.cc ${DEMO_SRC} -o rtps_pub -g -std=c++11 ${COMMON_INC} -I${COMMON_SRC} -I${TRANSPORT_SRC} -I${NETWORK_SRC} -I${FASTCDR_INC} -I${FASTRTPS_INC} -I./include -L${FASTCDR_LIB} -L${FASTRTPS_lib} -lfastcdr -lfastrtps ${COMMON_LIB}


r_sub:
	g++ src/rtps_sub.cc ${DEMO_SRC} -o rtps_sub -g -std=c++11 -I${COMMON_SRC} -I${TRANSPORT_SRC} -I${NETWORK_SRC} -I${FASTCDR_INC} -I${FASTRTPS_INC} -I./include -L${FASTCDR_LIB} -L${FASTRTPS_lib} -lfastcdr -lfastrtps ${COMMON_LIB}


all: pub sub
	
	