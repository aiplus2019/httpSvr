#include "log.h"
#include "funDef.h"

CGLog * CGLog::m_pInstance = nullptr;
CGLog::CGLog(void)
{

}

CGLog::~CGLog(void)
{
	google::ShutdownGoogleLogging();
}

int32_t CGLog::InitGLog(const char * argv0)
{	
#ifdef LOG_OUT_PRINT

	string dir_log = "log";
	string log_fatal = "./log/log_fatal_";
	string log_error = "./log/log_error_";
	string log_warning = "./log/log_warning_";
	string log_info = "./log/log_info_";
#ifdef WIN_OS 
	dir_log = "log";
	log_fatal = "log\\log_fatal_";
	log_error = "log\\log_error_";
	log_warning = "log\\log_warning_";
	log_info = "log\\log_info_";
#endif

	mkdir(dir_log.c_str(), 0755);
	google::InitGoogleLogging(argv0);
	google::SetStderrLogging(google::GLOG_INFO); //���ü������ google::INFO ����־ͬʱ�������Ļ
	google::SetLogDestination(google::GLOG_FATAL, log_fatal.c_str()); // ���� google::FATAL �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::GLOG_ERROR, log_error.c_str()); //���� google::ERROR �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::GLOG_WARNING, log_warning.c_str()); //���� google::WARNING �������־�洢·�����ļ���ǰ׺
	google::SetLogDestination(google::GLOG_INFO, log_info.c_str()); //���� google::INFO �������־�洢·�����ļ���
	
	FLAGS_max_log_size = 100; //�����־��СΪ 100MB
	FLAGS_stop_logging_if_full_disk = true; //�����̱�д��ʱ��ֹͣ��־���
	FLAGS_alsologtostderr = true;
	FLAGS_colorlogtostderr = true; //�����������Ļ����־��ʾ��Ӧ��ɫ
	
#endif	
	return 0;
}

void CGLog::GLogMsg(const char * funName, int lineNum, uint32_t nLogSeverity, const char *format, ...)
{
#ifdef LOG_OUT_PRINT
	string strTemp;
	strTemp.resize(MAX_BUFF_LOG_LEN+1);
    strTemp[MAX_BUFF_LOG_LEN] = '\0';
	char *pLogBuff = const_cast<char*>(strTemp.data());
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vsnprintf(pLogBuff,MAX_BUFF_LOG_LEN, format, arg_ptr);
	switch (nLogSeverity)
	{
	case 0:
		LOG(INFO) << "[" << funName << ":" << std::to_string(lineNum) <<"] " << pLogBuff;       
		break;
	case 1:
		LOG(WARNING) << "[" << funName << ":" << std::to_string(lineNum) << "] " << pLogBuff;
		break;
	case 2:
		LOG(ERROR) << "[" << funName << ":" << std::to_string(lineNum) << "] " << pLogBuff;
		break;
	case 3:
		LOG(FATAL) << "[" << funName << ":" << std::to_string(lineNum) << "] " << pLogBuff;
		break;
	default:
		break;
	}
	va_end(arg_ptr);	
	
#endif
	return;
}

