//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       codec-brower.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_vcodec_gen
\brief      Интерфейс объекта поиска кодеков в системе.
*/

namespace dlls { namespace codecs { namespace vcodec_gen { namespace browser {
/**
  \brief  Класс для хранения информации о доступных видеокодеках в системе.
  */
class CodecBrower final
{
  public:
  CodecBrower ();

  ~CodecBrower ();

  CodecBrower (const CodecBrower& _src) = delete;
  CodecBrower& operator= (const CodecBrower& _src) = delete;
  /**
    \brief      Функция возвращает по идентификатору имя файла с кодеком или пусто.
    \param[in]  _id идентификатор кодека.
    \return     имя файла.
    */
  std::string get_codec (const ::libs::helpers::utils::cuuid& _id);


  private:
  //  int types
  using sync_type      = std::mutex;
  using guard_type     = std::lock_guard<sync_type>;
  using guid2file_type = std::map<::libs::helpers::utils::cuuid, std::string>;
  /**
    \brief  Функция обновляет список кодеков
    */
  void refresh_list_codecs ();

  sync_type      mtx_;            //< Т.к. у объкту возможен доступ из разных потоков, кладем объект для синхронизации доступа.
  bool           refreshed_;      //< Флаг, список кодеков обновлен.
  guid2file_type guid2file_;      //< Поле для пребразования guid в имя файла.
};

}}}}      // namespace dlls::codecs::vcodec_gen::browser
