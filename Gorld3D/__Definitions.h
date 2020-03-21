/*
This file contains pre-definitions.

You should NOT #include this file directly, #include __Utilities.h instead.
*/


#pragma once

#define G3D_INTERNAL_VERSION "0.03" //update VER in Progress.ykw, __Definitions.h & exe.rc simultaneously
#define Y_CONCATENATE(q,w) q##w
#define ykw_debug
#define NO_LOG
//#define QT_NO_DEBUG_OUTPUT

#define info_std_qdebug qDebug("location: FILE = %s, FUNC = %s, LINE = %d",__FILE__,__FUNCTION__,__LINE__);
											///controls the highest level of elog output
											///* output log's level */
											///#define ELOG_LVL_ASSERT                      0
											///#define ELOG_LVL_ERROR                       1
											///#define ELOG_LVL_WARN                        2
											///#define ELOG_LVL_INFO                        3
											///#define ELOG_LVL_DEBUG                       4
											///#define ELOG_LVL_VERBOSE                     5
#ifdef NO_LOG
	#define LOG_LVL          ELOG_LVL_ASSERT-1
#elif _DEBUG
	#define LOG_LVL          ELOG_LVL_DEBUG
#else
	#define LOG_LVL          ELOG_LVL_INFO    //less log
#endif // NO_LOG|_DEBUG

#define MAX_TAG_LENGTH 99
#define LOG_TAG logger_tag
