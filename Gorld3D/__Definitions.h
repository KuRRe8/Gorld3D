/*
This file contains pre-definitions.

You should NOT #include this file directly, #include __Utilities.h instead.
*/


#pragma once

#define G3DVERSION "0.01" 
#define ykw_debug
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
#ifdef _DEBUG
	#define LOG_LVL          ELOG_LVL_DEBUG
#else
	#define LOG_LVL          ELOG_LVL_INFO    //less log
#endif // _DEBUG

#define LOG_TAG          logger_tag
