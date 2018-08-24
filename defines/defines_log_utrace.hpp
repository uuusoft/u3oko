#pragma once
/**
\file       defines_log_utrace.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      empty brief
*/
#if !defined(UUU_LOG_TAG)
//  ������������� ������ ��������� �� ���������. ����� (� �������� ������) ���� ������������� � ������ ������ �������.
#define UUU_LOG_TAG "uuu_def_tag"
#endif

#if defined(UUU_DISABLED_LOG)

#define ULOG_TRACE(_msg, _tag)
#define XULOG_TRACE(_msg)
#define ULOG_DEBUG(_msg, _tag)
#define XULOG_DEBUG(_msg)
#define ULOG_INFO(_msg, _tag)
#define XULOG_INFO(_msg)
#define ULOG_WARNING(_msg, _tag)
#define XULOG_WARNING(_msg)
#define ULOG_ERROR(_msg, _tag)
#define XULOG_ERROR(_msg)
#define ULOG_FATAL(_msg, _tag)
#define XULOG_FATAL(_msg)
#define ULOG_TEST(_msg, _tag)
#define XULOG_TEST(_msg)
#define ULOG_ASSERT(_msg, _tag)
#define XULOG_ASSERT(_msg)

#else

#if defined(UUU_DEBUG)

#define ULOG_TRACE(_msg, _tag) BOOST_LOG_TRIVIAL (trace) << _tag << ": " << _msg;
#define XULOG_TRACE(_msg) BOOST_LOG_TRIVIAL (trace) << UUU_LOG_TAG << ": " << _msg;
#define ULOG_DEBUG(_msg, _tag) BOOST_LOG_TRIVIAL (debug) << _tag << ": " << _msg;
#define XULOG_DEBUG(_msg) BOOST_LOG_TRIVIAL (debug) << UUU_LOG_TAG << ": " << _msg;
#define ULOG_INFO(_msg, _tag) BOOST_LOG_TRIVIAL (info) << _tag << ": " << _msg;
#define XULOG_INFO(_msg) BOOST_LOG_TRIVIAL (info) << UUU_LOG_TAG << ": " << _msg;
#define ULOG_WARNING(_msg, _tag) BOOST_LOG_TRIVIAL (warning) << _tag << ": " << _msg;
#define XULOG_WARNING(_msg) BOOST_LOG_TRIVIAL (warning) << UUU_LOG_TAG << ": " << _msg;
#define ULOG_ERROR(_msg, _tag) BOOST_LOG_TRIVIAL (error) << _tag << ": " << _msg;
#define XULOG_ERROR(_msg) BOOST_LOG_TRIVIAL (error) << UUU_LOG_TAG << ": " << _msg;
#define ULOG_FATAL(_msg, _tag) BOOST_LOG_TRIVIAL (fatal) << _tag << ": " << _msg;
#define XULOG_FATAL(_msg) BOOST_LOG_TRIVIAL (fatal) << UUU_LOG_TAG << ": " << _msg;
#define ULOG_TEST(_msg, _tag) BOOST_LOG_TRIVIAL (warning) << "uuu_test: " << _tag << ": " << _msg;
#define XULOG_TEST(_msg) BOOST_LOG_TRIVIAL (warning) << "uuu_test: " << UUU_LOG_TAG << ": " << _msg;
#define ULOG_ASSERT(_msg, _tag) BOOST_LOG_TRIVIAL (fatal) << "uuu_assert: " << _tag << ": " << _msg;
#define XULOG_ASSERT(_msg) BOOST_LOG_TRIVIAL (fatal) << "uuu_assert: " << UUU_LOG_TAG << ": " << _msg;

#else

#define ULOG_TRACE(_msg, _tag)
#define XULOG_TRACE(_msg)
#define ULOG_DEBUG(_msg, _tag)
#define XULOG_DEBUG(_msg)
#define ULOG_INFO(_msg, _tag) BOOST_LOG_TRIVIAL (info) << _tag << ": " << _msg;
#define XULOG_INFO(_msg) BOOST_LOG_TRIVIAL (info) << UUU_LOG_TAG << ": " << _msg;
#define ULOG_WARNING(_msg, _tag) BOOST_LOG_TRIVIAL (warning) << _tag << ": " << _msg;
#define XULOG_WARNING(_msg) BOOST_LOG_TRIVIAL (warning) << UUU_LOG_TAG << ": " << _msg;
#define ULOG_ERROR(_msg, _tag) BOOST_LOG_TRIVIAL (error) << _tag << ": " << _msg;
#define XULOG_ERROR(_msg) BOOST_LOG_TRIVIAL (error) << UUU_LOG_TAG << ": " << _msg;
#define ULOG_FATAL(_msg, _tag) BOOST_LOG_TRIVIAL (fatal) << _tag << ": " << _msg;
#define XULOG_FATAL(_msg) BOOST_LOG_TRIVIAL (fatal) << UUU_LOG_TAG << ": " << _msg;
#define ULOG_TEST(_msg, _tag) BOOST_LOG_TRIVIAL (warning) << "uuu_test: " << _tag << ": " << _msg;
#define XULOG_TEST(_msg) BOOST_LOG_TRIVIAL (warning) << "uuu_test: " << UUU_LOG_TAG << ": " << _msg;
#define ULOG_ASSERT(_msg, _tag) BOOST_LOG_TRIVIAL (fatal) << "uuu_assert: " << _tag << ": " << _msg;
#define XULOG_ASSERT(_msg) BOOST_LOG_TRIVIAL (fatal) << "uuu_assert: " << UUU_LOG_TAG << ": " << _msg;

#endif

#endif
