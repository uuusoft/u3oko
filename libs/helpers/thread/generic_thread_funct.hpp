#pragma once
/**
\file       generic_thread_funct.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.12.2016
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/

namespace libs { namespace helpers { namespace thread {
/**
  \brief      Общий каркас для каждой функции потока в данной системе.
  \tparam     TTObj         тип для уникальных операций в функции потока.
  \tparam     TLoggerObj    тип для логирования в функции потока.
  \param[in]  _ctrl         объект для уникальных операций для которых создается поток.
  \param[in]  _logger       логирующий объект.
  \param[in]  _indx_thread  индекс потока внутри каждой группы (по типу TTObj), опционально.
  */
template <
  typename TTObj,
  typename TLoggerObj>
void
generic_thread_funct (
  TTObj*               _ctrl,
  TLoggerObj           _logger,
  const unsigned short _indx_thread)
{
  XULOG_TRACE ("generic_thread_funct::beg");
  std::string _etext;

  try
    {
      CHECK_STATE (_ctrl, "empty _ctrl thread");
      _ctrl->thread_funct_impl (_indx_thread);
    }
  catch (boost::interprocess::interprocess_exception& _e)
    {
      _etext = _e.what ();
    }
  catch (boost::exception& _e)
    {
      _etext = boost::diagnostic_information (_e);
    }
  catch (std::exception& _e)
    {
      _etext = _e.what ();
    }
  catch (...)
    {
      _etext = "unknown exception from main thread";
    }

  _logger (_etext);

  try
    {
      _etext.clear ();
      if (_ctrl)
        {
          _ctrl->thread_postfunct_impl ();
        }
    }
  catch (boost::interprocess::interprocess_exception& _e)
    {
      _etext = _e.what ();
    }
  catch (boost::exception& _e)
    {
      _etext = boost::diagnostic_information (_e);
    }
  catch (std::exception& _e)
    {
      _etext = _e.what ();
    }
  catch (...)
    {
      _etext = "unknown exception from post thread";
    }

  _logger (_etext);
  XULOG_TRACE ("generic_thread_funct::end");
  return;
}

}}}      // namespace libs::helpers::thread
