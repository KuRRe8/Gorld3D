/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2015-04-28
 */

#include "../3rdparty/elog.h"
#include <stdio.h>
#include "../3rdparty/pthread.h"
#include <windows.h>
#include <iostream>  
#include <fstream>  
#include <direct.h>
#include <QtCore>
#pragma comment(lib,"pthreadVC2.lib")

static pthread_mutex_t output_lock;
using namespace std;

/**
 * EasyLogger port initialize
 *
 * @return result
 */
ElogErrCode elog_port_init(void) {
    ElogErrCode result = ELOG_NO_ERR;

    pthread_mutex_init(&output_lock, NULL);

    return result;
}

/**
 * output log port interface
 *
 * @param log output of log
 * @param size log size
 */
void elog_port_output(const char *log, size_t size) {
    /* output to terminal */
	char buf[255];
	sprintf(buf,"%.*s",(int)size,log);
	//文件名
	char filePath[255];
	_getcwd(filePath, 255);
	//目录名
	char filePath1[255];
	_getcwd(filePath1, 255);
	//当前时间
	time_t timep;
	time (&timep);
	char tmp[64];

	char pathHead[255] = "\\log\\locallog";
	//get system time
	strftime(tmp,sizeof(tmp),"%Y-%m-%d ",localtime(&timep));
	//strftime(tmp1,sizeof(tmp1),"%Y-%m-%d %H:%M:%S",localtime(&timep));

	strcat(pathHead,tmp);
	strcat(pathHead,".txt");
	strcat(filePath,pathHead);
	strcat(filePath1,"\\log");
	ofstream file;
	file.open(filePath,ios::app|ios::out);
	if(!file) //check open file
	{
		file.open(filePath,ios::app|ios::out);
		file.write(buf,size);
		file.close();
	}else{
		file.write(buf,size);;
		file.close();
	}
//   sprintf("%ls", log);
}

/**
 * output lock
 */
void elog_port_output_lock(void) {
    pthread_mutex_lock(&output_lock);
}

/**
 * output unlock
 */
void elog_port_output_unlock(void) {
    pthread_mutex_unlock(&output_lock);
}


/**
 * get current time interface
 *
 * @return current time
 */
const char *elog_port_get_time(void) {
    static char cur_system_time[24] = { 0 };
	time_t timep;
	time (&timep);
	//get system time
	strftime(cur_system_time,24,"%Y-%m-%d %H:%M:%S",localtime(&timep));
	/*static SYSTEMTIME currTime;

	GetLocalTime(&currTime);
	printf(cur_system_time, 24, "%02d-%02d %02d:%02d:%02d.%03d", currTime.wMonth, currTime.wDay,
	currTime.wHour, currTime.wMinute, currTime.wSecond, currTime.wMilliseconds);*/

    return cur_system_time;
}

/**
 * get current process name interface
 *
 * @return current process name
 */
const char *elog_port_get_p_info(void) {
    static char cur_process_info[10] = { 0 };
	DWORD pid = GetCurrentProcessId();
    sprintf(cur_process_info, " pid:%04ld", GetCurrentProcessId());

    return cur_process_info;
}

/**
 * get current thread name interface
 *
 * @return current thread name
 */
const char *elog_port_get_t_info(void) {
    static char cur_thread_info[10] = { 0 };

    sprintf(cur_thread_info, " tid:%04ld", GetCurrentThreadId());

    return cur_thread_info;
}
