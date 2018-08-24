//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       to_str.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      empty brief
*/

namespace libs { namespace ilink { namespace appl { namespace helpers {
/**
  \brief      Вспомогательная функция для преобразования структуры в строку. Для трассировки.
  \param[in]  _obj  объект преобразования.
  \return     строка результата преобразования.
  */
inline std::string
to_str (const StateProcessEventExt& _obj)
{
  std::string _ret;

  _ret += "sync " + ::to_str (_obj.sync_);
  _ret += ", request_ " + ::to_str (_obj.request_);
  _ret += ", answer_ " + ::to_str (_obj.answer_);
  _ret += ", recv_seq_ " + ::to_str (_obj.recv_seq_);
  _ret += ", make_seq_ " + ::to_str (_obj.make_seq_);

  if (_obj.make_seq_ || _obj.recv_seq_)
    {
      _ret += ", id " + _obj.id_seq_.name ();
    }

  _ret += ", msg " + (_obj.msg_ ? _obj.msg_->get_mid () : "empty");
  return _ret;
}

}}}}      // namespace libs::ilink::appl::helpers
