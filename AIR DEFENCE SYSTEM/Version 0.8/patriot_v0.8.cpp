#include <wiringPi.h>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include<stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define MAX 1024
#define PORT 54000
#define SA struct sockaddr
char buff[MAX];
char buffer[MAX] = "SERVER";


using namespace cv;
using namespace std;


const uint8_t HorizontalServoPin = 13;
const uint8_t VerticalServoPin = 12;
const uint8_t Trigger_ = 17;


uint16_t Lazer_X = 150;
uint16_t Lazer_Y = 150;

uint16_t Xposition = 140;
uint16_t Yposition = 140;
uint8_t pos_step = 1;
uint8_t sensivity = 40;

int mcenterx = 150;
int mcentery = 150;

bool control1=0;
bool control2=0;
bool control3=0;
bool control4=0;
bool trig_pos = 0;
bool AF = 0; //AF = 0 => Stop Auto Fire , AF = 1 => Open Auto Fire
bool DS = 0; //DS = 0 => Defence System Deactive , DS = 1 => Defence System Active
bool cisim_tespit_edildi = false;

Mat imgOriginal;
Mat imgHSV;
Mat imgThresholded;
/*
useconds_t usec = (useconds_t)(50*1000);//50 ms kadar bekle
int iLowH = 75;
int iHighH = 126;

int iLowS = 199;
int iHighS = 255;

int iLowV = 47;
int iHighV = 255;
*/
useconds_t usec = (useconds_t)(40*1000);//50 ms kadar bekle
int iLowH = 75;
int iHighH = 179;

int iLowS = 178;
int iHighS = 255;

int iLowV = 40;
int iHighV = 255;

int _map(int x, int in_min, int in_max, int out_min,int out_max){
    return (int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min));
}



void *motor_control_thread_func(void *arg){


    while (true){
        if(DS == 1){
            pwmWrite(HorizontalServoPin,Xposition);
            pwmWrite(VerticalServoPin, Yposition);
            digitalWrite (17, trig_pos&AF);
        }
        else{
            pwmWrite(HorizontalServoPin,140);
            pwmWrite(VerticalServoPin, 120);
            digitalWrite (17, LOW);
        }

    }
    return NULL;
}
void *UDPBroadcaster_thread_func(void *arg){
    char buffer[10] = "SERVER";
    int buffer_size = strlen(buffer);
    int sockfd;
    struct sockaddr_in     servaddr;
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    int broadcastPermission = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, sizeof(broadcastPermission)) < 0){
        perror("setsockopt() failed");
    }


    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr =  htonl(INADDR_BROADCAST);//inet_addr("255.255.255.255");
    printf("UDP Broadcaster Ready..\n");
    while(1){
        sendto(sockfd, buffer, buffer_size,MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr));
        delay(1000);
    }
    close(sockfd);
    return NULL;
}
void *TCPServer_thread_func(void *arg){

    int sockfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
    printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else{
        printf("TCP Server Ready..\n");
    }

    len = sizeof(cli);
	while(true){
    connfd = accept(sockfd, (sockaddr*)&cli, &len);
    if (connfd < 0) {
        printf("server accept failed...\n");
        exit(0);
    }
    read(connfd, buff, sizeof(buff));
    if(strcmp(buff,"OAF") == 0){
        if(DS == 1){
            AF = 1;
        }
    }
    else if(strcmp(buff,"SAF") == 0){
        AF = 0;
    }
    else if(strcmp(buff,"ADS") == 0){
        DS = 1;
    }
    else if(strcmp(buff,"DDS") == 0){
        DS = 0;
        AF = 0;
    }
    //printf("Received: %s\n", buff);
	}
	close(sockfd);
    return NULL;
}

void *axis_set_thread_func(void *arg){
control1=0;
control2=0;
while (true){

    if(cisim_tespit_edildi == true){

        if (mcentery > Lazer_Y + sensivity){
            Xposition -= pos_step;
            if (Xposition < 40)
                Xposition = 40;
                control2 = 0;
        }
        else if (mcentery < Lazer_Y - sensivity){
            Xposition += pos_step;
            if (Xposition > 240)
                Xposition = 240;
            control2 = 0;
        }
        else{
            control2 = 1;
        }



        if (mcenterx > Lazer_X + sensivity){
            Yposition += pos_step;
            /*
            if(Yposition > 220)
                Yposition = 220;
            */
            if(Yposition > 172)
                Yposition = 172;
            control1 = 0;
        }
        else if(mcenterx < Lazer_X - sensivity){
            Yposition -= pos_step;
            if(Yposition < 120)
                Yposition = 120;
            control1 = 0;
        }
        else{
            control1 = 1;
        }



        if(control1 == 1 && control2 == 1){
            trig_pos = 1;
        }
        else{
            trig_pos = 0;
        }

        usleep (usec);
    }
    else{
        trig_pos = 0;
    }

}
    return NULL;
}

int main(int argc, char** argv)
{
	VideoCapture cap(0);

	if (!cap.isOpened())
	{
		cout << "Cannot open the web cam" << endl;
		exit(-1);
	}

	wiringPiSetupGpio();
    pinMode(HorizontalServoPin,PWM_OUTPUT);
    pinMode(VerticalServoPin,PWM_OUTPUT);
    pinMode(Trigger_,OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetRange(2000);
    pwmSetClock(192);
    pthread_t motor_control_thread;
    pthread_t axis_set_thread;
    pthread_t TCPServer_thread;
    pthread_t UDPBroadcaster_thread;

    pthread_create(&motor_control_thread,NULL, motor_control_thread_func,NULL);
    pthread_create(&TCPServer_thread,NULL, TCPServer_thread_func,NULL);
    pthread_create(&UDPBroadcaster_thread,NULL, UDPBroadcaster_thread_func,NULL);
    pthread_create(&axis_set_thread,NULL, axis_set_thread_func,NULL);
	while (true)
	{
        bool bSuccess = cap.read(imgOriginal);
		if (!bSuccess)
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

        resize(imgOriginal, imgOriginal, Size(300,300));
		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV);
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		vector<vector<Point> > contours;
		vector<Vec4i>hierarchy;
		findContours(imgThresholded, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

		vector<Moments> mu(contours.size());
		if(contours.size() && DS){
            cisim_tespit_edildi = true;
            mu[0] = moments(contours[0]);
            vector<Point2f> mc(1);
            mcenterx = mu[0].m10 / mu[0].m00;
            mcentery = mu[0].m01 / mu[0].m00;
            mc[0] = Point2f((mcenterx), (mcentery));
            //drawContours(imgOriginal, contours, 0, Scalar(0, 255, 0), 2, 0);
            //circle(imgOriginal, Point(mcenterx, mcentery),3, Scalar(0, 0, 255),3, LINE_AA, 0);
            //putText(imgOriginal,("x:"+to_string(mcenterx)+"-y:"+to_string(mcentery)),Point(50,50),FONT_HERSHEY_SIMPLEX,1,Scalar(0,0,0),3,LINE_AA);
		}
		else{
            cisim_tespit_edildi = false;
		}

		/*
		imshow("Thresholded Image", imgThresholded);
		imshow("Original", imgOriginal);
        */
		if (waitKey(30) == 27)
		{
			cout << "esc key is pressed by user" << endl;
			exit(0);
		}
	}

	return 0;
}













