from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

import os
import yaml
from yaml import load, Loader

def generate_launch_description():
    commonFilePath = os.path.join(get_package_share_directory('cpp_sensorsim'), 'launch/common.yaml')
    with open(commonFilePath, 'r') as f:
        data = yaml.load(f, Loader=Loader)
    return LaunchDescription([
        Node(
            package="cpp_sensorsim",
            namespace=data['node_prop']['namespace'],
            executable="pub",
            output="screen",
            emulate_tty=True,
            parameters=[
                {
                    "topic_GPS_nodeName" : data['topic_GPS']['nodeName'], 
                    "topic_GPS_topicName" : data['topic_GPS']['topicName'], 
                    "topic_GPS_pubInterval" : data['topic_GPS']['publishInterval'], 
                    "topic_IMU_nodeName" : data['topic_IMU']['nodeName'], 
                    "topic_IMU_topicName" : data['topic_IMU']['topicName'], 
                    "topic_IMU_pubInterval" : data['topic_IMU']['publishInterval'], 
                    "topic_ENV_nodeName" : data['topic_ENV']['nodeName'], 
                    "topic_ENV_topicName" : data['topic_ENV']['topicName'], 
                    "topic_ENV_pubInterval" : data['topic_ENV']['publishInterval'], 
                    "topic_Ultrasound_nodeName" : data['topic_Ultrasound']['nodeName'], 
                    "topic_Ultrasound_topicName" : data['topic_Ultrasound']['topicName'], 
                    "topic_Ultrasound_pubInterval" : data['topic_Ultrasound']['publishInterval'], 
                    "topic_WheelState_nodeName" : data['topic_WheelState']['nodeName'], 
                    "topic_WheelState_topicName" : data['topic_WheelState']['topicName'], 
                    "topic_WheelState_pubInterval" : data['topic_WheelState']['publishInterval'], 
                    "topic_IDTable_nodeName" : data['topic_IDTable']['nodeName'], 
                    "topic_IDTable_topicName" : data['topic_IDTable']['topicName'], 
                    "topic_IDTable_pubInterval" : data['topic_IDTable']['publishInterval'], 
                    "mainNodeName" : data['node_prop']['nodeName'], 
                }
            ]
        )
    ])